#include "TestLayoutReader.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(TestLayoutReader);

void TestLayoutReader::setUp(){}
void TestLayoutReader::tearDown(){}

void TestLayoutReader::testConstructor(){}
void TestLayoutReader::GetAllFragmentLayouts1()
{	
	std::stringstream input;
	input << "155 11 87.83225 206 0 69 1693 1704 0 1208 2831 5871" << std::endl <<
		"155 15 85.08692 163 0 16 1041 1704 1 67 1088 2935" << std::endl <<
		"155 27 87.11507 159 0 455 1678 1704 0 0 1225 1862" << std::endl;
	LayoutReader *LR = new LayoutReader(input);

	std::list<Overlap*> *O = LR->readAllOverlaps();
	CPPUNIT_ASSERT_EQUAL((int)O->size(), 3);
	
}
void TestLayoutReader::GetAllFragmentLayouts2(){}
void TestLayoutReader::GetAllFragmentLayouts3(){}
void TestLayoutReader::GetAllFragmentLayouts4(){}
