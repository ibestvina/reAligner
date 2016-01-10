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
	//		funkciji se salje samo ime fileova, bez ekstenzije, kako bi se u outputConsensusAll funkciji moglo imenima dodati N/B/F/C prije ekstenzije


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

	/*
	* Concatenate all consensuses from list, write to "<path>/<fileName>C.fasta" as one fragment.
	*/
	static void outputConsensusFirstSymbolConcat(std::list<Consensus&> consensusList, std::string path, std::string fileName) {
		std::string sequence = "";
		for each (Consensus& cons in consensusList)
		{
			sequence = sequence + cons.toStringFirst();
		}
		// TODO
		// upisati sequence u "<path>/<fileName>C.fasta" kao jedan fragment
		
	}
	
	static void outputGFA(Alignment& alignment, std::string path, std::string fileName);

	static void outputConsensusAll(std::list<Consensus&> consensusList, std::string path, std::string fileName) {
		outputConsensusWithN(consensusList, path, fileName + "N");
		outputConsensusWithBrackets(consensusList, path, fileName + "B");
		outputConsensusWithFirstSymbol(consensusList, path, fileName + "F");
	}
};
