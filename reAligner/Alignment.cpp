#include "Alignment.h"


Alignment::Alignment(std::list<AlignedFragment*> &Fragments) :Fragments(Fragments)
{
}


Alignment::~Alignment()
{
}

std::list<FragmentAlignment*>& Alignment::getAllFragments()
{
	return *new std::list<FragmentAlignment*>();
}

FragmentAlignment& Alignment::FragmentAt(int index)
{
	return *new FragmentAlignment(0, 0, 0, 0, 0);
}

FragmentAlignment& Alignment::DetachFragmentAt(int index)
{
	return *new FragmentAlignment(0,0,0,0,0);
}

void Alignment::AddFragment(FragmentAlignment fragment)
{

}