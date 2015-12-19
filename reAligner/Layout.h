#pragma once

#include <list>

#include "AlignedFragment.h"
#include "Overlap.h"

class Layout
{
private:
	std::list<Overlap> Overlaps;
public:
	Layout();
	~Layout();

	//Add row from MHAP file
	void AddOverlap(int AID, int BID, int JaccardScore, int SharedMinMers, int ADirection,
		int AStart, int AEnd, int ALength, int BDirection, int BStart, int BEnd, int BLength);
	//Generate Alignment ordered by start index
	std::list<AlignedFragment> &GenerateAlignment();
};

