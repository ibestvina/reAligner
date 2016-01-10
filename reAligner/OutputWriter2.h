#include "FileReader.h"
#include "Alignment.h"
#include "Consensus.h"
#include "FileWriter.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>

class OutputWriter2
{

public:
	// NAPOMENA:
	//		prije zapisivanja, fileNameu dodati .fasta/.gfa
	//		funkciji se salje samo ime fileova, bez ekstenzije, kako bi se u outputConsensusAll funkciji moglo imenima dodati N/B/F prije ekstenzije


	/*
	* If there are multiple symbols writes n;
	*/
	static void outputConsensusWithN(std::list<Consensus&> consensusList, std::string path, std::string fileName);

	/*
	* If there are multiple symbols writes them inside of []
	*/
	static void outputConsensusWithBrackets(std::list<Consensus&> consensusList, std::string path, std::string fileName);

	/*
	* If there are multiple symbols writes first one.
	*/
	static void outputConsensusWithFirstSymbol(std::list<Consensus&> consensusList, std::string path, std::string fileName);

	
	static void outputGFA(Alignment& alignment, std::string path, std::string fileName);

	static void outputConsensusAll(std::list<Consensus&> consensusList, std::string path, std::string fileName) {
		outputConsensusWithN(consensusList, path, fileName + "N");
		outputConsensusWithBrackets(consensusList, path, fileName + "B");
		outputConsensusWithFirstSymbol(consensusList, path, fileName + "F");
	}
};
