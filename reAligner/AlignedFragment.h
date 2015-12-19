#pragma once

#include "Fragment.h"

class AlignedFragment :
	public Fragment
{
private:
	//offset in matrix
	int offset;
	int start;
	int end;
	int layoutOffset;
public:
	AlignedFragment(int id, int length, std::string sequence,
		int offset, int start, int end, int layoutOffset);
	AlignedFragment(Fragment &fragment, int start, int end, int layoutOffset);
	~AlignedFragment();

	/************************************************************************/
	/*					GETTERS                                             */
	/************************************************************************/
	inline int getOffset(){
		return offset;
	}
	inline int getStart(){
		return start;
	}
	inline int getEnd(){
		return end;
	}
	inline int getLayoutOffset(){
		return layoutOffset;
	}
};

