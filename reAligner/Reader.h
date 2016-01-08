#pragma once
#include <string>
#include <map>
#include <fstream>
#include "FragmentReader.h"
#include "Alignment.h"
#include "LayoutReader.h"

class Reader
{
	LayoutReader	*layoutReader;
	FragmentReader	*fragmentReader;
	Alignment		*alignment;

public:

	//************************************
	// Method:    Reader
	// FullName:  Reader::Reader
	// Access:    public 
	// Returns:   
	// Qualifier:
	// Parameter: std::string inputFasta
	// Parameter: std::string inputMHAP
	//************************************
	Reader(std::string inputFasta,std::string inputMHAP)
	{
		std::ifstream				fragmentFile;
		std::ifstream				layoutFile;
		std::list<AlignedFragment*> *alignedFragments = new std::list<AlignedFragment*>();

		fragmentFile.open(inputFasta);
		layoutFile	.open(inputMHAP);
		
		if (!layoutFile)
			throw std::exception("Problem loading MHAP file!");
		if (!fragmentFile)
			throw std::exception("Problem loading FASTA file!");

		try{
			layoutReader	= new LayoutReader(layoutFile);
			fragmentReader	= new FragmentReader(fragmentFile);

			std::list<Fragment*>				fragments			= fragmentReader->GetAllFragments();
			std::map<int, FragmentAlignment*>	fragmentAlignments	= layoutReader->GetAllFragmentLayouts();

			for (Fragment *F : fragments)
			{
				alignedFragments->push_back(new AlignedFragment(*F, *fragmentAlignments[F->getId()]));
			}
		}
		catch (int e)
		{
			std::cout << "An exception occurred. Exception #" << e << std::endl;
		}

		fragmentFile.close();
		layoutFile	.close();

		alignment = new Alignment(*alignedFragments);
	}

	//************************************
	// Method:    getAlignment
	// FullName:  Reader::getAlignment
	// Access:    public 
	// Returns:   Alignment *
	// Qualifier:
	//************************************
	Alignment *getAlignment()
	{
		return alignment;
	}
	~Reader()
	{
	}
};

