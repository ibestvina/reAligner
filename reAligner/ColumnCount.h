#pragma once

#include <list>
#include <string>
#include <algorithm>

class ColumnCount
{
public:
	int a = 0;
	int t = 0;
	int c = 0;
	int g = 0;
	int dash = 0;
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

	double getScore(char x) {
		return (getScore1(x) + getScore2(x)) / 2;
	}
};