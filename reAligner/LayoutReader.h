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
		readAllOverlaps();
		return *new std::list<FragmentAlignment*>();
	}
	std::list<Overlap*> *readAllOverlaps()
	{
		Overlaps = new std::list<Overlap*>();

		while (!inputStream.eof())
		{
			std::string sLine;
			std::getline(inputStream, sLine);
			if (sLine == "")
				continue;
			std::istringstream line(sLine);

			int ID_A, ID_B, start_A, start_B, end_A, end_B,
				length_A, length_B, direction_A, direction_B, shared;
			float JaccardScore;

			line >> ID_A			>> ID_B		>>
					JaccardScore	>> shared	>>
					direction_A		>> start_A  >>
					end_A			>> length_A >>
					direction_B		>> start_B  >>
					end_B			>> length_B;
			
			Overlaps->push_back(
				new Overlap(ID_A, ID_B, JaccardScore, shared,
				direction_A, start_A, end_A, length_A,
				direction_B, start_B, end_B, length_B));
		}
		return Overlaps;
	}
private:
	std::list<FragmentAlignment*> &generateFragmentAlignments()
	{
		return *new std::list<FragmentAlignment*>();
	}

	

};

