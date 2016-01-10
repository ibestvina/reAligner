#pragma once

#include <string>

class Fragment
{
private:
	int				id;
	int				length;
	std::string		inputId;
	std::string		sequence;
public:
	Fragment(int id, int length, std::string sequence) : id(id), length(length), sequence(sequence)
	{
	}
	Fragment(int id, std::string inputId) : id(id), inputId(inputId)
	{
		length = 0;
		sequence = "";
	}
	~Fragment() 
	{
	}
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

	inline std::string getInputId() {
		return inputId;
	}

	inline std::string getSequence(){
		return sequence;
	}

	inline char getAt(int index) {
		return sequence[index];
	}

	/************************************************************************/
	/*					METHODS                                             */
	/************************************************************************/
	void insertDashAt(int index)
	{
		sequence.insert(index, "-");
		length++;
	}

	void setSequence(std::string seq) {
		sequence = seq;
	}

	void setLength(int l) {
		length = l;
	}
};

