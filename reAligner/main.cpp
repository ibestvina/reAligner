#define TESTING 1

#ifdef TESTING
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <iostream>
#endif //TESTING


int main()
{
#ifdef TESTING


	std::cout << "Start testing..." << std::endl;
	// Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);

	// Change the default outputter to a compiler error format outputter
	runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),
		std::cerr));
	// Run the tests.
	bool wasSucessful = runner.run();

	std::cin.get();

	// Return error code 1 if the one of test failed.

	return wasSucessful ? 0 : 1;
#else  //not TESTING
#endif // TESTING
	return 0;
}