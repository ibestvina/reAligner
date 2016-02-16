#pragma once

#include <string>

class Fragment
{
private:
	int				id;
	int				length;
	bool			isUTG;
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

	inline bool getIsUTG()
	{
		return isUTG;
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
	
	void setIsUTG(bool utg) {
		isUTG = utg;
	}

	void complementSeq() {
		for (int i = 0; i < sequence.size(); i++) {
			switch (sequence[i]) {
			case 'A': sequence[i] = 'T';
				break;
			case 'T': sequence[i] = 'A';
				break;
			case 'G': sequence[i] = 'C';
				break;
			case 'C': sequence[i] = 'G';
				break;
			}
		}
	}

};

