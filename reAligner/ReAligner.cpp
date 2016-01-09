#include "ReAligner.h"
#include <vector>
#include <iostream>
#include <map>
#include <list>
#include <limits>
#include <algorithm>
#include <exception>


ReAligner::ReAligner()
{
}


ReAligner::~ReAligner()
{
}


double ReAligner::getConsensusScoreWeighted(double scoreF1, double scoreF2)
{
	return 0.5 * scoreF1 + 0.5 * scoreF2;
}

Consensus &ReAligner::getConsensus(Alignment & alignment)
{
	int columnsNum = getNumberOfColumns(alignment);
	Consensus &consensus = *new Consensus();
	double f1Score = 0.0;
	double f2Score = 0.0;
	double columnScoreTmp;
	for (int c = 0; c < columnsNum; ++c) {
		std::list<char> column = getColumn(alignment, c);
		Metasymbol* consensusSymbol = getConsensusMetasymbol(column);
		if (consensusSymbol->getSize() == 5) {
			int x = c;
		}
		consensus.addMetasymbol(consensusSymbol);

		columnScoreTmp = getColumnScore(column , consensusSymbol);

		f1Score += columnScoreTmp;
		if (column.size() > 0) {
			f2Score += columnScoreTmp / column.size();
		}
	}
	consensus.setScore(getConsensusScoreWeighted(f1Score, f2Score));
	return consensus;
}

Metasymbol * ReAligner::getConsensusMetasymbol(std::list<char>& column)
{
	Metasymbol* sym = new Metasymbol;
	if (column.size() == 0) {
		sym->addSymbol('-');
		return sym;
	}
	map<char, int> M;
	M['A'] = 0;
	M['C'] = 1;
	M['G'] = 2;
	M['T'] = 3;
	M['-'] = 4;
	char symbols[5] = { 'A', 'C', 'G', 'T', '-' };
	int counter[5];
	memset(counter, 0, sizeof(counter));
	int maks = 0;
	for (std::list<char>::iterator itr = column.begin(); itr != column.end(); ++itr) {
		int index = M[*itr];		
		counter[index]++;
		if (counter[index] > maks) {
			maks = counter[index];
		}
	}
	for (int i = 0; i < 5; ++i) {
		if (maks == counter[i]) {
			sym->addSymbol(symbols[i]);
		}
	}

	return sym;
}

void ReAligner::getAlignment(AlignedFragment & read, Consensus & cons, double eps)
{
	int min = std::numeric_limits<int>::min();
	std::list<Metasymbol*> consPartList;

	Metasymbol* dashSym = new Metasymbol();
	dashSym->addSymbol('-');

	int delta = (int)(eps / 2);

	int readLen = read.getLength();
	int readOff = read.getOffset();
	int consLen = cons.getLength();


	// -- Consensus part construction --
	int consPartStart = readOff - delta;
	int frontDashes = (consPartStart < 0) ? -consPartStart : 0;
	consPartStart = (consPartStart < 0) ? 0 : consPartStart;
	int consPartEnd = readOff + readLen + delta;
	int backDashes = (consPartEnd > consLen) ? consPartEnd-consLen : 0;
	consPartEnd = (consPartEnd > consLen) ? consLen : consPartEnd;

	consPartList = cons.getPart(consPartStart, consPartEnd);

	for (int i = 0; i < backDashes; i++)
		consPartList.push_back(dashSym);
	for (int i = 0; i < frontDashes; i++)
		consPartList.push_front(dashSym);

	int consPartLen = consPartList.size();

	std::vector<Metasymbol*> consPart(std::begin(consPartList), std::end(consPartList));


	// -- Needleman–Wunsch algorithm --

	vector<vector<int>> valueTable;
	vector<vector<bool>> isDiagonal;
	for (int i = 0; i <= readLen; i++) {
		vector<int> rowInt;
		vector<bool> rowBool;
		for (int j = 0; j <= consPartLen; j++) {
			rowInt.push_back(min);
			rowBool.push_back(false);
		}
		valueTable.push_back(rowInt);
		isDiagonal.push_back(rowBool);
	}

	// Initial values
	for (int j = 0; j <= 2 * delta; j++) {
		valueTable[0][j] = -abs(j - delta);
	}

	// Main loop
	for (int i = 1; i <= readLen; i++) {
		for (int j = 1; j <= consPartLen; j++) {
			if (j >= i && j <= i + 2 * delta) {
				Metasymbol *sym = consPart[j - 1];
				int cost = -1;
				if (sym->contains(read.getAt(i - 1)) || sym->isDashOnly())
					cost = 0;

				int scoreDiag = valueTable[i - 1][j - 1] + cost;
				int scoreLeft = (valueTable[i][j - 1] == min) ? min : valueTable[i][j - 1] - 1;

				if (scoreDiag >= scoreLeft) {
					valueTable[i][j] = scoreDiag;
					isDiagonal[i][j] = true;
				}
				else {
					valueTable[i][j] = scoreLeft;
				}
			}
		}
	}

	int score = min;
	int endPoisition = 0;
	for (int i = 0; i <= 2 * delta; i++) {
		int currentValue = valueTable[readLen][consPartLen - i];
		if (score < currentValue) {
			score = currentValue;
			endPoisition = consPartLen - i;
		}
	}

	std::string newSequence = "";
	int tabi = readLen;
	int tabj = endPoisition;
	while (tabi > 0) {
		if (isDiagonal[tabi][tabj]) {
			newSequence = read.getAt(tabi-1) + newSequence;
			tabi--;
			tabj--;
		}
		else {
			newSequence = "-" + newSequence;
			tabj--;
		}
	}

	int newOffset = read.getOffset() + tabj - delta;

	read.setSequence(newSequence);
	read.setOffset(newOffset);

	return;
}

