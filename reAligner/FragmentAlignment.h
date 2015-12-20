#pragma once

#include "Fragment.h"

class FragmentAlignment
{
private:
	int id;
	int length;
	int start;
	int end;
	int offset;
public:
	FragmentAlignment(int id, int length,
		int start, int end, int offset)
	{

	}
	~FragmentAlignment()
	{

	}

	/************************************************************************/
	/*					GETTERS                                             */
	/************************************************************************/
	int getId(){
		return id;
	}
	int getLength(){
		return length;
	}
	int getStart(){
		return start;
	}
	int getEnd(){
		return end;
	}
	int getOffset(){
		return offset;
	}
	FragmentAlignment &setOffset(int offset){
		this->offset = offset;
		return *this;
	}
	FragmentAlignment &setEnd(int end){
		this->end = end;
		return *this;
	}
	FragmentAlignment &setLength(int length){
		this->length = length;
		return *this;
	}
};

