#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "AlignedFragment.h"

class TestReAligner : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestReAligner);
	CPPUNIT_TEST(getConsensusTest);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();

	void getConsensusTest();
};