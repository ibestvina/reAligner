#pragma once

#include "Metasymbol.h"
#include <exception>
#include <string>
#include <list>
#include <iostream>

using namespace std;

class Consensus
{
private:
	std::list<Metasymbol*> *metasymbols;
	double consensusScore;
	int ID;
public:

	Consensus(int ID)
	{
		this->ID		= ID;
		consensusScore	= 0;
		metasymbols		= new std::list<Metasymbol*>();
	}
	Consensus()
	{
		consensusScore	= 0;
		metasymbols		= new std::list<Metasymbol*>();
	}
	~Consensus()
	{
	}
	
	// Get part of consensus
	std::list<Metasymbol*> getPart(int start, int end) {
		if (start < 0 || end < 0 || start > metasymbols->size() || end > metasymbols->size() || start > end) {
			std::cout << "Start: " << start << ", end: " << end << ", size: " << metasymbols->size();
			throw exception("Invalid start/end arguments. (Consensus::getPart)");
		}
		std::list<Metasymbol*> part;
		std::list<Metasymbol*>::iterator iter = std::next(metasymbols->begin(), start);
		for (int i = start; i < end; i++) {
			part.push_back(*iter);
			iter++;
		}
		return part;
	}

	// Add dash in the from of the consensus.
	void addDashInFront() {
		Metasymbol *dash = new Metasymbol();
		dash->addSymbol('-');
		this->metasymbols->push_front(dash);
	}

	// Add dash at the end of the consensus.
	void addDashToBack() {
		Metasymbol *dash = new Metasymbol();
		dash->addSymbol('-');
		this->metasymbols->push_back(dash);
	}

	inline double getScore() {
		return consensusScore;
	}

	inline void setScore(double score) {
		consensusScore = score;
	}

	inline int getLength() {
		return metasymbols->size();
	}

	void addMetasymbol(Metasymbol *ms) {
		metasymbols->push_back(ms);
	}
};

