#include "FileReader.h"
#include "Alignment.h"
#include "Consensus.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class GFAWriter :
	public GFAWriter
{
	std::istream &outStream;
	Alignment alignment;
	Consensus consensus;
public:

	GFAWriter(std::istream &outputStream, Alignment alignment, Consensus consensus) : outStream(outputStream), alignment(alignment), consensus(consensus)
	{		

	}
	~GFAWriter()
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
		for (i = 0; i * 60 < (int)s.size(); ++i) {
			for (int j = 0; i * 60 + j < (int)s.size(); ++j) {
				ss += "-";
				ss[(int)ss.size() - 1] = s[i * 60 + j];
			}
			ret.push_back(ss);
			ss = "";
		}
		return ret;
	}

	vector<string> getOutput(bool withN) {
		std::list<Metasymbol*> metasymbols = consensus.getMetasymbols();
		string ret = "";
		for (std::list<Metasymbol*>::iterator itr = metasymbols.begin(); itr != metasymbols.end(); ++itr) {
			vector<string> chars = getVector(*itr);
			if (chars.size() == 1) {
				ret += chars[0]
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
				if (withN) {
					ret += "n"
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

	void outputGFAWithN() {
		ofstream file;
		file.open("GFAWithN.gfa");
		file << consensus.getId();
		vector<string> rows = getOutput(true);
		for (int i = 0; i < (int)rows.size(); ++i) {
			file << rows[i];
		}
		file.close();
	}

	void outputGFAwithBrackets() {
		vector<string> rows = getOutput(false);
		ofstream file;
		file.open("GFAWithBrackets.gfa");
		file << consensus.getId();
		vector<string> rows = getOutput(true);
		for (int i = 0; i < (int)rows.size(); ++i) {
			file << rows[i];
		}
		file.close();
	}


};
