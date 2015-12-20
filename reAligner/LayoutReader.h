#pragma once
#include "FileReader.h"
#include "Overlap.h"
#include "AlignedFragment.h"

#include <fstream>
#include <iostream>

class LayoutReader :
	public FileReader
{
private:
	std::list<Overlap>	Overlaps;
	std::ifstream		fileStream;

public:
	LayoutReader(std::string inFileName)
	{

	}
	~LayoutReader()
	{

	}

	std::list<FragmentAlignment> &GetAllFragmentLayouts(std::ifstream inFile)
	{
		return *new std::list<FragmentAlignment>();
	}

private:
	std::list<FragmentAlignment> &generateFragmentAlignments()
	{
		return *new std::list<FragmentAlignment>();
	}

	void readAllOverlaps()
	{

	}

};

