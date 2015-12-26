#pragma once
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "LayoutReader.h"

class TestLayoutReader : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestLayoutReader);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(GetAllFragmentLayouts1);
	CPPUNIT_TEST(GetAllFragmentLayouts2);
	CPPUNIT_TEST(GetAllFragmentLayouts3);
	CPPUNIT_TEST(GetAllFragmentLayouts4);
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp();
	void tearDown();

	void testConstructor();
	void GetAllFragmentLayouts1();
	void GetAllFragmentLayouts2();
	void GetAllFragmentLayouts3();
	void GetAllFragmentLayouts4();
};

