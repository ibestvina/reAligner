#pragma once

#include <string>
#include <map>
#include <fstream>
#include <list>
#include <iostream>
#include <stdexcept>
#include <map>


#include "FragmentReader.h"
#include "Alignment.h"
#include "LayoutReader.h"
#include "GFAReader.h"

class Reader
{
	std::list<Alignment*>	*alignments;

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
	Reader(std::string inputFasta, std::string inputMHAP, bool useMhap)
	{
		std::ifstream				fragmentFile;
		std::ifstream				mhapFile;
		std::list<AlignedFragment*> *alignedFragments = new std::list<AlignedFragment*>();

		fragmentFile.open(inputFasta);
		mhapFile.open(inputMHAP);
		
		if (!mhapFile)
			throw std::runtime_error("Problem loading MHAP file!");
		if (!fragmentFile)
			throw std::runtime_error("Problem loading FASTA file!");

		try{
			LayoutReader	mhapReader(mhapFile);
			FragmentReader	fragmentReader(fragmentFile);

			fragmentReader.GetAllFragments();
			std::map<int,std::map<int, FragmentAlignment*>*>	fragmentAlignments	= layoutReader.GetAllFragmentLayouts();			
			
			for (std::pair<int, std::map<int, FragmentAlignment*>*> A : fragmentAlignments)
			{
				for (Fragment *F : fragments)
				{
					if (A.second->count(F->getId()) != 0)
					{
						if ((*A.second)[F->getId()]->getStart() != 0)
						{
							std::string str = F->getSequence();
							F->setSequence(std::string(str.rbegin(),str.rend()));
						}
						alignedFragments->push_back(new AlignedFragment(*F, *(*A.second)[F->getId()]));
					}
				}
				alignments.push_back(new Alignment(*alignedFragments));
			}
		}
		catch (int e)
		{
			std::cout << "An exception occurred. Exception #" << e << std::endl;
		}

		fragmentFile.close();
		layoutFile	.close();
	}


	Reader(std::string inputFasta, std::string inputGFA)
	{
		alignments = new std::list<Alignment*>();
		std::ifstream				fragmentFile;
		std::ifstream				layoutFile;
		std::list<AlignedFragment*> *alignedFragments = new std::list<AlignedFragment*>();

		fragmentFile.open(inputFasta);
		layoutFile.open(inputGFA);

		if (!layoutFile)
			throw std::runtime_error("Problem loading GFA file!");
		if (!fragmentFile)
			throw std::runtime_error("Problem loading FASTA file!");

		try{
			GFAReader	layoutReader(layoutFile);
			FragmentReader	fragmentReader(fragmentFile);

			fragmentReader.GetAllFragments();
			std::list<FragmentAlignment*>	fragmentAlignments = layoutReader.GetFragmentAlignments();

			for (FragmentAlignment *FA : fragmentAlignments)
			{

				Fragment *F = fragmentReader.get(FA->getName());
				//FA->setId(F->getId());
				std::string seq = F->getSequence();
				if (FA->getStart() < FA->getEnd())
				{
					F->setSequence(std::string( seq.begin()+FA->getStart() , 
												seq.begin()+FA->getEnd()));
				}
				else 
				{
					//indexing starts from position 0, on rbegin starts from end
					//so, we have to add the size of seq - 1
					F->setSequence(std::string(seq.rbegin() + seq.size() - 1 - FA->getStart(), 
												seq.rbegin() + seq.size() - 1 - FA->getEnd()));
					F->complementSeq();
				}
				F->setLength(FA->getLength());
				alignedFragments->push_back(new AlignedFragment(*F,*FA));

				
			}
			alignments->push_back(new Alignment(*alignedFragments));
		}
		catch (int e)
		{
			std::cout << "An exception occurred. Exception #" << e << std::endl;
		}

		fragmentFile.close();
		layoutFile.close();
	}
	Reader(std::string inputFasta, std::string inputGFA, std::string inputMHAP) :alignments()
	{
		alignments = new std::list<Alignment*>();
		std::ifstream				fragmentFile;
		std::ifstream				layoutFile;
		std::ifstream				mhapFile;
		std::list<AlignedFragment*> *alignedFragments = new std::list<AlignedFragment*>();

		fragmentFile.open(inputFasta);
		layoutFile.open(inputGFA);
		mhapFile.open(inputMHAP);

		if (!layoutFile)
			throw std::runtime_error("Problem loading GFA file!");
		if (!fragmentFile)
			throw std::runtime_error("Problem loading FASTA file!");
		if (!mhapFile)
			throw std::runtime_error("Problem loading MHAP file!");

		try{
			GFAReader		layoutReader(layoutFile);
			FragmentReader	fragmentReader(fragmentFile);
			LayoutReader	mhapReader(mhapFile);

			fragmentReader.GetAllFragments();
			std::list<FragmentAlignment*>	fragmentAlignments = layoutReader.GetFragmentAlignments();

			for (FragmentAlignment *FA : fragmentAlignments)
			{
				Fragment* F = fragmentReader.get(FA->getName());
				FA->setId(F->getId());

			}
			for (FragmentAlignment *FA : fragmentAlignments)
			{
				Fragment* F = fragmentReader.get(FA->getName());
				std::string seq = F->getSequence();
				if (FA->getStart() < FA->getEnd())
				{
					F->setSequence(std::string(seq.begin() + FA->getStart(),
						seq.begin() + FA->getEnd()));
					F->complementSeq();
				}
				else
				{
					//indexing starts from position 0, on rbegin starts from end
					//so, we have to add the size of seq - 1
					F->setSequence(std::string(seq.rbegin() + seq.size() - 1 - FA->getStart(),
						seq.rbegin() + seq.size() - 1 - FA->getEnd()));
				}
				F->setLength(FA->getLength());
				alignedFragments->push_back(new AlignedFragment(*F, *FA));
				
				std::list<FragmentAlignment*> overlaping = mhapReader.getFragmentAlignments(FA);
				
				for (FragmentAlignment* OFA : overlaping)
				{
					//if is in gfa, continue
					bool inGFA = false;
					for (auto check : fragmentAlignments)
						if (OFA->getId() == check->getId())
							inGFA = true;
					if (inGFA)
						continue;
					//if already added
					bool added = false;
					for (auto check : *alignedFragments)
						if (OFA->getId() == check->getId())
							added = true;
					if (added)
						continue;

					Fragment* F = fragmentReader.get(OFA->getId());
					//OFA->setId(F->getId());
					std::string seq = F->getSequence();
					if (OFA->getStart() < OFA->getEnd())
					{
						F->setSequence(std::string(seq.begin() + OFA->getStart(),
							seq.begin() + OFA->getEnd()));
					}
					else
					{
						//indexing starts from position 0, on rbegin starts from end
						//so, we have to add the size of seq - 1
						F->setSequence(std::string(seq.rbegin() + seq.size() - 1 - OFA->getStart(),
							seq.rbegin() + seq.size() - 1 - OFA->getEnd()));
					}
					F->setLength(OFA->getLength());
					alignedFragments->push_back(new AlignedFragment(*F, *OFA));
				}
			}
			


			alignments->push_back(new Alignment(*alignedFragments));
		}
		catch (int e)
		{
			std::cout << "An exception occurred. Exception #" << e << std::endl;
		}

		fragmentFile.close();
		layoutFile.close();
	}
	//************************************
	// Method:    getAlignment
	// FullName:  Reader::getAlignment
	// Access:    public 
	// Returns:   Alignment *
	// Qualifier:
	//************************************
	std::list<Alignment*> &getAlignment()
	{
		return *alignments;
	}
	~Reader()
	{
	}
};

