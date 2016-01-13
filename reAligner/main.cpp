//#define TESTING

#ifdef TESTING
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#endif //TESTING

#include <iostream>
#include <string>
#include <list>
#include <chrono>

#include "Reader.h"
#include "OutputWriter.h"
#include "ReAligner.h"
#include "Alignment.h"
#include "Consensus.h"


int main(int argc, char *argv[])
{
#ifdef TESTING


	std::cout << "Start testing..." << std::endl;
	// Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);

	// Change the default outputter to a compiler error format outputter
	runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),
		std::cerr));
	// Run the tests.
	bool wasSucessful = runner.run();

	std::cin.get();

	// Return error code 1 if the one of test failed.

	return wasSucessful ? 0 : 1;
#else  //not TESTING

	// Command line arguments:
	//<fasta input> <mhap input> <epsilon value> <max number of iterations> <output directory> <output filename>

	if (argc != 7) {
		std::cout << "Wrong number of arguments" << std::endl;
		return 0;
	}

	// parse command line input
	std::string fasta(argv[1]);
	std::string mhap(argv[2]);
	double epsilon = std::stod(std::string(argv[3]));
	int maxIters = std::stoi(std::string(argv[4]));
	std::string outDir(argv[5]);
	std::string outFile(argv[6]);
	std::cout << "Fasta input: " << fasta << std::endl << "Mhap input: " << mhap << std::endl;
	std::cout << "Epsilon: " << epsilon << std::endl << "Max iterations: " << maxIters << std::endl;
	std::cout << "Output: " << outDir << outFile << "~" << std::endl;


	// read input files
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	Reader reader = *new Reader(fasta, mhap);
	std::list<Alignment*> alignments = reader.getAlignment();
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	// realign initial alignments
	std::list<Consensus*> consensusesBefore;
	std::list<Consensus*> consensusesAfter;
	int iter = 1;
	for (Alignment* alignment : alignments) {
		std::cout << std::endl << "--- Realigning alignment component " << iter << " ---" << std::endl;
		consensusesBefore.push_back(ReAligner::getConsensus(alignment));
		consensusesAfter.push_back(ReAligner::reAlign(*alignment, epsilon, maxIters));
		iter++;
	}
	std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();

	// output times
	auto readTime = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	auto doTime = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();
	std::cout << std::endl << "TIME READ: " << (float)readTime / 1000000.0 << std::endl;
	std::cout << "TIME DO: " << (float)doTime / 1000000.0 << std::endl;

	// output new consensuses
	OutputWriter::outputConsensusConcat(consensusesBefore, outDir, outFile + "_initial");
	OutputWriter::outputConsensusConcat(consensusesAfter, outDir, outFile);
	OutputWriter::outputConsensusAll(consensusesAfter, outDir, outFile);

#endif // TESTING
	return 0;
}