#pragma once
#include <cppunit/extensions/HelperMacros.h>

#include "FragmentReader.h"


class TestFragmentReader : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestFragmentReader);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testGetAllFragments);
	CPPUNIT_TEST(testGetAllFragmentsQ);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testConstructor();
	void testGetAllFragments();
	void testGetAllFragmentsQ();
};

