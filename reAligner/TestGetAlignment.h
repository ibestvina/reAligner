#pragma once
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "ReAligner.h"

class TestGetAlignment : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestGetAlignment);
	CPPUNIT_TEST(removeDashes1);
	CPPUNIT_TEST(removeDashes2);
	CPPUNIT_TEST(GetAlignment1);
	CPPUNIT_TEST(GetAlignment2);
	CPPUNIT_TEST(GetAlignment3);
	CPPUNIT_TEST(GetAlignment4);
	CPPUNIT_TEST(GetAlignment5);
	CPPUNIT_TEST(GetAlignment6);
	CPPUNIT_TEST(GetAlignment7);
	CPPUNIT_TEST_SUITE_END();

public:

	void protoTest(std::string readSeq, int readOff, std::string consSeq, double eps, int expectedOff, std::string expectedRead);
	void removeDashes1();
	void removeDashes2();
	void GetAlignment1();
	void GetAlignment2();
	void GetAlignment3();
	void GetAlignment4();
	void GetAlignment5();
	void GetAlignment6();
	void GetAlignment7();

};

