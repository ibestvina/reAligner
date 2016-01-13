#include <vector>
#include <iostream>
#include <map>
#include <list>
#include <limits>
#include <algorithm>
#include <iterator>
#include <string>
#include <cstring>

#include "ReAligner.h"



std::vector<vector<double>> valueTable;
std::vector<vector<bool>> isDiagonal;
int numberOfColumns = 0;
ColumnCount* dash;



ReAligner::ReAligner()
{
}


ReAligner::~ReAligner()
{
}

// defines the weights of scores used
double ReAligner::getConsensusScoreWeighted(double scoreF1, double scoreF2)
{
	return 0.5 * scoreF1 + 0.5 * scoreF2;
}

// returns a part of consensus with delta dashes added to the front and back to which a fragment is aligned
// consensus is returned in list<ColumnCount> format, for easier score calculation
std::vector<ColumnCount> ReAligner::getPartOfConsensus(Alignment* alignment, int start, int end, int dashesFront, int dashesBack)
{
	int columnsNum = numberOfColumns;
	std::vector<ColumnCount> part(end-start + dashesFront + dashesBack);
	
	// add dashes front
	for (int c = 0; c < dashesBack; c++) {
		part[c] = *dash;
	}

	// add consensus columnCounts
	for (int c = 0; c < end - start; ++c) {
		std::list<char> *column = getColumn(alignment, c+start);
		ColumnCount columnCount(column);

		part[c+dashesBack] = columnCount;

		delete column;
	}

	// add dashes back
	int partEnd = dashesBack + end - start + dashesFront;
	for (int c = dashesBack + end - start; c < partEnd; c++) {
		part[c] = *dash;
	}

	return part;
}

// returns a consensus (list<Metasymbol>) of an alignment and calculates its score
Consensus *ReAligner::getConsensus(Alignment* alignment)
{
	int columnsNum = getNumberOfColumns(alignment);
	Consensus *consensus = new Consensus();

	double f1Score = 0.0;
	double f2Score = 0.0;
	double columnScoreTmp;
	for (int c = 0; c < columnsNum; ++c) {
		std::list<char> *column = getColumn(alignment, c);
		Metasymbol* consensusSymbol = getConsensusMetasymbol(column);

		consensus->addMetasymbol(consensusSymbol);

		columnScoreTmp = getColumnScore(column , consensusSymbol);

		f1Score += columnScoreTmp;
		int colSize = column->size();
		if (colSize > 0) {
			f2Score += columnScoreTmp / colSize;
		}
		delete column;
	}
	consensus->setScore(getConsensusScoreWeighted(f1Score, f2Score));
	return consensus;
}

