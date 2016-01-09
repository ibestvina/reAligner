#pragma once

#include <string>
#include <list>
#include <exception>

#include "Fragment.h"
#include "FragmentAlignment.h"

class FileReader
{
public:
	FileReader()
	{
	}
	~FileReader()
	{
	}
protected:
	int StringToInteger(std::string &toBeFormatted)
	{
		std::string &output = *new std::string();
		for (char &character : toBeFormatted){
			if (character == '_' || character == '>') continue;
			else if (character >= '0' && character <= '9'){
				output.push_back(character);
			}
			else{
				std::cout << toBeFormatted << std::endl;
				std::cout << "Invalid format for number!" << std::endl;
				exit(-1);
			}
		}
		return stoi(output);
	}
};

