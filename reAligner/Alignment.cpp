#include "Alignment.h"


Alignment::Alignment(std::list<AlignedFragment> &Fragments) :Fragments(Fragments)
{
}


Alignment::~Alignment()
{
}

std::list<FragmentAlignment> Alignment::&getAllFragments(){

}

FragmentAlignment Alignment::&FragmentAt(int index){

}

FragmentAlignment Alignment::&DetachFragmentAt(int index)
{

}

void Alignment::AddFragment(FragmentAlignment fragment)
{

}