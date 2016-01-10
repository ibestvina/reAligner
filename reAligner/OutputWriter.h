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
	std::string folderPath;
	Alignment &alignment;
	Consensus &consensus;
public:

	
	OutputWriter(std::string folderPath, Alignment& alignment, Consensus& consensus) : folderPath(folderPath), alignment(alignment), consensus(consensus)
	{		

	}
	~OutputWriter()
	{

	}

	vector<string> getVector(Metasymbol* metasymbol) {
		std::list<char> row = metasymbol->getSymbols();
		vector<string> ret; ret.clear();
		string tmp = "-";
		for (std::list<char>::iterator itr = row.begin(); itr != row.end(); ++itr) {
			tmp[0] = *itr;
			ret.push_back(tmp);
		}
		return ret;
	}

	vector<string> getRows(string s) {
		string ss = "";
		vector<string> ret;
		for (int i = 0; i * 60 < (int)s.size(); ++i) {
			for (int j = 0; i * 60 + j < (int)s.size(); ++j) {
				ss += "-";
				ss[(int)ss.size() - 1] = s[i * 60 + j];
			}
			ret.push_back(ss);
			ss = "";
		}
		return ret;
	}

	vector<string> getOutput(int version) {
		std::list<Metasymbol*> metasymbols = consensus.getMetasymbols();
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
	* If there are multiple symbols writes n;
	*/
	void outputConsensusWithN() {
		ofstream file;
		file.open(folderPath + "consensusWithN.fasta");
		file << consensus.getId();
		vector<string> rows = getOutput(0);
		for (int i = 0; i < (int)rows.size(); ++i) {
			file << rows[i] << endl;
		}
		file.close();
	}

	/*
	* If there are multiple symbols writes them inside of []
	*/
	void outputConsensusWithBrackets() {
		ofstream file;
		file.open(folderPath + "consensusWithBrackets.fasta");
		file << consensus.getId();
		vector<string> rows = getOutput(1);
		for (int i = 0; i < (int)rows.size(); ++i) {
			file << rows[i] << endl;
		}
		file.close();
	}

	/*
	 * If there are multiple symbols writes first one.
	 */
	void outputConsensusWithFirstSymbol() {
		ofstream file;
		file.open(folderPath + "consensusOnlyFirst.fasta");
		file << consensus.getId();
		vector<string> rows = getOutput(2);
		for (int i = 0; i < (int)rows.size(); ++i) {
			file << rows[i] << endl;
		}
		file.close();
	}

	void outputGFA() {
		ofstream file;
		file.open(folderPath + "output.gfa");
		std::list<AlignedFragment*> fragments = alignment.getAllFragments();
		for (std::list<AlignedFragment*>::iterator itr = fragments.begin(); itr != fragments.end(); ++itr) {
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

	void outputAll() {
		outputConsensusWithN();
		outputConsensusWithBrackets();
		outputConsensusWithFirstSymbol();
		outputGFA();
	}
};
