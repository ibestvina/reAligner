#include <list>
#include <string>
#include <sstream>
#include <iostream>

#include "TestFragmentReader.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(TestFragmentReader);


void
TestFragmentReader::setUp()
{
}


void
TestFragmentReader::tearDown()
{
}


void
TestFragmentReader::testConstructor(){}

void TestFragmentReader::testGetAllFragments()
{
	std::stringstream fragmentFile;
	FragmentReader FR(fragmentFile);
	
	std::list<Fragment*> fragments = (new FragmentReader(fragmentFile))->GetAllFragments();
	CPPUNIT_ASSERT(fragments.size() == 0);

	fragmentFile.clear();
	fragmentFile << ">1" << std::endl;
	fragmentFile << "TTTTCGACCAAAGGTAACGAGGTAACAACCATGC" << std::endl;
	fragmentFile << ">2" << std::endl;
	fragmentFile << "GTGAGTAAATTAAAATTTTATTGACTTAGGTCACTAAATACTTTAACCAATATA" << std::endl;
	fragmentFile << "GTGAGTAAATTAAAATTTTATTGACTTAGGTCACTA" << std::endl;
	fragmentFile << ">3" << std::endl;
	fragmentFile << "AGA" << std::endl;
	fragmentFile << "TAA" << std::endl;
	fragmentFile << "AGATAACACATCA" << std::endl;
	fragments = (new FragmentReader(fragmentFile))->GetAllFragments();	
	CPPUNIT_ASSERT(fragments.size() == 3);	
	CPPUNIT_ASSERT(fragments.front()->getId() == 1);
	CPPUNIT_ASSERT(fragments.front()->getLength() == 34);
	CPPUNIT_ASSERT_EQUAL(fragments.front()->getSequence(), std::string("TTTTCGACCAAAGGTAACGAGGTAACAACCATGC"));
	CPPUNIT_ASSERT(fragments.back()->getId() == 3);
	CPPUNIT_ASSERT(fragments.back()->getLength() == 19);
	CPPUNIT_ASSERT_EQUAL(fragments.back()->getSequence(), std::string("AGATAAAGATAACACATCA"));

}

void TestFragmentReader::testGetAllFragmentsQ()
{
	std::stringstream fragmentFile;
	FragmentReader FR(fragmentFile);

	std::list<Fragment*> fragments = (new FragmentReader(fragmentFile))->GetAllFragments();
	CPPUNIT_ASSERT(fragments.size() == 0);

	fragmentFile.clear();
	fragmentFile << ">1" << std::endl;
	fragmentFile << "TTTTCGACCAAAGGTAACGAGGTAACAACCATGC" << std::endl;
	fragmentFile << "+2" << std::endl;
	fragmentFile << "random characters" << std::endl;
	fragmentFile << "more random characters" << std::endl;
	fragmentFile << ">2" << std::endl;
	fragmentFile << "AGACCCCTTTTTACACA" << std::endl;
	fragmentFile << ">3" << std::endl;
	fragmentFile << "AGA" << std::endl;
	fragmentFile << "TAA" << std::endl;
	fragmentFile << "AGATAACACATCA" << std::endl;
	fragments = (new FragmentReader(fragmentFile))->GetAllFragments();
	CPPUNIT_ASSERT(fragments.size() == 3);
	CPPUNIT_ASSERT(fragments.front()->getId() == 1);
	CPPUNIT_ASSERT(fragments.front()->getLength() == 34);
	CPPUNIT_ASSERT_EQUAL(fragments.front()->getSequence(), std::string("TTTTCGACCAAAGGTAACGAGGTAACAACCATGC"));
	CPPUNIT_ASSERT(fragments.back()->getId() == 3);
	CPPUNIT_ASSERT(fragments.back()->getLength() == 19);
	CPPUNIT_ASSERT_EQUAL(fragments.back()->getSequence(), std::string("AGATAAAGATAACACATCA"));

}