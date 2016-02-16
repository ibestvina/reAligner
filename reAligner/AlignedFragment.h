#pragma once

#include <string>

#include "Fragment.h"
#include "FragmentAlignment.h"

class AlignedFragment
{
private:
	Fragment			&fragment;
	FragmentAlignment	&fragmentAlignment;
public:

	AlignedFragment(Fragment &fragment, FragmentAlignment &fragmentAlignment) 
		:fragment(fragment), fragmentAlignment(fragmentAlignment)
	{
	}

	~AlignedFragment()
	{
	}

	inline int getId(){
		return fragment.getId();
	}
	inline int getLength(){
		return fragment.getLength();
	}
	inline std::string getInputId() {
		return fragment.getInputId();
	}
	inline int getStart(){
		return fragmentAlignment.getStart();
	};
	inline int getEnd(){
		return fragmentAlignment.getEnd();
	};
	inline int getOffset(){
		return fragmentAlignment.getOffset();
	};
	inline int getGfaLength() {
		return fragmentAlignment.getGfaLength();
	};
	inline void setOffset(int offset){
		fragmentAlignment.setOffset(offset);
	};

	inline std::string getSequence(){
		return fragment.getSequence();
	}
	
	void insertDashAt(int index)
	{
		fragmentAlignment.setEnd(fragmentAlignment.getEnd() + 1)
					     .setLength(fragmentAlignment.getLength() + 1);
		fragment.insertDashAt(index);
	}

	char getAt(int index) {
		return fragment.getAt(index);
	}

	void setSequence(std::string seq) {
		fragment.setSequence(seq);
	}
	void  removeDashesFrontAndBack()
	{
		std::string newSeq;
		for (char C : fragment.getSequence())
			if (C != '-')
				newSeq.push_back(C);

		fragment.setSequence(newSeq);


	}
};

