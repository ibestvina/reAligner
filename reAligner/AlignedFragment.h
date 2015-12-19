#pragma once

#include "Fragment.h"

class AlignedFragment :
	public Fragment
{
private:
	int start;
	int end;
	int offset;
public:
	AlignedFragment(int id, int length, std::string sequence,
					int start, int end, int offset);
	AlignedFragment(Fragment &fragment, int start, int end, int offset);
	~AlignedFragment();

	/************************************************************************/
	/*					GETTERS                                             */
	/************************************************************************/

	inline int getStart(){
		return start;
	};
	inline int getEnd(){
		return end;
	};
	inline int getOffset(){
		return offset;
	};
	inline void setOffset(int offset){
		this->offset = offset;
	};
};