Consensus& ReAligner::reAlign(Alignment & alignment, double epsilonPrecision, int numOfIterations)
{
	Consensus &consensus = getConsensus(alignment);
	double initialScore = consensus.getScore();
	bool shouldContinue = true;
	int iteration = 1;
	int numOfReads = alignment.getSize();
	
	double minimalScore = initialScore;
	Consensus& bestConsensus = consensus;

	while (shouldContinue) {
		std::cout << "Iterating...";

		for (int k = 0; k < numOfReads; k++) {
			std::cout << k << "/" << numOfReads << endl;
			// detach first fragment in a list - append it last after iteration
			AlignedFragment* sequence = alignment.PopFirst();
			dashFunction(*sequence);
			dashFunction(consensus);
			consensus = getConsensus(alignment);
			getAlignment(*sequence, consensus, sequence->getLength() * epsilonPrecision);

			alignment.AddFragment(sequence);
			consensus = getConsensus(alignment);
			if (consensus.getScore() < minimalScore) {
				bestConsensus = consensus;
				minimalScore = consensus.getScore();
			}
		}

		if (bestConsensus.getScore() >= initialScore || iteration == numOfIterations) {
			shouldContinue = false;
		}

		std::cout << "After " << iteration << " iterations score is: " << bestConsensus.getScore() << "   previous score : " << initialScore;
		initialScore = bestConsensus.getScore();
		iteration++;
	}

	return bestConsensus;
}

void ReAligner::dashFunction(Consensus &consensus)
{
	consensus.removeDashesFrontAndBack();
}

void ReAligner::dashFunction(AlignedFragment & fragment)
{
	fragment.removeDashesFrontAndBack();
}

std::list<char>& ReAligner::getColumn(Alignment & layoutMap, int index)
{
	std::list<char> &column = *new std::list<char>;
	std::list<AlignedFragment*> &fragments = layoutMap.getAllFragments();
	for (std::list<AlignedFragment*>::const_iterator iter = fragments.begin(); iter != fragments.end(); ++iter) {
		int offset = (*iter)->getOffset();
		int length = (*iter)->getLength();
		if (offset <= index && offset + length > index) {
			char sym = (*iter)->getAt(index - offset);
			column.push_back(sym);
		}
	}
	return column;
}

/**
 * Returns how many symbols from column don't match symbols from metasymbol.
 */
double ReAligner::getColumnScore(std::list<char> &column, Metasymbol* sym) {
	double score = 0.0;
	std::list<char> symbols = sym->getSymbols();
	for (std::list<char>::iterator c = column.begin(); c != column.end(); ++c) {
		if (std::find(symbols.begin(), symbols.end(), *c) == symbols.end()) {
			score += 1;
		}
	}
	return score;
}

/**
 * Returns how many symbols from column don't match sym.
 */
double ReAligner::getColumnScore(std::list<char> &column, char sym) {
	double score = 0.0;
	for (std::list<char>::iterator c = column.begin(); c != column.end(); ++c) {
		if (sym != *c) {
			score += 1;
		}
	}
	return score;
}

int ReAligner::getNumberOfColumns(Alignment & layoutMap)
{
	int numOfColumns = 0;
	std::list<AlignedFragment*> &fragments = layoutMap.getAllFragments();
	for (std::list<AlignedFragment*>::const_iterator iter = fragments.begin(); iter != fragments.end(); ++iter) {
		int offset = (*iter)->getOffset();
		int length = (*iter)->getLength();
		numOfColumns = std::max(numOfColumns, offset + length);
	}
	return numOfColumns;
}