// returns a column metasymbol
Metasymbol * ReAligner::getConsensusMetasymbol(std::list<char>* column)
{
	Metasymbol* sym = new Metasymbol;
	if (column->size() == 0) {
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
	std::memset(counter, 0, sizeof(counter));
	int maks = 0;
	for (std::list<char>::iterator itr = column->begin(); itr != column->end(); ++itr) {
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

// Needleman–Wunsch algorithm implementation. Takes an alignment, fragment, and delta value. Aligns the fragment to the consensus of alignment, 
void ReAligner::getAlignment(AlignedFragment & read, Alignment *alignment, int delta)
{
	int readLen = read.getLength();
	int readOff = read.getOffset();
	int consLen = numberOfColumns;


	// -- Consensus part construction --
	int consPartStart = readOff - delta;
	int frontDashes = (consPartStart < 0) ? -consPartStart : 0;
	consPartStart = (consPartStart < 0) ? 0 : consPartStart;
	int consPartEnd = readOff + readLen + delta;
	int backDashes = (consPartEnd > consLen) ? consPartEnd-consLen : 0;
	consPartEnd = (consPartEnd > consLen) ? consLen : consPartEnd;

	std::vector<ColumnCount> consPart = getPartOfConsensus(alignment, consPartStart, consPartEnd, frontDashes, backDashes);
	

	int consPartLen = consPart.size();

	// -- Needleman–Wunsch algorithm --


	// Initial values
	for (int j = 0; j <= 2 * delta; j++) {
		valueTable[0][j] = -abs(j - delta);
	}

	// First column
	for (int i = 1; i <= readLen; i++) {
		ColumnCount cc = consPart[i - 1];
		double cost = cc.getScore(read.getAt(i - 1));

		double scoreDiag = valueTable[i - 1][0] + cost;

		valueTable[i][0] = scoreDiag;
		isDiagonal[i][0] = true;
	}


	int stripWidth = 2 * delta + 1;

	// Main loop
	for (int i = 1; i <= readLen; i++) {
		for (int k = 1; k < stripWidth; k++) {
			ColumnCount cc = consPart[k + i - 1];
			double cost = cc.getScore(read.getAt(i - 1));

			double scoreDiag = valueTable[i - 1][k] + cost;
			double scoreLeft = valueTable[i][k - 1] - 1;

			if (scoreDiag >= scoreLeft) {
				valueTable[i][k] = scoreDiag;
				isDiagonal[i][k] = true;
			}
			else {
				valueTable[i][k] = scoreLeft;
				isDiagonal[i][k] = false;
			}
		}
	}

	double score = -1 * numeric_limits<double>::max();
	int endPoisition = 0;
	for (int i = 0; i <= 2 * delta; i++) {
		int currentValue = valueTable[readLen][stripWidth - 1 - i];
		if (score < currentValue) {
			score = currentValue;
			endPoisition = stripWidth - 1 - i;
		}
	}

	std::string newSequence = "";
	int tabi = readLen;
	int tabj = endPoisition;
	while (tabi > 0) {
		if (isDiagonal[tabi][tabj]) {
			newSequence = read.getAt(tabi-1) + newSequence;
			tabi--;
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

// round-robin frame method of the main algorithm
// iterates through fragments and realignes them
Consensus *ReAligner::reAlign(Alignment & alignment, double epsilonPrecision, int numOfIterations)
{
	numberOfColumns = getNumberOfColumns(&alignment);
	Consensus *initialConsensus = getConsensus(&alignment);
	double initialScore = initialConsensus->getScore();
	int iteration = 1;
	int numOfReads = alignment.getSize();

	std::list<char> *dashList = new std::list<char>();
	dashList->push_back('-');
	dash = new ColumnCount(dashList);

	// initialize valueTable and isDiagonal
	int maxReadLen = 0;
	for (AlignedFragment* AF : *(alignment.getAllFragments()))
	{
		int currLen = AF->getLength();
		if (currLen > maxReadLen) {
			maxReadLen = currLen;
		}
	}

	valueTable.clear();
	isDiagonal.clear();
	maxReadLen = maxReadLen * pow((epsilonPrecision + 1), numOfIterations);
	int maxStripWidth = (int)(epsilonPrecision * maxReadLen) + 1;
	for (int i = 0; i <= maxReadLen; i++) {
		std::vector<double> rowInt(maxStripWidth);
		std::vector<bool> rowBool(maxStripWidth);

		valueTable.push_back(rowInt);
		isDiagonal.push_back(rowBool);
	}

	

	double bestScore = initialScore;
	Consensus *bestConsensus = initialConsensus;
	int oldNumberOfColumns = numberOfColumns;

	std::cout << "Starting score is: " << bestScore << std::endl;

	while (true) 
	{
		for (int k = 0; k < numOfReads; k++) 
		{
			//std::cout << k << "/" << numOfReads << endl;

			// detach first fragment in a list - append it last after iteration
			AlignedFragment* sequence = alignment.PopFirst();
			if (sequence->getLength() + sequence->getOffset() == numberOfColumns) {
				oldNumberOfColumns = numberOfColumns;
				numberOfColumns = getNumberOfColumns(&alignment);
			}
			
			//dashFunction(*sequence);

			int delta = (int)((epsilonPrecision * sequence->getLength()) / 2);
			getAlignment(*sequence, &alignment, delta);

			alignment.AddFragment(sequence);
			numberOfColumns = oldNumberOfColumns;
		}

		Consensus *newConsensus = getConsensus(&alignment);
		double newScore = newConsensus->getScore();
		if (newScore >= bestScore) 
		{
			std::cout << "Ending with score: " << bestScore << std::endl;
			return bestConsensus;
		}
		if (iteration == numOfIterations) 
		{
			std::cout << "Ending with score: " << newScore << std::endl;
			return newConsensus;
		}

		std::cout << "After " << iteration << " iterations score is: " << newScore << std::endl;
		delete bestConsensus;
		bestConsensus = newConsensus;
		bestScore = newScore;
		iteration++;
	}

	return bestConsensus;
}

void ReAligner::dashFunction(Consensus *consensus)
{
	consensus->removeDashesFrontAndBack();
}

void ReAligner::dashFunction(AlignedFragment & fragment)
{
	fragment.removeDashesFrontAndBack();
}


// finds all elements of a specified column in alignment
std::list<char>* ReAligner::getColumn(Alignment* layoutMap, int index)
{
	std::list<char> *column = new std::list<char>;
	std::list<AlignedFragment*> *fragments = layoutMap->getAllFragments();
	for (std::list<AlignedFragment*>::const_iterator iter = fragments->begin(); iter != fragments->end(); ++iter) {
		int offset = (*iter)->getOffset();
		int length = (*iter)->getLength();
		if (offset <= index && offset + length > index) {
			char sym = (*iter)->getAt(index - offset);
			column->push_back(sym);
		}
	}
	return column;
}

/**
 * Returns how many symbols from column don't match symbols from metasymbol.
 */
double ReAligner::getColumnScore(std::list<char> *column, Metasymbol* sym) {
	double score = 0.0;
	std::list<char> symbols = sym->getSymbols();
	for (std::list<char>::iterator c = column->begin(); c != column->end(); ++c) {
		if (std::find(symbols.begin(), symbols.end(), *c) == symbols.end()) {
			score += 1;
		}
	}
	return score;
}

/**
 * Returns how many symbols from column don't match sym.
 */
double ReAligner::getColumnScore(std::list<char> *column, char sym) {
	double score = 0.0;
	for (std::list<char>::iterator c = column->begin(); c != column->end(); ++c) {
		if (sym != *c) {
			score += 1;
		}
	}
	return score;
}

// returns a number of columns in an alignment
int ReAligner::getNumberOfColumns(Alignment* layoutMap)
{
	int numOfColumns = 0;
	std::list<AlignedFragment*> *fragments = layoutMap->getAllFragments();
	for (std::list<AlignedFragment*>::const_iterator iter = fragments->begin(); iter != fragments->end(); ++iter) {
		int offset = (*iter)->getOffset();
		int length = (*iter)->getLength();
		numOfColumns = std::max(numOfColumns, offset + length);
	}
	return numOfColumns;
}
