#pragma once

#include <string>

class Fragment
{
private:
	int				id;
	int				length;
	std::string		sequence;
public:
	Fragment(int id, int length, std::string sequence);
	~Fragment();
	/************************************************************************/
	/*                    GETTERS                                           */
	/************************************************************************/
	
	inline int getId(){
		return id;
	}

	inline int getLength()
	{
		return length;
	}

	inline std::string getSequence(){
		return sequence;
	}

	/************************************************************************/
	/*					METHODS                                             */
	/************************************************************************/
	void insertDashAt(int index)
	{
		sequence.insert(index, "-");
		length++;
	}
};

