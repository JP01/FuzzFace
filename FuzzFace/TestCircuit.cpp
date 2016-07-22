#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "Circuit.h"

//Declaration of test parameters
double fuzzInvalidLower, fuzzValidLower, fuzzValid, fuzzValidUpper, fuzzInvalidUpper, 
	   volInvalidLower, volValidLower, volValid, volValidUpper, volInvalidUpper;

/*Creates a per test case Fixture used for testing parameters.
struct Before {

	//Default Constructor for setup of the Before Vals
	Before()
	{ 
		//Boost message post
		BOOST_TEST_MESSAGE("setup fixture"); 
		std::cout << "inside the struct constructor" << std::endl;
		setUpParams();
	}

	//Default Destructor
	~Before() { BOOST_TEST_MESSAGE("teardown fixture"); }
	
	void setUpParams() {
		fuzzInvalidLower = 0;
		std::cout << "inside setUpParams" << std::endl;
	}
	//std::cout << "inside the struct";

};
*/

BOOST_FIXTURE_TEST_CASE(testCase1, Before) {
	//Create an instance of Circuit c
	Circuit c;
	fuzzInvalidLower = 0;
	
}

BOOST_FIXTURE_TEST_CASE(testCase2, Before) {
	//Create an instance of Circuit c
	Circuit c;
	
}

