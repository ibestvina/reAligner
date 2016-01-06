#include "ReAligner.h"
#include <vector>
#include <iostream>
#include <list>
#include <limits>


ReAligner::ReAligner()
{
}


ReAligner::~ReAligner()
{
}

Consensus &ReAligner::getConsensus(Alignment & alignment)
{
	// TODO (mock object only)
	return *new Consensus(0);
}

void ReAligner::calculateConsensusScore(Consensus & consensus, Alignment & alignment)
{
	// TODO: after calculating do: consensus.setScore(calculatedScore);
}

Metasymbol * ReAligner::getConsensusMetasymbol(std::list<char>& column, int height)
{
	return nullptr;
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

Consensus ReAligner::reAlign(Alignment & alignment, double epsilonPrecision, int numOfIterations)
{
	Consensus consensus = getConsensus(alignment);
	calculateConsensusScore(consensus, alignment);
	double initialScore = consensus.getScore();
	bool shouldContinue = true;
	int iteration = 1;
	int numOfReads = alignment.getSize();
	
	double minimalScore = initialScore;
	Consensus bestConsensus = consensus;

	while (shouldContinue) {
		std::cout << "Iterating...";

		for (int k = 0; k < numOfReads; k++) {
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
