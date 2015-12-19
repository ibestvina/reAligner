#include "FileReader.h"
#include <ctype.h>
#include <iostream>

FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}

std::list<AlignedFragment> &FileReader::GetAllAlignments(std::string inFile, std::list<Fragment> fragments){
	/*TODO*/
	return *new std::list<AlignedFragment>();
}
std::list<Fragment> &FileReader::GetAllFragments(std::string inFile){
	/*TODO*/
	return *new std::list<Fragment>();
}

int FileReader::StringToInteger(std::string &toBeFormatted) {
	std::string &output = *new std::string();
	for (char &character: toBeFormatted){
		if (character == '_') continue;
		else if (character<='0' && character>='9'){
			output.push_back(character);
		}
		else{
			std::cout << toBeFormatted << std::endl;
			std::cout<<"Invalid format for number"<<std::endl;
			exit(-1);
		}
	}
	return stoi(output);
}