#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <fstream>
#include <stdexcept>
#include "GFAReader.h"
#include "Reader.h"

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
void TestLayoutReader::GetAllFragmentLayouts2(){
	std::stringstream input;
	input << "1 2 87.83225 206 0 69 1693 1704 0 1208 2831 5871" << std::endl <<
			 "1 3 85.08692 163 0 16 1041 1704 0 67 1088 2935" << std::endl <<
			 "1 4 87.11507 159 0 455 1678 1704 0 0 1225 1862";
	LayoutReader *LR = new LayoutReader(input);

	//std::list<Overlap*> *O = LR->readAllOverlaps();
	
	std::map<int, std::map<int, FragmentAlignment*>*> alignemnts = LR->GetAllFragmentLayouts();
	std::map<int, FragmentAlignment*> alignemnt = *(alignemnts[0]);
	//std::cout << "out" << std::endl;
	CPPUNIT_ASSERT_EQUAL(alignemnt[1]->getId(), 1);
	CPPUNIT_ASSERT_EQUAL(alignemnt[2]->getId(), 2);
	CPPUNIT_ASSERT_EQUAL(alignemnt[3]->getId(), 3);
	CPPUNIT_ASSERT_EQUAL(alignemnt[4]->getId(), 4);
	CPPUNIT_ASSERT_EQUAL(alignemnt[1]->getOffset(), 1139);
	CPPUNIT_ASSERT_EQUAL(alignemnt[2]->getOffset(), 0);
	CPPUNIT_ASSERT_EQUAL(alignemnt[3]->getOffset(), 1088);
	CPPUNIT_ASSERT_EQUAL(alignemnt[4]->getOffset(), 1594);
	CPPUNIT_ASSERT_EQUAL(alignemnt[1]->getEnd(), 1704);
	CPPUNIT_ASSERT_EQUAL(alignemnt[2]->getEnd(), 5871);
	CPPUNIT_ASSERT_EQUAL(alignemnt[3]->getEnd(), 2935);
	CPPUNIT_ASSERT_EQUAL(alignemnt[4]->getEnd(), 1862);

}
void TestLayoutReader::GetAllFragmentLayouts3(){
	std::stringstream input;
	input << "1 2 87.83225 206 0 69 1693 1704 0 1208 2831 5871" << std::endl <<
		"2 3 85.08692 163 0 16 1041 5871 0 67 1088 2935" << std::endl <<
		"1 4 87.11507 159 0 455 1678 1704 0 0 1225 1862";
	LayoutReader *LR = new LayoutReader(input);

	//std::list<Overlap*> *O = LR->readAllOverlaps();
	std::map<int, std::map<int, FragmentAlignment*>*> alignemnts = LR->GetAllFragmentLayouts();
	std::map<int, FragmentAlignment*> alignemnt = *(alignemnts[0]);
	//std::cout << "out" << std::endl;
	CPPUNIT_ASSERT_EQUAL(alignemnt[1]->getId(), 1);
	CPPUNIT_ASSERT_EQUAL(alignemnt[2]->getId(), 2);
	CPPUNIT_ASSERT_EQUAL(alignemnt[3]->getId(), 3);
	CPPUNIT_ASSERT_EQUAL(alignemnt[4]->getId(), 4);
	CPPUNIT_ASSERT_EQUAL(alignemnt[1]->getOffset(), 1190);
	CPPUNIT_ASSERT_EQUAL(alignemnt[2]->getOffset(), 51);
	CPPUNIT_ASSERT_EQUAL(alignemnt[3]->getOffset(), 0);
	CPPUNIT_ASSERT_EQUAL(alignemnt[4]->getOffset(), 1645);
	CPPUNIT_ASSERT_EQUAL(alignemnt[1]->getEnd(), 1704);
	CPPUNIT_ASSERT_EQUAL(alignemnt[2]->getEnd(), 5871);
	CPPUNIT_ASSERT_EQUAL(alignemnt[3]->getEnd(), 2935);
	CPPUNIT_ASSERT_EQUAL(alignemnt[4]->getEnd(), 1862);
}
void TestLayoutReader::Count1(){
	std::list<int> lst;
	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(3);
	lst.push_back(4);
	CPPUNIT_ASSERT(LayoutReader::contains<int>(lst, 1));
	CPPUNIT_ASSERT(LayoutReader::contains<int>(lst, 2));
	CPPUNIT_ASSERT(LayoutReader::contains<int>(lst, 4));
	CPPUNIT_ASSERT(!LayoutReader::contains<int>(lst, 5));

}
void TestLayoutReader::GetLayoutFromFile(){
	std::ifstream file;
	file.open("..\\samples\\synthetic500\\500_align.mhap");
	if (!file)
		throw std::runtime_error("Error reading file!");
	LayoutReader LR(file);
	std::map<int, std::map<int, FragmentAlignment*>*> FL = LR.GetAllFragmentLayouts();
	file.close();

}
void TestLayoutReader::GetAllFragmentLayouts4(){

	std::stringstream input;
	input << "1 2 87.83225 206 0 69 1693 1704 1 1208 2831 5871" << std::endl <<
		"2 3 85.08692 163 0 16 1041 5871 0 67 1088 2935" << std::endl <<
		"1 4 87.11507 159 0 455 1678 1704 1 0 1225 1862";
	LayoutReader *LR = new LayoutReader(input);

	//std::list<Overlap*> *O = LR->readAllOverlaps();
	std::map<int, std::map<int, FragmentAlignment*>*> alignemnts = LR->GetAllFragmentLayouts();
	std::map<int, FragmentAlignment*> alignemnt = *(alignemnts[0]);
	//std::cout << "out" << std::endl;
	CPPUNIT_ASSERT_EQUAL(alignemnt[1]->getId(), 1);
	CPPUNIT_ASSERT_EQUAL(alignemnt[2]->getId(), 2);
	CPPUNIT_ASSERT_EQUAL(alignemnt[3]->getId(), 3);
	CPPUNIT_ASSERT_EQUAL(alignemnt[4]->getId(), 4);
	CPPUNIT_ASSERT_EQUAL(alignemnt[1]->getOffset(), 3022);
	CPPUNIT_ASSERT_EQUAL(alignemnt[2]->getOffset(), 51);
	CPPUNIT_ASSERT_EQUAL(alignemnt[3]->getOffset(), 0);
	CPPUNIT_ASSERT_EQUAL(alignemnt[4]->getOffset(), 2841);
	CPPUNIT_ASSERT_EQUAL(alignemnt[1]->getEnd(), 1704);

}
void TestLayoutReader::GFATest()
{
	std::stringstream input;
	input << "S	utg000001l	GCCTTCAATCGCCAGAATCGCGAATGATGAAGCGGTTAGTATGCAGCCGTCTATTGAGTGGAAGTGAGTATGAGTACC" << std::endl <<
		"a	utg000001l	0	channel_257_read_10_twodirections:22-14264	+	2458"<<std::endl<<
		"a	utg000001l	2458	channel_497_read_15_twodirections:21 - 11715 + 1012"<<std::endl<<
		"a	utg000001l	3470	channel_220_read_11_twodirections : 18 - 17974 + 3994"<<std::endl<<
		"a	utg000001l	7464	channel_175_read_0_twodirections : 32 - 14935 - 298"<<std::endl<<
		"a	utg000001l	7762	channel_307_read_3_twodirections : 51 - 14631 + 14581"<<std::endl<<
		"x	utg000001l	22343	5	0	0	channel_257_read_10_twodirections : 22 - 14264 + channel_307_read_3_twodirections : 51 - 14631 - ";
	GFAReader gfa(input);
	gfa.GetFragmentAlignments();
}
void TestLayoutReader::GFATest2()
{
	Reader R("../samples/testGFA/lambda_ont_reads.fasta","../samples/testGFA/lambda_ont_layout.gfa");
	std::list<Alignment*> L = R.getAlignment();
}
void TestLayoutReader::GFATest3()
{
	Reader R("../samples/testGFA/lambda_ont_reads.fasta", "../samples/testGFA/lambda_ont_layout.gfa", "../samples/testGFA/lambda_ont_overlaps.mhap");
	std::list<Alignment*> L = R.getAlignment();
}
void TestLayoutReader::NewMHAPTest(){
	std::stringstream input;
	input << "2 1 0.410281 1287 0 70 17597 18315 1 4224832 4242927 4830022"<<std::endl<<
		"6 1 0.447153 410 0 304 4817 5046 0 1621705 1626251 4830022" << std::endl <<
		"9 1 0.203224 537 0 2138 18952 19456 1 252410 271682 4830022";
	LayoutReader LR(input);
	std::map<int, FragmentAlignment*> LAY= LR.GetFragmentLayout();
	LAY.empty();
}