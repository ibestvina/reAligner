#pragma once

#include <list>

#include "AlignedFragment.h"

class Alignment
{
	std::list<AlignedFragment*>	&Fragments;
public:
	//************************************
	// Method:    Alignment
	// FullName:  Alignment::Alignment
	// Access:    public 
	// Returns:   
	// Qualifier:
	// Parameter: std::list<AlignedFragment * > & Fragments
	//************************************
	Alignment(std::list<AlignedFragment*>  &Fragments);
	
	~Alignment();
	
	//************************************
	// Method:    getAllFragments
	// FullName:  Alignment::getAllFragments
	// Access:    public 
	// Returns:   std::list<AlignedFragment*> &
	// Qualifier:
	//************************************
	std::list<AlignedFragment*> &getAllFragments();

	//************************************
	// Method:    FragmentAt
	// FullName:  Alignment::FragmentAt
	// Access:    public 
	// Returns:   AlignedFragment &
	// Qualifier:
	// Parameter: int index
	//************************************
	AlignedFragment &FragmentAt(int index);
	
	AlignedFragment *PopFirst();

	void AddFragment(AlignedFragment* fragment);

	int getSize();

};

