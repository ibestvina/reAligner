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

	std::map<int,FragmentAlignment*> &GetAllFragmentLayouts()
	{
		readAllOverlaps();
		return generateFragmentAlignments();
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
	template <typename T>
	static bool contains(std::list<T> &lst, T var)
	{
		return std::find(lst.begin(), lst.end(), var) != lst.end();
	}
private:
	std::map<int,FragmentAlignment*> &generateFragmentAlignments()
	{
		std::list<int> AlignedIndexes;
		std::map<int,FragmentAlignment*> *FragmentAlignments = new std::map<int,FragmentAlignment*>();
		while (!Overlaps->empty())
		{
			//Get any overlap if we have just started
			Overlap *overlap = NULL;
			if (AlignedIndexes.empty())
			{
				overlap = Overlaps->front();
				Overlaps->remove(overlap);
				//Add Fragments to Alignment Matrix
				if (overlap->getDirection_A() == 0 && overlap->getDirection_B() == 0 &&
					overlap->getStart_A() <= overlap->getStart_B())
				{
					(*FragmentAlignments)[overlap->getID_B()] = 
						new FragmentAlignment(overlap->getID_B(), overlap->getLength_B(), 0, overlap->getLength_B() - 1, 0);
					(*FragmentAlignments)[overlap->getID_A()] =
						new FragmentAlignment(overlap->getID_A(), overlap->getLength_A(), 
						overlap->getStart_B() - overlap->getStart_A(), 
						overlap->getLength_A() - 1 + overlap->getStart_B() - overlap->getStart_A(), 0);
				}
				else if (overlap->getDirection_A() == 0 && overlap->getDirection_B() == 0 &&
					overlap->getStart_A() > overlap->getStart_B())
				{
					(*FragmentAlignments)[overlap->getID_A()] =
						new FragmentAlignment(overlap->getID_A(), overlap->getLength_A(), 0, overlap->getLength_A() - 1, 0);
					(*FragmentAlignments)[overlap->getID_B()] =
						new FragmentAlignment(overlap->getID_B(), overlap->getLength_B(),
						overlap->getStart_A() - overlap->getStart_B(),
						overlap->getLength_B() - 1 + overlap->getStart_A() - overlap->getStart_B(), 0);
				}
				else if (overlap->getDirection_A() == 0 && overlap->getDirection_B() == 1 &&
					overlap->getStart_A() <= overlap->getLength_B() - overlap->getEnd_B())
				{
					throw new std::exception("not implemented yet");
				}
				else if (overlap->getDirection_A() == 0 && overlap->getDirection_B() == 1 &&
					overlap->getStart_A() > overlap->getLength_B() - overlap->getEnd_B())
				{
					throw new std::exception("not implemented yet");
				}
				//else if (overlap->getDirection_A() == 1 && overlap->getDirection_B() == 0 &&
				//	overlap->getLength_A() - overlap->getEnd_A() < overlap->getStart_B())
				//{
				//	throw new std::exception("not implemented yet");
				//}
				//else if (overlap->getDirection_A() == 1 && overlap->getDirection_B() == 0 &&
				//	overlap->getLength_A() - overlap->getEnd_A() > overlap->getStart_B())
				//{
				//	throw new std::exception("not implemented yet");
				//}
				//else if (overlap->getDirection_A() == 1 && overlap->getDirection_B() == 1 &&
				//	overlap->getLength_A() - overlap->getEnd_A() <  overlap->getLength_B() - overlap->getEnd_B())
				//{
				//	throw new std::exception("not implemented yet");
				//}
				//else if (overlap->getDirection_A() == 1 && overlap->getDirection_B() == 1 &&
				//	overlap->getLength_A() - overlap->getEnd_A() >  overlap->getLength_B() - overlap->getEnd_B())
				//{
				//	throw new std::exception("not implemented yet");
				//}
				else //Both have same index
				{
					throw new std::exception("Something went wrong!");
				}
				AlignedIndexes.push_back(overlap->getID_A());
				AlignedIndexes.push_back(overlap->getID_B());
			}
			//If we have not just started, get Overlap which one of indexes
			//exists in aligned_indexes
			else
			{

				bool split_matrix = true;
				for (Overlap* O : *Overlaps)
				{
					bool findA = std::find(AlignedIndexes.begin(), AlignedIndexes.end(), O->getID_A()) != AlignedIndexes.end();
					bool findB = std::find(AlignedIndexes.begin(), AlignedIndexes.end(), O->getID_B()) != AlignedIndexes.end();
					if (findA || findB)
					{
						split_matrix = false;
						overlap = O;
						Overlaps->remove(O);
						break;
					}
				}
			//If it does not exist in added indexes throw new exception
				if (split_matrix) throw new std::exception("Matrix is split");
				int startPos, endPos, index, length;
			//if matrix is not split use found overlap and position it
				if (overlap->getDirection_A() == 0 && overlap->getDirection_B() == 0)
				{
					//if index A exist add indexB
					//if index B exist add indexA
					if (contains<int>(AlignedIndexes, overlap->getID_A()))
					{
						startPos	= (*FragmentAlignments)[overlap->getID_A()]->getStart() - (overlap->getStart_B() - overlap->getStart_A());
						endPos = startPos + overlap->getLength_B() - 1;
						index = overlap->getID_B();
						length = overlap->getLength_B();
					}
					else
					{
						startPos = (*FragmentAlignments)[overlap->getID_B()]->getStart() - (overlap->getStart_A() - overlap->getStart_B());
						endPos = startPos + overlap->getLength_A() - 1;
						index = overlap->getID_A();
						length = overlap->getLength_A();
					}
				}
				else if (overlap->getDirection_A() == 0 && overlap->getDirection_B() == 1)
				{
					throw new std::exception("not implemented yet");
				}
				/*else if (overlap->getDirection_A() == 1 && overlap->getDirection_B() == 0)
				{
				throw new std::exception("not implemented yet");
				}
				else if (overlap->getDirection_A() == 1 && overlap->getDirection_B() == 1)
				{
				throw new std::exception("not implemented yet");
				}*/
				else
				{
					throw new std::exception("Read something wrong!");
				}

				//add index to AlignedIndexes
				if (contains<int>(AlignedIndexes, overlap->getID_A()))
					AlignedIndexes.push_back(overlap->getID_B());
				else AlignedIndexes.push_back(overlap->getID_A());
				
				//move everything
				if (startPos < 0)
				{
					for (auto &fragmentAlignment : *FragmentAlignments)
					{
						fragmentAlignment.second->setEnd(fragmentAlignment.second->getEnd() - startPos);
						fragmentAlignment.second->setStart(fragmentAlignment.second->getStart() - startPos);
					}
					(*FragmentAlignments)[index] = new FragmentAlignment(index, length, 0, endPos - startPos, 0);
				}
				else (*FragmentAlignments)[index] = new FragmentAlignment(index, length, startPos, endPos, 0);
			}		
		}
		//map to list
		return *FragmentAlignments;
	}

	

};

