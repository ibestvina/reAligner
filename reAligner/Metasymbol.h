#pragma once

#include<list>

class Metasymbol
{
private:
	std::list<char> Symbols;
public:

	Metasymbol() :Symbols()
	{
	}

	~Metasymbol()
	{
	}
	std::list<char> &getSymbols(){
		return Symbols;
	}
	std::list<char> &addSymbol(char symbol)
	{
		for (char &c:Symbols)
			if (c == symbol)
			{
				return Symbols;
			}
		Symbols.push_back(symbol);
		return Symbols;
	}
};

