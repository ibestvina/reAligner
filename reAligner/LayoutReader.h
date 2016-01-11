#pragma once

#include <fstream>
#include <iostream>
#include <istream>
#include <list>
#include <map>
#include <sstream>
#include <algorithm>

#include "FileReader.h"
#include "Overlap.h"
#include "AlignedFragment.h"


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
	std::map<int, std::map<int, FragmentAlignment*>*> &GetAllFragmentLayouts()
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
	std::map<int, std::map<int, FragmentAlignment*>*> &generateFragmentAlignments()
	{
		int debug = Overlaps->size(), debugStep = debug / 100, debugCount = 100;
		std::cout << "...." << std::endl;
		//map<alignemnt id, alignedIndexes>
		int alignmentId = 0;
		std::map<int, std::list<int>*> AlignedIndexes;
		AlignedIndexes[alignmentId] = new std::list<int>();
		std::map<int, std::map<int, FragmentAlignment*>*> *alignmentContainer = 
			new std::map<int, std::map<int, FragmentAlignment*>*>();
		//TODO map of maps of alignments
		std::map<int,FragmentAlignment*> *FragmentAlignments = new std::map<int,FragmentAlignment*>();
		//read until all overlaps are processed
		while (!Overlaps->empty())
		{
			//debug
			if (debugStep*debugCount > Overlaps->size())
				std::cout << debugCount-- << std::endl;
			//Get any overlap if we have just started
			Overlap *overlap = NULL;
			if (AlignedIndexes[alignmentId]->empty())
			{
				//TODO
				//select first overlap, find all with same id
				//find all with same ids, select one with highest jaccard score
				//remove them all
				overlap = Overlaps->front();

				overlap = getOverlapWithHighestJaccard(overlap->getID_A(), overlap->getID_B(), *Overlaps);
				
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
					throw std::runtime_error("Something went wrong!");
				}
				AlignedIndexes[alignmentId]->push_back(overlap->getID_A());
				AlignedIndexes[alignmentId]->push_back(overlap->getID_B());
			}
			//If we have not just started, get Overlap which one of indexes
			//exists in aligned_indexes
			else
			{

				bool split_matrix = true;
				bool alreadyPlaced = false;
				for (Overlap* O : *Overlaps)
				{
					bool findA = std::find(AlignedIndexes[alignmentId]->begin(), AlignedIndexes[alignmentId]->end(), O->getID_A()) != AlignedIndexes[alignmentId]->end();
					bool findB = std::find(AlignedIndexes[alignmentId]->begin(), AlignedIndexes[alignmentId]->end(), O->getID_B()) != AlignedIndexes[alignmentId]->end();
					if (findA || findB)
					{
						if (findA && findB){
							getOverlapWithHighestJaccard(O->getID_A(), O->getID_B(), *Overlaps);
							alreadyPlaced = true;
							break;
						}
						//find all overlaps with same ids, select one with highest jaccard score
						overlap = getOverlapWithHighestJaccard(O->getID_A(), O->getID_B(), *Overlaps);
						split_matrix = false;
						break;
					}
				}
			//crate new alignment and push it to map, continue
				if (alreadyPlaced)
					continue;
				if (split_matrix) {
					(*alignmentContainer)[alignmentId++] = FragmentAlignments;
					AlignedIndexes[alignmentId] = new std::list<int>();
					FragmentAlignments = new std::map<int, FragmentAlignment*>();
					continue;
				}
				int startPos, endPos, index, length, offset;
			//if matrix is not split use found overlap and position it
				if (overlap->getDirection_A() == 0 && overlap->getDirection_B() == 0)
				{
					//if index A exist add indexB
					//if index B exist add indexA
					if (contains<int>(*AlignedIndexes[alignmentId], overlap->getID_A()))
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
					if (contains<int>(*AlignedIndexes[alignmentId], overlap->getID_A()))
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
					throw std::runtime_error("Read something wrong!");
				}

				//add index to AlignedIndexes
				if (contains<int>(*AlignedIndexes[alignmentId], overlap->getID_A()))
					AlignedIndexes[alignmentId]->push_back(overlap->getID_B());
				else AlignedIndexes[alignmentId]->push_back(overlap->getID_A());
				
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
		//int minOffset = -1;
		//for (auto &fragmentAlignment : *FragmentAlignments)
		//{
		//	if (fragmentAlignment.second->getOffset() < minOffset || minOffset==-1)
		//		minOffset = fragmentAlignment.second->getOffset();
		//}
		//for (auto &fragmentAlignment : *FragmentAlignments)
		//{
		//	fragmentAlignment.second->setOffset(fragmentAlignment.second->getOffset() - minOffset);
		//}
		(*alignmentContainer)[alignmentId++] = FragmentAlignments;
		return *alignmentContainer;
	}

	//************************************
	// Method:    getOverlapWithHighestJaccard
	// FullName:  LayoutReader::getOverlapWithHighestJaccard
	// Access:    private 
	// Returns:   Overlap *
	// Qualifier:
	// Parameter: int idA
	// Parameter: int idB
	// Parameter: std::list<Overlap * > & overlaps
	// Description: It fetches all overlaps with same ids, and removes them from list of 
	//				overlaps, and returns one with highest score
	//************************************
	Overlap *getOverlapWithHighestJaccard(int idA, int idB, std::list<Overlap*> &overlaps)
	{
		std::list<Overlap*> doubles;
		for (Overlap *O : overlaps)
		{
			if ((O->getID_A() == idA && O->getID_B() == idB) ||
				(O->getID_A() == idB && O->getID_B() == idA))
				doubles.push_back(O);
		}
		for (Overlap *O : doubles)
			overlaps.remove(O);

		float highestJaccardScore = -1;
		Overlap *retOverlap = NULL;
		
		for (Overlap *O : doubles)
		{
			if (O->getJaccardScore() > highestJaccardScore)
			{
				highestJaccardScore = O->getJaccardScore();
				retOverlap = O;
			}
		}

		return retOverlap;
	}

	

};

