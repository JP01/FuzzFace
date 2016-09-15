#define BOOST_TEST_MODULE circuitMutAcc

#include "TestHelper.h"

/*Declaration of test parameters*/
/* Fuzz Range - 0 < fuzz < 1 */
double fuzzInvalidLower = 0;
double fuzzValidLower = 0.01;
double fuzzValid = 0.5; 
double fuzzValidUpper = 0.99;
double fuzzInvalidUpper = 1;

/* Vol Range - 0 < vol < 1 */
double volInvalidLower = 0;
double volValidLower = 0.01;
double volValid = 0.5;
double volValidUpper = 0.99;
double volInvalidUpper = 1;

double defaultFuzz = 0.6;
double defaultVol = 0.4;

double ctrlMin = CTRL_MIN + CTRL_INCREMENT;
double ctrlMax = CTRL_MAX - CTRL_INCREMENT;

/*Test the getters and setters for the Circuit class*/
BOOST_AUTO_TEST_CASE(testFuzzInvalidLower) {
	//Create an instance of Circuit c
	Circuit c;
	//set fuzz
	c.setParams(fuzzInvalidLower, defaultVol);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getFuzz() , ctrlMin);
}

BOOST_AUTO_TEST_CASE(testFuzzValidLower) {
	//Create an instance of Circuit c
	Circuit c;
	//set fuzz
	c.setParams(fuzzValidLower,defaultVol);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getFuzz(), fuzzValidLower);
}

BOOST_AUTO_TEST_CASE(testFuzzValid) {
	//Create an instance of Circuit c
	Circuit c;
	//set fuzz
	c.setParams(fuzzValid, defaultVol);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getFuzz(), fuzzValid);
}

BOOST_AUTO_TEST_CASE(testFuzzValidUpper) {
	//Create an instance of Circuit c
	Circuit c;
	//set fuzz
	c.setParams(fuzzValidUpper, defaultVol);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getFuzz(), fuzzValidUpper);
}

BOOST_AUTO_TEST_CASE(testFuzzInvalidUpper) {
	//Create an instance of Circuit c
	Circuit c;
	//set fuzz
	c.setParams(fuzzInvalidUpper, defaultVol);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getFuzz(), ctrlMax);
}

BOOST_AUTO_TEST_CASE(testVolInvalidLower) {
	//Create an instance of Circuit c
	Circuit c;
	//set Vol
	c.setParams(defaultFuzz, volInvalidLower);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getVol(), ctrlMin);
}

BOOST_AUTO_TEST_CASE(testVolValidLower) {
	//Create an instance of Circuit c
	Circuit c;
	//set Vol
	c.setParams(defaultFuzz, volValidLower);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getVol(), volValidLower);
}

BOOST_AUTO_TEST_CASE(testVolValid) {
	//Create an instance of Circuit c
	Circuit c;
	//set Vol
	c.setParams(defaultFuzz, volValid);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getVol(), volValid);
}

BOOST_AUTO_TEST_CASE(testVolValidUpper) {
	//Create an instance of Circuit c
	Circuit c;
	//set Vol
	c.setParams(defaultFuzz, volValidUpper);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getVol(), volValidUpper);
}

BOOST_AUTO_TEST_CASE(testVolInvalidUpper) {
	//Create an instance of Circuit c
	Circuit c;
	//set Vol
	c.setParams(defaultFuzz, volInvalidUpper);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getVol(), ctrlMax);
}



