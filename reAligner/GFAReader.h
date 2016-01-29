#pragma once
#include "FileReader.h"
#include "FragmentAlignment.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

class GFAReader :
	public FileReader
{
	std::istream &inStream;
public:

	GFAReader(std::istream &inputStream) :inStream(inputStream)
	{
	}
	std::list<FragmentAlignment*> GetFragmentAlignments()
	{
		std::list<FragmentAlignment*> FA;
		while (!inStream.eof())
		{
			std::string line;
			std::getline(inStream, line);
			std::istringstream sLine(line);
			std::string		utgName		= "";
			int				utgStart	= 0;
			std::string		readName	= "";
			int				start		= 0;
			int				end			= 0;
			char			readOri		= '+';
			int				length		= 0;
			char			chow;

			switch (line[0])
			{
			case 'S':
			case 's':
				break;
			case 'a':
			case 'A':
				sLine >> chow; //prvi znak
				sLine >> utgName;
				sLine >> utgStart;
				sLine >> chow; //get first char of readName
				while (chow != ':')
				{
					readName.push_back(chow);
					sLine >> chow;
				}
				sLine >> start >> chow >> end;
				sLine >> readOri;
				sLine >> length;
				//TODO indexiranje
				if (readOri == '+')
					FA.push_back(new FragmentAlignment(readName, length, start, end, utgStart));
				else
					FA.push_back(new FragmentAlignment(readName, length, end, start, utgStart));
				break;
			case 'x':
			case 'X':
				break;
			}
		}
		return FA;
	}
	~GFAReader()
	{
	}
};

