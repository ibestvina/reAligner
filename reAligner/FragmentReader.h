#pragma once

#include "FileReader.h"
#include <iostream>
#include <string>
#include <fstream>

class FragmentReader :
	public FileReader
{
public:
	
	FragmentReader(std::string inFileName)
	{

	}
	~FragmentReader()
	{

	}
	std::list<Fragment> &GetAllFragments(){
		return *new std::list<Fragment>();
	}
};

