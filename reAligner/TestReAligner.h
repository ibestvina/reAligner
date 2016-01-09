#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <exception>

#include "AlignedFragment.h"

class TestReAligner : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestReAligner);
	CPPUNIT_TEST(getConsensusTest);
	CPPUNIT_TEST(getConsensusMetasymbolTest);
	CPPUNIT_TEST(getColumnScoreTest);
	CPPUNIT_TEST(testRealign1);
	CPPUNIT_TEST(testRealign2);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();

	void getConsensusTest();
	void getConsensusMetasymbolTest();
	void getColumnScoreTest();

	void testRealign1();
	void testRealign2();
};