#include "ReAligner.h"
#include <vector>
#include <iostream>


ReAligner::ReAligner()
{
}


ReAligner::~ReAligner()
{
}

void ReAligner::calculateConsensusScore(Consensus & consensus, Alignment & alignment)
{
	// TODO: consensus.setScore(calculatedScore);
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
