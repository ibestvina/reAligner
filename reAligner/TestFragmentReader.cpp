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
TestFragmentReader::testConstructor()
{
	CPPUNIT_FAIL("not implemented");
}

void TestFragmentReader::testGetAllFragments()
{
	
	std::stringstream fragmentFile;
	fragmentFile << ">1" << std::endl;
	fragmentFile << "GTGAGTAAATTAAAATTTTATTGACTTAGGTCACTAAATACTTTAACCAATATA" << std::endl;
	fragmentFile << ">2" << std::endl;
	fragmentFile << "TTTTCGACCAAAGGTAACGAGGTAACAACCATGC" << std::endl;

	FragmentReader FR(fragmentFile);
	std::list<Fragment*> fragments = FR.GetAllFragments();
	CPPUNIT_ASSERT(fragments.size() == 2);

}