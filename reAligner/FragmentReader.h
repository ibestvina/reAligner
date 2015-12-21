#pragma once

#include "FileReader.h"
#include <iostream>
#include <string>
#include <fstream>

class FragmentReader :
	public FileReader
{
	std::istream &inStream;
public:
	
	FragmentReader(std::istream &inputStream) :inStream(inputStream)
	{

	}
	~FragmentReader()
	{

	}
	std::list<Fragment*> &GetAllFragments(){
		return *new std::list<Fragment*>();
	}
};

