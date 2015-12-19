#pragma once

#include <string>
#include <list>

#include "Fragment.h"
#include "AlignedFragment.h"

class FileReader
{
public:
	std::list<Fragment> &GetAllFragments(std::string inFile);
	std::list<AlignedFragment> &GetAllAlignments(std::string inFile, std::list<Fragment> fragments);
	FileReader();
	~FileReader();
private:
	int StringToInteger(std::string &toBeFormatted);
};

