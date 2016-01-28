#pragma once

#include "Fragment.h"

class FragmentAlignment
{
private:
	int id;
	std::string name;
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
	FragmentAlignment(std::string name , int length,
		int start, int end, int offset)
	{
		this->name = name;
		this->length = length;
		this->start = start;
		this->end = end;
		this->offset = offset;
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
	std::string getName()
	{
		return name;
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
	FragmentAlignment &setStart(int start)
	{
		this->start = start;
		return *this;
	}
};

