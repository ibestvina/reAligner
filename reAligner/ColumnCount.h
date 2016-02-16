#pragma once

#include <list>
#include <string>
#include <algorithm>

/*
* ColumnCount class holds the number of occurrences of each symbol in one alignment column. 
*/
class ColumnCount
{
public:
	int a = 0;
	int t = 0;
	int c = 0;
	int g = 0;
	int dash = 0;
	// number of occurrences of the most frequent symbol
	int max;

	ColumnCount()
	{
	}
	ColumnCount(std::list<char> *column)
	{
		for (char x : *column)
		{
			switch (x)
			{
			case 'A': a++;
				break;
			case 'C': c++;
				break;
			case 'G': g++;
				break;
			case 'T': t++;
				break;
			case '-': dash++;
				break;
			}
		}
		max = std::max(a, std::max(t, std::max(c, std::max(g, dash))));
	}

	int maxCount()
	{
		return std::max(a, std::max(t, std::max(c, std::max(g, dash))));
	}

	// calculates the cost of aligning char x with this column using the function:
	// f(x,X) = 0 if x is element of X, -1 otherwise, where x is a given symbol, and X is a set of most frequent symbols in a column
	double getScore1(char x)
	{

		switch (x)
		{
		case 'A': return (int)(a == max) - 1;
		case 'C': return (int)(c == max) - 1;
		case 'G': return (int)(g == max) - 1;
		case 'T': return (int)(t == max) - 1;
		case '-': return (int)(dash == max) - 1;
		}
	}

	// calculates the cost of aligning char x with this column using the function:
	// f(x,X) = (C-Nx) / C, where C is the size of column, and Nx the number of occurrences of symbol x in the column
	double getScore2(char x)
	{
		int sum = a + c + t + g + dash;
		if (sum == 0) return 0;
		switch (x)
		{
		case 'A': return (a - sum) / sum;
		case 'C': return (c - sum) / sum;
		case 'G': return (g - sum) / sum;
		case 'T': return (t - sum) / sum;
		case '-': return (dash - sum) / sum;
		}
	}

	// calculates weighted combination of two scores
	double getScore(char x) {
		return (getScore1(x) + getScore2(x)) / 2;
	}

	char toChar() {
		if (a == max) return 'A';
		if (c == max) return 'C';
		if (g == max) return 'G';
		return 'T';
	}
};