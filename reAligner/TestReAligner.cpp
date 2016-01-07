#include "TestReAligner.h"
#include "ReAligner.h"
#include <list>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(TestReAligner);

void TestReAligner::setUp(){}
void TestReAligner::tearDown(){}

void TestReAligner::getConsensusTest() {
	std::list<AlignedFragment*> fragments = std::list<AlignedFragment*>();
	fragments.push_back(new AlignedFragment(*new Fragment(1, 3, "ACA"), *new FragmentAlignment(1, 3, 0, 0, 0)));
	fragments.push_back(new AlignedFragment(*new Fragment(1, 3, "TAT"), *new FragmentAlignment(1, 3, 0, 0, 0)));
	fragments.push_back(new AlignedFragment(*new Fragment(1, 3, "AAT"), *new FragmentAlignment(1, 3, 0, 0, 0)));
	Consensus consensus = ReAligner::getConsensus(*new Alignment(fragments));
	std::list<Metasymbol*> metasymbols = consensus.getPart(0, 3);
	vector<int> symbols[3];
	int counter = 0;
	for (std::list<Metasymbol*>::iterator itr = metasymbols.begin(); itr != metasymbols.end(); ++itr) {
		symbols[counter].clear();
		std::list<char> chars = (*itr)->getSymbols();
		for (std::list<char>::iterator it = chars.begin(); it != chars.end(); ++it) {
			symbols[counter].push_back(*it);
		}
		counter++;
	}
	CPPUNIT_ASSERT(symbols[0].size() == 1);
	CPPUNIT_ASSERT(symbols[1].size() == 1);
	CPPUNIT_ASSERT(symbols[2].size() == 1);
	CPPUNIT_ASSERT(symbols[0][0] == 'A');
	CPPUNIT_ASSERT(symbols[1][0] == 'A');
	CPPUNIT_ASSERT(symbols[2][0] == 'T');
}