#pragma once

#include <list>

#include "AlignedFragment.h"

class Alignment
{
	std::list<AlignedFragment>	&Fragments;
public:
	Alignment(std::list<AlignedFragment>  &Fragments);
	
	~Alignment();
	
	std::list<FragmentAlignment> &getAllFragments();

	FragmentAlignment &FragmentAt(int index);
	
	FragmentAlignment &DetachFragmentAt(int index);
	
	void AddFragment(FragmentAlignment fragment);


};

