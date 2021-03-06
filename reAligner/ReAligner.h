#pragma once

#include <list>

#include "Consensus.h"
#include "Alignment.h"
#include "AlignedFragment.h"
#include "Metasymbol.h"
#include "ColumnCount.h"


class ReAligner
{
public:
	ReAligner();
	~ReAligner();
	static Consensus *getConsensus(Alignment *alignment);
	static Consensus *reAlign(Alignment *alignment, double epsilonPrecision, int numOfIterations);
	static char* consensusToString(Alignment* alignment);
	static char* consensusToString2(Alignment* alignment);
	static char getColumnChar(Alignment* layoutMap, int index);
	static std::vector<ColumnCount> getPartOfConsensus(Alignment* alignment, int start, int end, int dashesFront, int dashesBack);
	static double getConsensusScoreWeighted(double scoreF1, double scoreF2);
	static Metasymbol *getConsensusMetasymbol(std::list<char> *column);
	static std::list<char>* getColumn(Alignment* layoutMap, int index);
	static double getColumnScore(std::list<char> *column, Metasymbol* sym);
	static double getColumnScore(std::list<char> *column, char sym);
	static int getNumberOfColumns(Alignment *layoutMap);
	static void dashFunction(Consensus *consensus);
	static void dashFunction(AlignedFragment &fragment);
	static void getAlignment(AlignedFragment &read, Alignment *alignment, int delta);
};

