#include "TestReAligner.h"
#include "ReAligner.h"
#include <list>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(TestReAligner);

void TestReAligner::setUp(){}
void TestReAligner::tearDown(){}

vector<char> toVector(std::list<char> chars) {
	vector<char> ret; ret.clear();
	for (std::list<char>::iterator it = chars.begin(); it != chars.end(); ++it) {
		ret.push_back(*it);
	}
	return ret;
}

bool compareDouble(double a, double b) {
	if (abs(a - b) <= 0.0000001) {
		return true;
	}
	return false;
}

void TestReAligner::getConsensusTest() {
	std::list<AlignedFragment*> fragments = std::list<AlignedFragment*>();
	fragments.push_back(new AlignedFragment(*new Fragment(1, 3, "ACA"), *new FragmentAlignment(1, 3, 0, 0, 0)));
	fragments.push_back(new AlignedFragment(*new Fragment(1, 3, "TAT"), *new FragmentAlignment(1, 3, 0, 0, 0)));
	fragments.push_back(new AlignedFragment(*new Fragment(1, 3, "AAT"), *new FragmentAlignment(1, 3, 0, 0, 0)));
	Consensus consensus = ReAligner::getConsensus(*new Alignment(fragments));
	std::list<Metasymbol*> metasymbols = consensus.getPart(0, 3);
	vector<char> symbols[3];
	int counter = 0;
	for (std::list<Metasymbol*>::iterator itr = metasymbols.begin(); itr != metasymbols.end(); ++itr) {
		symbols[counter].clear();
		symbols[counter] = toVector((*itr)->getSymbols());
		counter++;
	}
	CPPUNIT_ASSERT(symbols[0].size() == 1);
	CPPUNIT_ASSERT(symbols[1].size() == 1);
	CPPUNIT_ASSERT(symbols[2].size() == 1);
	CPPUNIT_ASSERT(symbols[0][0] == 'A');
	CPPUNIT_ASSERT(symbols[1][0] == 'A');
	CPPUNIT_ASSERT(symbols[2][0] == 'T');
}

void TestReAligner::getConsensusMetasymbolTest() {
	std::list<char> column;
	column.push_back('T');
	column.push_back('A');
	column.push_back('C');
	column.push_back('A');
	vector<char> symbols = toVector(ReAligner::getConsensusMetasymbol(column)->getSymbols());
	CPPUNIT_ASSERT(symbols.size() == 1);
	CPPUNIT_ASSERT(symbols[0] == 'A');

	column.push_back('T');
	symbols = toVector(ReAligner::getConsensusMetasymbol(column)->getSymbols());
	CPPUNIT_ASSERT(symbols.size() == 2);
	CPPUNIT_ASSERT(symbols[0] == 'A');
	CPPUNIT_ASSERT(symbols[1] == 'T');
}

void TestReAligner::getColumnScoreTest() {
	std::list<char> column;
	column.push_back('T');
	column.push_back('A');
	column.push_back('C');
	column.push_back('A');
	Metasymbol* metasymbol = ReAligner::getConsensusMetasymbol(column);
	double score = ReAligner::getColumnScore(column, metasymbol);
	
	column.push_back('T');
	column.push_back('A');
	metasymbol = ReAligner::getConsensusMetasymbol(column);
	score = ReAligner::getColumnScore(column, metasymbol);
	CPPUNIT_ASSERT(compareDouble(3.0, score) == true);

	column.push_back('T');
	metasymbol = ReAligner::getConsensusMetasymbol(column);
	score = ReAligner::getColumnScore(column, metasymbol);
	CPPUNIT_ASSERT(compareDouble(1.0, score) == true);
}