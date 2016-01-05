#include "TestGetAlignment.h"
#include <string>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(TestGetAlignment);

void TestGetAlignment::protoTest(std::string readSeq, int readOff, std::string consSeq, double eps, int expectedOff, std::string expectedRead)
{
	int readLen = readSeq.length();

	Fragment &fragment = *new Fragment(0, readLen, readSeq);
	FragmentAlignment &fragAlign = *new FragmentAlignment(0, readLen, 0, readLen, readOff);
	AlignedFragment &read = *new AlignedFragment(fragment, fragAlign);

	Consensus &consensus = *new Consensus(0);
	for (int i = 0; i < consSeq.length(); i++) {
		consensus.addMetasymbol(new Metasymbol(string(1, consSeq[i])));
	}

	ReAligner::getAlignment(read, consensus, eps);


	CPPUNIT_ASSERT_EQUAL(expectedOff, read.getOffset());
	CPPUNIT_ASSERT_EQUAL(expectedRead, read.getSequence());
}

void TestGetAlignment::GetAlignment1()
{	
	protoTest("AAAAAAAAAA", 0, "AAAAAAAAAA", 4, 0, "AAAAAAAAAA");
}
void TestGetAlignment::GetAlignment2()
{
	protoTest("ABCDE", 0, "XABCDE", 4, 1, "ABCDE");
}
void TestGetAlignment::GetAlignment3()
{
	protoTest("ABCDE", 0, "XABXCDE", 4, 1, "AB-CDE");
}
void TestGetAlignment::GetAlignment4()
{
	protoTest("ABCDE", 0, "A-BCDE", 4, 1, "ABCDE");
}
void TestGetAlignment::GetAlignment5()
{
	protoTest("ACE", 0, "ABCDE", 4, 0, "A-C-E");
}
void TestGetAlignment::GetAlignment6()
{
	protoTest("BDEGH", 0, "ABCDEFGH", 10, 1, "B-DE-GH");
}
void TestGetAlignment::GetAlignment7()
{
	protoTest("BDEGH", 0, "ABCDEFGH", 4, 1, "B-DEGH");
}
