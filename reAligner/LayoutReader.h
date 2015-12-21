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
	std::list<Overlap*>	*Overlaps;
	std::istream		&inputStream;

public:
	LayoutReader(std::istream &inputStream) :inputStream(inputStream)
	{

	}
	~LayoutReader()
	{

	}

	std::list<FragmentAlignment*> &GetAllFragmentLayouts(std::istream inputStream)
	{
		return *new std::list<FragmentAlignment*>();
	}

private:
	std::list<FragmentAlignment*> &generateFragmentAlignments()
	{
		return *new std::list<FragmentAlignment*>();
	}

	void readAllOverlaps()
	{

	}

};

