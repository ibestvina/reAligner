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

	std::list<Fragment*> &GetAllFragments(){
		std::string currentSequence = "";
		while (!inStream.eof())
		{
			std::string sLine;
			std::getline(inStream, sLine);
			if (sLine[0] == '>') {
				if (currentSequence != "" && fragments->size() > 0) {
					fragments->back()->setLength(currentSequence.size());
					fragments->back()->setSequence(currentSequence);
					currentSequence = "";
				}
				fragments->push_back(new Fragment(StringToInteger(sLine)));
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

