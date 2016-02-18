#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <fstream>

#include "TestReAligner.h"
#include "ReAligner.h"
#include "FragmentReader.h"
#include "LayoutReader.h"
#include "Reader.h"
#include "OutputWriter.h"
#include "ColumnCount.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(TestReAligner);

void TestReAligner::setUp(){}
void TestReAligner::tearDown(){}


std::string mySamplesPath = "../samples/";
//std::string mySamplesPath = "D:/Projects/bioinf/realigner/project/reAligner/samples/";
//std::string mySamplesPath = "C:/prog/bioinformatika/reAligner/samples/";
//std::string mySamplesPath = "../samples/";


std::vector<char> toVector(std::list<char> chars) {
	std::vector<char> ret; ret.clear();
	for (std::list<char>::iterator it = chars.begin(); it != chars.end(); ++it) {
		ret.push_back(*it);
	}
	return ret;
}

bool compareDouble(double a, double b) {
	if (abs(a - b) <= 0.0000001) {
		return true;
	}
	return false;
}
void TestReAligner::testRealign2()
{
	/*Fragment F1(1,18,std::string("CCTGGTACGTACACTTGT"));
	Fragment F2(2,20,"TCACGTATCCCTCTGTTAGA");
	Fragment F3(3,25,"GTACCCTCTGTTAGAAAGCTCACGT");
	Fragment F4(4,17,"CTCACTTAGTTCTCTGT");
	Fragment F5(5, 17, "TCACTTGTTCTGTGTAG");
	Fragment F6(6, 19, "TGTTCCGTGCTAGTAGCTA");
	FragmentAlignment FA1(1,18,0,17,0);
	FragmentAlignment FA2(2,20,0,24,5);
	FragmentAlignment FA3(3,25,0,33,9);
	FragmentAlignment FA4(4,17,0,43,27);
	FragmentAlignment FA5(5,17,0,44,28);
	FragmentAlignment FA6(6,19,0,51,33);
	AlignedFragment *AF1 = new AlignedFragment(F1, FA1);
	AlignedFragment *AF2 = new AlignedFragment(F2, FA2);
	AlignedFragment *AF3 = new AlignedFragment(F3, FA3);
	AlignedFragment *AF4 = new AlignedFragment(F4, FA4);
	AlignedFragment *AF5 = new AlignedFragment(F5, FA5);
	AlignedFragment *AF6 = new AlignedFragment(F6, FA6);
	std::list<AlignedFragment*> &AFL = *new std::list<AlignedFragment*>;
	AFL.push_back(AF1);
	AFL.push_back(AF2);
	AFL.push_back(AF3);
	AFL.push_back(AF4);
	AFL.push_back(AF5);
	AFL.push_back(AF6);
	Alignment& A = *new Alignment(AFL);
	Consensus* consBegin = ReAligner::getConsensus(&A);
	Consensus* cons = ReAligner::reAlign(A, 4, 10);
	std::cout << std::endl << cons->toStringFirst();*/

}
void TestReAligner::testRealign1()
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	//Reader reader = *new Reader(mySamplesPath + "synthetic500/500_2_frags.fasta", mySamplesPath + "synthetic500/500_2_align.mhap");
	//Reader reader = *new Reader(mySamplesPath + "ecoli/ecoli_frags.fasta", mySamplesPath + "ecoli/ecoli_align.mhap");
	//Reader reader = *new Reader(mySamplesPath + "synthetic5k/5k_frags.fasta", mySamplesPath + "synthetic5k/5k_align.mhap");
	//Reader reader = *new Reader(mySamplesPath + "testGFA/lambda_ont_reads.fasta", mySamplesPath + "testGFA/lambda_ont_layout.gfa");//, mySamplesPath + "testGFA/lambda_ont_overlaps.mhap");
	Reader reader = *new Reader(mySamplesPath + "ecoli/reads.fq", mySamplesPath + "ecoli/layout.gfa");//, mySamplesPath + "ecoli/overlaps.after_unitigger.mhap");

	std::list<Alignment*> alignments = reader.getAlignment();
	Alignment *alignment = NULL;
	int maxSize = 0;
	for (auto A : alignments)
		if (A->getSize() > maxSize)
		{
			alignment = A;
			maxSize = A->getSize();
		}
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	std::cout << "reading over" << std::endl;
	char* before2 = ReAligner::consensusToString2(alignment);
	std::cout << "writing to file" << std::endl;
	std::ofstream fb2;
	fb2.open(mySamplesPath + "before_cons_gfa.fasta");
	fb2 << ">s0" << std::endl << before2 << std::endl;
	fb2.close();
	char* before1 = ReAligner::consensusToString(alignment);
	std::cout << "writing to file2" << std::endl;
	std::ofstream fb1;
	fb1.open(mySamplesPath + "before_cons_maj.fasta");
	fb1 << ">s0" << std::endl << before1 << std::endl;
	fb1.close();

	std::cout << "write over" << std::endl;
	//std::cout << std::endl << c << std::endl;
	Consensus *consAfter = ReAligner::reAlign(alignment, 0.05, 3);


	std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();

	auto readTime = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
	auto doTime = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();
	std::cout << std::endl<<"TIME READ: " << (float)readTime/1000000.0 << std::endl;
	std::cout << "TIME DO: " << (float)doTime/1000000.0 << std::endl;

	std::cout << "sad ce ispisati" << endl;
	// TEST OUTPUT WRITER
	/*std::string outputTestPath = "C:/Users/Zrinka/Desktop/bioinf/";
	std::list<Consensus> cons = std::list<Consensus>();
	cons.push_back(*consAfter);
	OutputWriter::outputConsensusAll(cons, outputTestPath, "konsenzusi");
	OutputWriter::outputGFA(*alignment, outputTestPath, "gfa_output");*/
	
	char* after1 = ReAligner::consensusToString(alignment);
	std::cout << "writing to file2" << std::endl;
	std::ofstream fa1;
	fa1.open(mySamplesPath + "after_cons_maj.fasta");
	fa1 << ">s0" << std::endl << after1 << std::endl;
	fa1.close();
	char* after2 = ReAligner::consensusToString2(alignment);
	std::cout << "writing to file" << std::endl;
	std::ofstream fa2;
	fa2.open(mySamplesPath + "after_cons_gfa.fasta");
	fa2 << ">s0" << std::endl << after2 << std::endl;
	fa2.close();
	

	//std::cout << endl << ReAligner::consensusToString(alignment) << endl;
}
void TestReAligner::getConsensusTest() {
	/*std::list<AlignedFragment*> fragments = std::list<AlignedFragment*>();
	fragments.push_back(new AlignedFragment(*new Fragment(1, 3, "ACA"), *new FragmentAlignment(1, 3, 0, 0, 0)));
	fragments.push_back(new AlignedFragment(*new Fragment(1, 3, "TAT"), *new FragmentAlignment(1, 3, 0, 0, 0)));
	fragments.push_back(new AlignedFragment(*new Fragment(1, 3, "AAT"), *new FragmentAlignment(1, 3, 0, 0, 0)));
	Consensus *consensus = ReAligner::getConsensus(new Alignment(fragments));
	std::list<Metasymbol*> metasymbols = consensus->getPart(0, 3);
	std::vector<char> symbols[3];
	int counter = 0;
	for (std::list<Metasymbol*>::iterator itr = metasymbols.begin(); itr != metasymbols.end(); ++itr) {
		symbols[counter].clear();
		symbols[counter] = toVector((*itr)->getSymbols());
		counter++;
	}
	CPPUNIT_ASSERT(symbols[0].size() == 1);
	CPPUNIT_ASSERT(symbols[1].size() == 1);
	CPPUNIT_ASSERT(symbols[2].size() == 1);
	CPPUNIT_ASSERT(symbols[0][0] == 'A');
	CPPUNIT_ASSERT(symbols[1][0] == 'A');
	CPPUNIT_ASSERT(symbols[2][0] == 'T');*/
}

