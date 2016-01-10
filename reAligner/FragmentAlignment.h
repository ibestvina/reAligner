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
		this->id		= id;
		this->length	= length;
		this->start		= start;
		this->end		= end;
		this->offset	= offset;
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
	void setOffset(int offset){
		this->offset = offset;
	}
	void setEnd(int end){
		this->end = end;
	}
	void setLength(int length){
		this->length = length;
	}
	void setStart(int start)
	{
		this->start = start;
	}
};

