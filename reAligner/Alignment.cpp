#include "Alignment.h"


Alignment::Alignment(std::list<AlignedFragment*> &Fragments) :Fragments(Fragments)
{
}


Alignment::~Alignment()
{
}

std::list<AlignedFragment*>& Alignment::getAllFragments()
{
	return Fragments;
}

AlignedFragment& Alignment::FragmentAt(int index)
{
	for (AlignedFragment *A : Fragments)
		if (A->getId() == index)
			return *A;

	throw new std::exception("Index out of range");
	//TODO if needed (this is mock only)
	//FragmentAlignment &fa = *new FragmentAlignment(0, 0, 0, 0, 0);
	//Fragment &f = *new Fragment(0, 0, "");
	//return *new AlignedFragment(f, fa);
}

AlignedFragment *Alignment::PopFirst()
{
	AlignedFragment *first = Fragments.front();
	Fragments.pop_front();
	return first;
}

void Alignment::AddFragment(AlignedFragment* fragment)
{
	Fragments.push_back(fragment);
}

int Alignment::getSize()
{
	return Fragments.size();
}		


