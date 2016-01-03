#pragma once

#include<list>

class Metasymbol
{
private:
	std::list<char> symbols;
public:

	Metasymbol() :symbols()
	{
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
	bool contains(char c) {
		return std::find(symbols.begin(), symbols.end(), c) != symbols.end();
	}
	bool isDashOnly() {
		return symbols.size() == 1 && symbols.front() == '-';
	}
};

