#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "Circuit.h"

/*Declaration of test parameters*/
/* Fuzz Range - 0 < fuzz <= 1 */
double fuzzInvalidLower = 0;
double fuzzValidLower = 0.01;
double fuzzValid = 0.5; 
double fuzzValidUpper = 1;
double fuzzInvalidUpper = 1.01;

/* Vol Range - 0 < vol <= 1 */
double volInvalidLower = 0;
double volValidLower = 0.01;
double volValid = 0.5;
double volValidUpper = 1;
double volInvalidUpper = 1.01;
double defaultFuzz = 0.6;
double defaultVol = 0.4;

/*Test the getters and setters for the Circuit class*/

BOOST_AUTO_TEST_CASE(testFuzzInvalidLower) {
	//Create an instance of Circuit c
	Circuit c;
	//set fuzz
	c.setFuzz(fuzzInvalidLower);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getFuzz() , defaultFuzz);
}

BOOST_AUTO_TEST_CASE(testFuzzValidLower) {
	//Create an instance of Circuit c
	Circuit c;
	//set fuzz
	c.setFuzz(fuzzValidLower);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getFuzz(), fuzzValidLower);
}

BOOST_AUTO_TEST_CASE(testFuzzValid) {
	//Create an instance of Circuit c
	Circuit c;
	//set fuzz
	c.setFuzz(fuzzValid);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getFuzz(), fuzzValid);
}

BOOST_AUTO_TEST_CASE(testFuzzValidUpper) {
	//Create an instance of Circuit c
	Circuit c;
	//set fuzz
	c.setFuzz(fuzzValidUpper);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getFuzz(), fuzzValidUpper);
}

BOOST_AUTO_TEST_CASE(testFuzzInvalidUpper) {
	//Create an instance of Circuit c
	Circuit c;
	//set fuzz
	c.setFuzz(fuzzInvalidUpper);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getFuzz(), defaultFuzz);
}

BOOST_AUTO_TEST_CASE(testVolInvalidLower) {
	//Create an instance of Circuit c
	Circuit c;
	//set Vol
	c.setVol(volInvalidLower);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getVol(), defaultVol);
}

BOOST_AUTO_TEST_CASE(testVolValidLower) {
	//Create an instance of Circuit c
	Circuit c;
	//set Vol
	c.setVol(volValidLower);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getVol(), volValidLower);
}

BOOST_AUTO_TEST_CASE(testVolValid) {
	//Create an instance of Circuit c
	Circuit c;
	//set Vol
	c.setVol(volValid);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getVol(), volValid);
}

BOOST_AUTO_TEST_CASE(testVolValidUpper) {
	//Create an instance of Circuit c
	Circuit c;
	//set Vol
	c.setVol(volValidUpper);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getVol(), volValidUpper);
}

BOOST_AUTO_TEST_CASE(testVolInvalidUpper) {
	//Create an instance of Circuit c
	Circuit c;
	//set Vol
	c.setVol(volInvalidUpper);
	//check get matches default
	BOOST_CHECK_EQUAL(c.getVol(), defaultVol);
}