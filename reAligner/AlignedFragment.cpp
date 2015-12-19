#include "AlignedFragment.h"


AlignedFragment::AlignedFragment(int id, int length, std::string sequence, int offset, int start, int end, int layoutOffset)
	:Fragment(id,length,sequence)
{
}
AlignedFragment::~AlignedFragment()
{
}
