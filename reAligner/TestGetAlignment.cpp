#include <list>
#include <string>
#include <iostream>

#include "TestGetAlignment.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(TestGetAlignment);

void TestGetAlignment::removeDashes1(){
	std::string S("asdadsasdd");
	Fragment F (1, 10, S);
	FragmentAlignment FA (1, 10, 0, 9, 0);
	AlignedFragment AF(F, FA);

	AF.insertDashAt(2);
	AF.insertDashAt(0);
	AF.insertDashAt(10);

	AF.removeDashesFrontAndBack();
	CPPUNIT_ASSERT_EQUAL(AF.getSequence(), S);

}
void TestGetAlignment::removeDashes2(){

}

void TestGetAlignment::protoTest(std::string readSeq, int readOff, std::string consSeq, int delta, int expectedOff, std::string expectedRead)
{
	int readLen = readSeq.length();

	Fragment &fragment = *new Fragment(0, readLen, readSeq);
	FragmentAlignment &fragAlign = *new FragmentAlignment(0, readLen, 0, readLen, readOff);
	AlignedFragment &read = *new AlignedFragment(fragment, fragAlign);

	Consensus *consensus = new Consensus(0);
	for (int i = 0; i < consSeq.length(); i++) {
		consensus->addMetasymbol(new Metasymbol(string(1, consSeq[i])));
	}

	ReAligner::getAlignment(read, consensus, delta);


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
void TestGetAlignment::GetAlignment8()
{
	protoTest("BDEGH", 0, "ABCDEFGH", 4, 1, "B-DEGH");
}
