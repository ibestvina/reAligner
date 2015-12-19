#pragma once

#include <list>

#include "AlignedFragment.h"

class Alignment
{
	std::list<AlignedFragment> &AlignedFragments;
public:
	Alignment(std::list<AlignedFragment> &AlignedFragments);
	~Alignment();

	std::list<AlignedFragment> &getAllFragments();
	AlignedFragment &FragmentAt(int index);
	AlignedFragment &DetachFragmentAt(int index);
	void AddFragment(AlignedFragment fragment);


};

