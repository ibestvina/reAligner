#include "FileReader.h"
#include "Alignment.h"
#include "Consensus.h"
#include "FileWriter.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class OutputWriter : public FileWriter
{
	
public:
	OutputWriter() {

	}
	~OutputWriter()
	{

	}
	
	/**
	 * Receives metasymbol and returns vector of symbols inside of that metasymbol.
	 */
	static vector<string> getVector(Metasymbol* metasymbol) {
		std::list<char> row = metasymbol->getSymbols();
		vector<string> ret; ret.clear();
		string tmp = "-";
		for (std::list<char>::iterator itr = row.begin(); itr != row.end(); ++itr) {
			tmp[0] = *itr;
			ret.push_back(tmp);
		}
		return ret;
	}

	/**
	 * Divides string s into chunks of size 60.
	 */
	static vector<string> getRows(string s) {
		vector<string> ret;
		for (int i = 0; i < (int)s.size(); i += 60) {
			if (i + 60 <= (int)s.size()) {
				ret.push_back(s.substr(i, 60));
			}
			else {
				ret.push_back(s.substr(i));
			}
		}
		return ret;
	}

	/**
	 * Returns output for consensus depending on version
	 *    if version == 0 outputs n in place of multiple symbols
	 *    if version == 1 outputs multiple symbols inside of []
	 *    if version == 2 outputs first one if there are multiple symbol
	 */
	static vector<string> getOutput(Consensus* consensus, int version) {
		std::list<Metasymbol*> metasymbols = consensus->getMetasymbols();
		string ret = "";
		for (std::list<Metasymbol*>::iterator itr = metasymbols.begin(); itr != metasymbols.end(); ++itr) {
			vector<string> chars = getVector(*itr);
			if (chars.size() == 1) {
				ret += chars[0];
			}
			else if (chars.size() == 2 && (chars[0] == "-" || chars[1] == "-")) {
				if (chars[0] == "-") {
					ret += chars[1];
				}
				else {
					ret += chars[0];
				}
			}
			else {
				if (version == 0) {
					ret += "n";
				}
				else if (version == 2) {
					ret += chars[0];
				}
				else {
					ret += "[";
					for (int i = 0; i < (int)chars.size(); ++i) {
						ret += chars[i];
					}
					ret += "]";
				}
			}
		}
		return getRows(ret);
	}

	/*
	 * Outputs consensus with different versions depending on parameter version:
	 *    if version == 0 outputs n in place of multiple symbols
	 *    if version == 1 outputs multiple symbols inside of []
	 *    if version == 2 outputs first one if there are multiple symbols
	 */
	static void outputConsensus(std::list<Consensus*> consensusList, std::string path, std::string fileName, int version) {
		ofstream file;
		file.open(path + fileName);
		for (std::list<Consensus*>::iterator itr = consensusList.begin(); itr != consensusList.end(); ++itr) {
			Consensus* consensus = *itr;
			file << ">" << consensus->getId() << endl;
			vector<string> rows = getOutput(consensus, version);
			for (int i = 0; i < (int)rows.size(); ++i) {
				file << rows[i] << endl;
			}
		}
		file.close();
	}

	/**
	 * Outputs all three versions of consensus into appropriate files.
	 */
	static void outputConsensusAll(std::list<Consensus*> consensusList, std::string path, std::string fileName) {
		std::string consensusExt = ".fasta";
		std::string versionNames[3] = { "N", "B", "F" };
		for (int i = 0; i < 3; ++i) {
			outputConsensus(consensusList, path, fileName + versionNames[i] + consensusExt, i);
		}
	}

	// Output concatenated sequences as one fragment, taking first symbol from metasymbol.
	static void outputConsensusConcat(std::list<Consensus*> consensusList, std::string path, std::string fileName) {
		std::string concatSeq = "";
		for (Consensus* cons : consensusList) {
			concatSeq = concatSeq + cons->toStringFirst();
		}
		concatSeq.erase(std::remove(concatSeq.begin(), concatSeq.end(), '-'), concatSeq.end());
		ofstream file;
		file.open(path + fileName + "C.fasta");
		file << ">s0" << endl;
		file << concatSeq << endl;
	}

	/**
	 * Outputs alignment in GFA.
	 */
	static void outputGFA(Alignment& alignment, std::string path, std::string fileName) {
		ofstream file;
		file.open(path + fileName + ".gfa");
		std::list<AlignedFragment*> *fragments = alignment.getAllFragments();
		for (std::list<AlignedFragment*>::iterator itr = fragments->begin(); itr != fragments->end(); ++itr) {
			AlignedFragment* fragment = *itr;
			file << "a\t" << "comment\t";
			file << fragment->getId() << "\t" << fragment->getOffset() << "\t";
			file << fragment->getInputId() << ":";
			int start = fragment->getStart();
			int end = fragment->getEnd();
			if (start <= end) {
				file << start << "-" << end << "\t+\t";
			}
			else {
				file << end << "-" << start << "\t-\t";
			}
			file << fragment->getLength() << endl;
		}
		file.close();
	}
};
