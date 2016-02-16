#pragma once

#include <iostream>
#include <istream>
#include <string>
#include <fstream>
#include <list>
#include <map>

#include "FileReader.h"

class FragmentReader :
	public FileReader
{
	std::istream &inStream;
	std::map<int, Fragment*> fragments;
	std::map<std::string, int> stringIDtoID;
public:
	
	FragmentReader(std::istream &inputStream) :inStream(inputStream)
	{
	}
	~FragmentReader()
	{

	}

	/**
	 * Takes string that might have lowercase letters and makes them uppercase.
	 */
	std::string toUpperCase(std::string s) {
		for (int i = 0; i < (int)s.size(); ++i) {
			if (s[i] >= 'a' && s[i] <= 'z') {
				s[i] = s[i] - 'a' + 'A';
			}
		}
		return s;
	}

	/**
	 * Goes through input file line by line and reads all fragments, saves them to list and returns.
	 * If fragment is divided on multiple lines concates them together.
	 */
	std::map<int, Fragment*> GetAllFragments(){
		std::string currentSequence = "";

		int counter = 1;
		bool reading = false;
		while (!inStream.eof())
		{
			std::string sLine;
			std::getline(inStream, sLine);
			if (sLine[0] == '>' || sLine[0] == '@') {
				if (currentSequence != "" && fragments.size() > 0) {
					fragments[counter]->setLength(currentSequence.size());
					fragments[counter]->setSequence(toUpperCase(currentSequence));
					currentSequence = "";
					counter++;
				}
				//fragments->push_back(new Fragment(counter++,sLine.substr(1)));
				std::string name = "";
				char chown='\0';
				std::istringstream L(sLine);
				L >> chown; //remove >
				L >> name; //read till whitespace
				fragments[counter] = new Fragment(counter, name);
				stringIDtoID[name] = counter;
				reading = true;
			}
			else if (sLine[0] == '+') {
				reading = false;
			}
			else {
				if (reading == true) {
					currentSequence += sLine;
				}
			}
		}
		if (currentSequence != "") {
			fragments[counter]->setLength(currentSequence.size());
			fragments[counter]->setSequence(toUpperCase(currentSequence));
		}
		return fragments;
	}

	Fragment* get(int id) {
		return fragments[id];
	}

	Fragment* get(std::string name) {
		return fragments[stringIDtoID[name]];
	}
};

