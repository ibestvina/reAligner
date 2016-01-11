#pragma once

#include <string>
#include <list>
#include <iostream>
#include <iterator>
#include <stdexcept>

#include "Metasymbol.h"


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
		while (!metasymbols->empty()) 
			delete metasymbols->front(), metasymbols->pop_front();
	}
	
	int getId() {
		return ID;
	}

	std::list<Metasymbol*> getPart(int start, int end) {
		if (start < 0 || end < 0 || start > metasymbols->size() || end > metasymbols->size() || start > end) {
			std::cout << "Start: " << start << ", end: " << end << ", size: " << metasymbols->size();
			throw std::runtime_error("Invalid start/end arguments. (Consensus::getPart)");
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

	double getScore() {
		return consensusScore;
	}

	void setScore(double score) {
		consensusScore = score;
	}
	Metasymbol *getRow(int row)
	{
		int r = 0;
		for (Metasymbol *var : *metasymbols)
			if (++r == row)
				return var;
		throw std::runtime_error("Index out of range");
	}
	int getLength() {
		return metasymbols->size();
	}

	void addMetasymbol(Metasymbol *ms) {
		metasymbols->push_back(ms);
	}
	void removeDashesFrontAndBack()
	{
		std::list<Metasymbol*> *newList =new std::list<Metasymbol*>();
		for (Metasymbol* M : *metasymbols)
			if (!(M->getSize() == 1 && M->contains('-')))
				newList->push_back(M);
		
		metasymbols = newList;
		

	}
	std::string toStringFirst() {
		std::string s = "";
		for (Metasymbol* M : *metasymbols)
			s = s + M->getSymbols().front();
		return s;
	}

	std::list<Metasymbol*> getMetasymbols() {
		return *metasymbols;
	}
};

