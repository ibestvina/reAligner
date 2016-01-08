#pragma once

#include "FileReader.h"
#include <iostream>
#include <string>
#include <fstream>

class FragmentReader :
	public FileReader
{
	std::istream &inStream;
	std::list<Fragment*> *fragments = NULL;
public:
	
	FragmentReader(std::istream &inputStream) :inStream(inputStream)
	{
		fragments = new std::list<Fragment*>();

	}
	~FragmentReader()
	{

	}

	std::string toUpperCase(std::string s) {
		for (int i = 0; i < (int)s.size(); ++i) {
			if (s[i] >= 'a' && s[i] <= 'z') {
				s[i] = s[i] - 'a' + 'A';
			}
		}
		return s;
	}

	std::list<Fragment*> &GetAllFragments(){
		std::string currentSequence = "";
		int counter = 1;
		while (!inStream.eof())
		{
			std::string sLine;
			std::getline(inStream, sLine);
			if (sLine[0] == '>') {
				if (currentSequence != "" && fragments->size() > 0) {
					fragments->back()->setLength(currentSequence.size());
					fragments->back()->setSequence(toUpperCase(currentSequence));
					currentSequence = "";
				}
				fragments->push_back(new Fragment(counter++, sLine));
			}
			else {
				currentSequence += sLine;
			}
		}
		if (currentSequence != "") {
			fragments->back()->setLength(currentSequence.size());
			fragments->back()->setSequence(currentSequence);
		}
		/*
		// temp debug ispis
		for (std::list<Fragment*>::iterator itr = fragments->begin(); itr != fragments->end(); ++itr) {
			printf("%d %d %s\n", (*itr)->getId(), (*itr)->getLength(), (*itr)->getSequence().c_str());
		}
		*/
		return *fragments;
	}
};

