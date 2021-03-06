#pragma once

#include <list>
#include <string>
#include <algorithm>

class Metasymbol
{
private:
	std::list<char> symbols;
public:

	Metasymbol() :symbols()
	{
	}

	//**************************************************************
	// Method:    Metasymbol
	// FullName:  Metasymbol::Metasymbol
	// Access:    public 
	// Returns:   
	// Parameter: std::string input
	// Description: Container for possible symbols on specific index
	//***************************************************************
	Metasymbol(std::string input)
	{
		for (int i = 0; i < input.length(); i++) {
			symbols.push_back(input[i]);
		}
	}

	~Metasymbol()
	{
	}
	std::list<char> &getSymbols(){
		return symbols;
	}
	std::list<char> &addSymbol(char symbol)
	{
		for (char &c:symbols)
			if (c == symbol)
			{
				return symbols;
			}
		symbols.push_back(symbol);
		return symbols;
	}
	int getSize()
	{
		return symbols.size();
	}
	bool contains(char c) {
		return std::find(symbols.begin(), symbols.end(), c) != symbols.end();
	}
	bool isDashOnly() {
		return symbols.size() == 1 && symbols.front() == '-';
	}
};

