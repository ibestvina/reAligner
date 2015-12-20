#pragma once
#include <string>
#include "Metasymbol.h"

class Consensus
{
private:
	std::list<Metasymbol*> *Metasymbols;
	double consensusScore;
	int ID;
public:

	Consensus(int ID)
	{
		this->ID		= ID;
		consensusScore	= 0;
		Metasymbols		= new std::list<Metasymbol*>();
	}
	Consensus()
	{
		consensusScore	= 0;
		Metasymbols		= new std::list<Metasymbol*>();
	}
	~Consensus()
	{
	}
	/**
	* Add dash in the from of the consensus.
	*/
	void addDashInFront() {
		Metasymbol *dash = new Metasymbol();
		dash->addSymbol('-');
		this->Metasymbols->push_front(dash);
	}
	/**
	* Add dash at the end of the consensus.
	*/
	void addDashToBack() {
		Metasymbol *dash = new Metasymbol();
		dash->addSymbol('-');
		this->Metasymbols->push_back(dash);
	}
};

