#pragma once
#include "Consensus.h"
#include "Alignment.h"
#include "AlignedFragment.h"

class ReAligner
{
public:
	ReAligner();
	~ReAligner();
	static Consensus &getConsensus(Alignment &alignment);
private:

	static void calculateConsensusScore(Consensus &consensus, Alignment &alignment);
	static Metasymbol *getConsensusMetasymbol(std::list<char> &column, int height);
	static double getConsensusScoreWeighted(AlignedFragment &detachedSeq, Consensus &consensus, Alignment &subalignment);
	static double getConsensusScoreWithFunction1(AlignedFragment &sequence, Consensus &consensus);
	static double getConsensusScoreWithFunction2(AlignedFragment &sequence, Alignment &alignmentMap);
	static std::list<char> &getColumn(Alignment &layoutMap, int index);
	static double getColumnScore(std::list<char> &column, Metasymbol sym);
	static double getColumnScore(std::list<char> &column, char sym);
	static int getNumberOfColumns(Alignment &layoutMap);
	static void dashFunction(Consensus &consensus);
	static void dashFunction(AlignedFragment &fragment);
	/**
	*  Alignment function  Needleman Wunsch algorithm
	*  @param seqA  detached sequence
	*  @param seqB  consensus sequence
	*  @param eps  eps
	*/
	static double getAlignment(AlignedFragment &sequenceA, Consensus &sequenceB, double eps);
	/**
	*  ReAligner
	*  @param  layoutMap map of reads
	*  @param  epsilonPrecision - predicted error of read layout, in percentage (0.0 to 1.0)
	*  @param  numOfIterations max number of iterations
	*/
	static Consensus reAlign(Alignment &layoutMap, double epsilonPrecision, int numOfIterations);
};

