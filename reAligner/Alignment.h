#pragma once

#include <list>

#include "AlignedFragment.h"

class Alignment
{
	std::list<AlignedFragment*>	&Fragments;
public:
	Alignment(std::list<AlignedFragment*>  &Fragments);
	
	~Alignment();
	
	std::list<AlignedFragment*> &getAllFragments();

	AlignedFragment &FragmentAt(int index);
	
	AlignedFragment *PopFirst();

	void AddFragment(AlignedFragment* fragment);

	int getSize();

};

