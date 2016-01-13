#include <stdexcept>
#include <list>

#include "Alignment.h"


Alignment::Alignment(std::list<AlignedFragment*> &Fragments) :Fragments(Fragments)
{
}


Alignment::~Alignment()
{
}

// returns all fragments in an alignment
std::list<AlignedFragment*>* Alignment::getAllFragments()
{
	return &Fragments;
}

// returns a fragment with a given ID
AlignedFragment& Alignment::FragmentAt(int id)
{
	for (AlignedFragment *A : Fragments)
		if (A->getId() == id)
			return *A;

	throw std::runtime_error("Index out of range");
}

// removes first fragment
AlignedFragment *Alignment::PopFirst()
{
	AlignedFragment *first = Fragments.front();
	Fragments.pop_front();
	return first;
}

// adds fragment to the back of the fragments list
void Alignment::AddFragment(AlignedFragment* fragment)
{
	Fragments.push_back(fragment);
}

// returns the number of fragments
int Alignment::getSize()
{
	return Fragments.size();
}		


