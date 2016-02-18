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

	void FwdSeqSplit(int start, int end)
	{
		sequence = std::string(sequence.begin() + start,
					sequence.begin() + end);
		length = sequence.size();
	}
	void RevSeqSplit(int start, int end)
	{
		sequence = std::string(sequence.rbegin() + sequence.size() - start,
						sequence.rbegin() + sequence.size() - end);
		
		length = sequence.size();
		for (int i = 0; i < length;i++)
		{
			switch (sequence[i])
			{
				case 'A': 
					sequence[i] = 'T';
					break;
				case 'T':
					sequence[i] = 'A';
					break;
				case 'C':
					sequence[i] = 'G';
					break;
				case 'G':
					sequence[i] = 'C';
					break;	
			}
		}

	}
};

