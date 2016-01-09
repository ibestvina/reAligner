#pragma once
#include "Consensus.h"
#include "Alignment.h"
#include "AlignedFragment.h"
#include <exception>

class ReAligner
{
public:
	ReAligner();
	~ReAligner();
	static Consensus &getConsensus(Alignment &alignment);

//private:
	static double getConsensusScoreWeighted(double scoreF1, double scoreF2);
	static Metasymbol *getConsensusMetasymbol(std::list<char> &column);
	static std::list<char> &getColumn(Alignment &layoutMap, int index);
	static double getColumnScore(std::list<char> &column, Metasymbol* sym);
	static double getColumnScore(std::list<char> &column, char sym);
	static int getNumberOfColumns(Alignment &layoutMap);
	static void dashFunction(Consensus &consensus);
	static void dashFunction(AlignedFragment &fragment);
	static void getAlignment(AlignedFragment &read, Consensus &cons, double eps);
	static Consensus& reAlign(Alignment &alignment, double epsilonPrecision, int numOfIterations);
};