void TestReAligner::getConsensusMetasymbolTest() {
	std::list<char> column;
	column.push_back('T');
	column.push_back('A');
	column.push_back('C');
	column.push_back('A');
	std::vector<char> symbols = toVector(ReAligner::getConsensusMetasymbol(&column)->getSymbols());
	CPPUNIT_ASSERT(symbols.size() == 1);
	CPPUNIT_ASSERT(symbols[0] == 'A');

	column.push_back('T');
	symbols = toVector(ReAligner::getConsensusMetasymbol(&column)->getSymbols());
	CPPUNIT_ASSERT(symbols.size() == 2);
	CPPUNIT_ASSERT(symbols[0] == 'A');
	CPPUNIT_ASSERT(symbols[1] == 'T');
}

void TestReAligner::getColumnScoreTest() {
	std::list<char> column;
	column.push_back('T');
	column.push_back('A');
	column.push_back('C');
	column.push_back('A');
	Metasymbol* metasymbol = ReAligner::getConsensusMetasymbol(&column);
	double score = ReAligner::getColumnScore(&column, metasymbol);
	
	column.push_back('T');
	column.push_back('A');
	metasymbol = ReAligner::getConsensusMetasymbol(&column);
	score = ReAligner::getColumnScore(&column, metasymbol);
	CPPUNIT_ASSERT(compareDouble(3.0, score) == true);

	column.push_back('T');
	metasymbol = ReAligner::getConsensusMetasymbol(&column);
	score = ReAligner::getColumnScore(&column, metasymbol);
	CPPUNIT_ASSERT(compareDouble(1.0, score) == true);
}