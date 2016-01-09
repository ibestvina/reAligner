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

	//*****************************************************************************************
	// Method:    GetAllFragmentLayouts
	// FullName:  LayoutReader::GetAllFragmentLayouts
	// Access:    public 
	// Returns:   std::map<int,FragmentAlignment*> &
	// Qualifier:
	// Description: istream is fetched via constructor and this function returns pure alignment
	//*****************************************************************************************
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
			float sharedH;
			if (sLine == "")
				continue;
			std::istringstream line(sLine);

			int ID_A, ID_B, start_A, start_B, end_A, end_B,
				length_A, length_B, direction_A, direction_B, shared;
			float JaccardScore;

			line >> ID_A			>> ID_B		>>
					JaccardScore	>> sharedH	>>
					direction_A		>> start_A  >>
					end_A			>> length_A >>
					direction_B		>> start_B  >>
					end_B			>> length_B;
			
			shared = (int)sharedH;
			
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

	//********************************************************************************
	// Method:    generateFragmentAlignments
	// FullName:  LayoutReader::generateFragmentAlignments
	// Access:    private 
	// Returns:   std::map<int,FragmentAlignment*> &
	// Qualifier:
	// Description: Reads out overlaps and calculates offsets, start and end indexes
	//********************************************************************************
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
				//Add first fragments to Alignment Matrix when B fragment id more left then A fragment
				if (overlap->getDirection_A() == 0 && overlap->getDirection_B() == 0 &&
					overlap->getStart_A() <= overlap->getStart_B())
				{
					(*FragmentAlignments)[overlap->getID_B()] = 
						new FragmentAlignment(overlap->getID_B(), overlap->getLength_B(), 0, overlap->getLength_B(), 0);
					(*FragmentAlignments)[overlap->getID_A()] =
						new FragmentAlignment(overlap->getID_A(), overlap->getLength_A(), 
						0, overlap->getLength_A(), 
						overlap->getStart_B() - overlap->getStart_A());
				}
				//Add first fragments to Alignment Matrix when A fragment id more left then B fragment
				else if (overlap->getDirection_A() == 0 && overlap->getDirection_B() == 0 &&
					overlap->getStart_A() > overlap->getStart_B())
				{
					(*FragmentAlignments)[overlap->getID_A()] =
						new FragmentAlignment(overlap->getID_A(), overlap->getLength_A(), 0, overlap->getLength_A(), 0);
					(*FragmentAlignments)[overlap->getID_B()] =
						new FragmentAlignment(overlap->getID_B(), overlap->getLength_B(),
						0, overlap->getLength_B(), 
						overlap->getStart_A() - overlap->getStart_B());
				}
				//When B direction is rc and B fragment is more left
				else if (overlap->getDirection_A() == 0 && overlap->getDirection_B() == 1 &&
					overlap->getStart_A() <= overlap->getLength_B() - overlap->getEnd_B())
				{
					(*FragmentAlignments)[overlap->getID_B()] =
						new FragmentAlignment(overlap->getID_B(), overlap->getLength_B(), overlap->getLength_B(), 0, 0);
					(*FragmentAlignments)[overlap->getID_A()] =
						new FragmentAlignment(overlap->getID_A(), overlap->getLength_A(),
						0, overlap->getLength_A(),
						overlap->getLength_B() - overlap->getEnd_B() - overlap->getStart_A());
				}
				//When B direction is rc and A fragment is more left
				else if (overlap->getDirection_A() == 0 && overlap->getDirection_B() == 1 &&
					overlap->getStart_A() > overlap->getLength_B() - overlap->getEnd_B())
				{
					(*FragmentAlignments)[overlap->getID_A()] =
						new FragmentAlignment(overlap->getID_A(), overlap->getLength_A(), 0, overlap->getLength_A(), 0);
					(*FragmentAlignments)[overlap->getID_B()] =
						new FragmentAlignment(overlap->getID_B(), overlap->getLength_B(),
						overlap->getLength_B(), 0,
						overlap->getStart_A() - (overlap->getLength_B() - overlap->getEnd_B()));
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
						/*if (overlapToRemove != nullptr){
							Overlaps->remove(overlapToRemove);
							overlapToRemove = nullptr;
						}
						if (findA && findB){
							overlapToRemove = O;
							continue;
						}*/
						split_matrix = false;
						overlap = O;
						Overlaps->remove(O);
						break;
					}
				}
			//If it does not exist in added indexes throw new exception
				if (split_matrix) {
					std::cout << "Matrix is split" << std::endl;
					throw new std::exception("Matrix is split");
				}
				int startPos, endPos, index, length, offset;
			//if matrix is not split use found overlap and position it
				if (overlap->getDirection_A() == 0 && overlap->getDirection_B() == 0)
				{
					//if index A exist add indexB
					//if index B exist add indexA
					if (contains<int>(AlignedIndexes, overlap->getID_A()))
					{
						offset		= (*FragmentAlignments)[overlap->getID_A()]->getOffset() - (overlap->getStart_B() - overlap->getStart_A());
						startPos	= 0;
						endPos		= overlap->getLength_B();
						index		= overlap->getID_B();
						length		= overlap->getLength_B();
					}
					else
					{
						offset		= (*FragmentAlignments)[overlap->getID_B()]->getOffset() - (overlap->getStart_A() - overlap->getStart_B());
						startPos	= 0;
						endPos		= overlap->getLength_A();
						index		= overlap->getID_A();
						length		= overlap->getLength_A();
					}
				}
				else if (overlap->getDirection_A() == 0 && overlap->getDirection_B() == 1)
				{
					if (contains<int>(AlignedIndexes, overlap->getID_A()))
					{
						offset = (*FragmentAlignments)[overlap->getID_A()]->getOffset() -
							((overlap->getLength_B() - 1 - overlap->getEnd_B()) - overlap->getStart_A());
						startPos = overlap->getLength_B();
						endPos = 0;
						index = overlap->getID_B();
						length = overlap->getLength_B();
					}
					else
					{
						offset = (*FragmentAlignments)[overlap->getID_B()]->getOffset() -
							(overlap->getStart_A() - (overlap->getLength_B() - 1 - overlap->getEnd_B()));
						startPos = 0;
						endPos = overlap->getLength_A();
						index = overlap->getID_A();
						length = overlap->getLength_A();
					}
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
				
				//if offset is negative, it means it is most left
				//so we have to move everything to right
				if (offset < 0)
				{
					for (auto &fragmentAlignment : *FragmentAlignments)
					{
						fragmentAlignment.second->setOffset(fragmentAlignment.second->getOffset() - offset);
					}
					(*FragmentAlignments)[index] = new FragmentAlignment(index, length, startPos, endPos, 0);
				}
				else (*FragmentAlignments)[index] = new FragmentAlignment(index, length, startPos, endPos, offset);
			}		
		}
		int minOffset = -1;
		for (auto &fragmentAlignment : *FragmentAlignments)
		{
			if (fragmentAlignment.second->getOffset() < minOffset || minOffset==-1)
				minOffset = fragmentAlignment.second->getOffset();
		}
		for (auto &fragmentAlignment : *FragmentAlignments)
		{
			fragmentAlignment.second->setOffset(fragmentAlignment.second->getOffset() - minOffset);
		}

		return *FragmentAlignments;
	}

	

};

