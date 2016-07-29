//#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "Circuit.h"
#include "TestHelper.h"
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "Eigen/Dense"

/*
Test Data 
*/
//Test SampleRates
double SR441 = 44100;  
double SR48 = 48000;
double SR96 = 96000;

//Test fuzz values
double fuzzDefault = 0.6;
double fuzzLow = 0.01;
double fuzzHigh = 0.99;
//Test Volume values
double volDefault = 0.4;
double volLow = 0.01;
double volHigh = 0.99;

//Different Sample rates with default Fuzz and Vol
std::string matlabSettingsDefault_SR441 = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/systemMatrixFromMatlab_F_60_V_40_SR_44100.txt";
std::string matlabSettingsDefault_SR48 = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/systemMatrixFromMatlab_F_60_V_40_SR_48000.txt";
std::string matlabSettingsDefault_SR96 = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/systemMatrixFromMatlab_F_60_V_40_SR_96000.txt";

//Different Sample-rates with Low fuzz and vol
std::string matlabSettingsLow_SR441 = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/systemMatrixFromMatlab_F_01_V_01_SR_44100.txt";
std::string matlabSettingsLow_SR48 = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/systemMatrixFromMatlab_F_01_V_01_SR_48000.txt";
std::string matlabSettingsLow_SR96 = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/systemMatrixFromMatlab_F_01_V_01_SR_96000.txt";

//Different Sample-rates with High fuzz and vol
std::string matlabSettingsHigh_SR441 = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/systemMatrixFromMatlab_F_99_V_99_SR_44100.txt";
std::string matlabSettingsHigh_SR48 = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/systemMatrixFromMatlab_F_99_V_99_SR_48000.txt";
std::string matlabSettingsHigh_SR96 = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/systemMatrixFromMatlab_F_99_V_99_SR_96000.txt";

//Create an instance of TestHelper
TestHelper th;


/*
Test the system matrix against expected values (from matlab) with default settings for fuzz vol and sample rate 44100
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixDefault_SR441) {
	//Create an instance of Circuit with default Samplerate
	Circuit c(SR441);
	//Set Fuzz and Vol settings
	c.setFuzz(fuzzDefault);
	c.setVol(volDefault);
	
	//Create the testPass flag used to store result of matrixChecker
	bool testPass;
	testPass = th.matrixChecker(matlabSettingsDefault_SR441, c.getSystemMatrix());
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}

/*
Test the system matrix against expected values (from matlab) with default settings for fuzz vol and sample rate 48000
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixDefault_SR48) {
	//Create an instance of Circuit with default Samplerate
	Circuit c(SR48);
	//Set Fuzz and Vol settings
	c.setFuzz(fuzzDefault);
	c.setVol(volDefault);

	//Create the testPass flag used to store result of matrixChecker
	bool testPass;
	testPass = th.matrixChecker(matlabSettingsDefault_SR48, c.getSystemMatrix());
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}

/*
Test the system matrix against expected values (from matlab) with default settings for fuzz vol and sample rate 96000
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixDefault_SR96) {
	//Create an instance of Circuit with default Samplerate
	Circuit c(SR96);
	//Set Fuzz and Vol settings
	c.setFuzz(fuzzDefault);
	c.setVol(volDefault);

	//Create the testPass flag used to store result of matrixChecker
	bool testPass;
	testPass = th.matrixChecker(matlabSettingsDefault_SR96, c.getSystemMatrix());
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}


/*
Test the system matrix against expected values (from matlab) with Low settings for fuzz vol and sample rate 44100
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixLow_SR441) {
	//Create an instance of Circuit with default Samplerate
	Circuit c(SR441);
	//Set Fuzz and Vol settings
	c.setFuzz(fuzzLow);
	c.setVol(volLow);

	//Create the testPass flag used to store result of matrixChecker
	bool testPass;
	testPass = th.matrixChecker(matlabSettingsLow_SR441, c.getSystemMatrix());
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}

/*
Test the system matrix against expected values (from matlab) with Low settings for fuzz vol and sample rate 48000
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixLow_SR48) {
	//Create an instance of Circuit with default Samplerate
	Circuit c(SR48);
	//Set Fuzz and Vol settings
	c.setFuzz(fuzzLow);
	c.setVol(volLow);

	//Create the testPass flag used to store result of matrixChecker
	bool testPass;
	testPass = th.matrixChecker(matlabSettingsLow_SR48, c.getSystemMatrix());
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}

/*
Test the system matrix against expected values (from matlab) with Low settings for fuzz vol and sample rate 96000
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixLow_SR96) {
	//Create an instance of Circuit with default Samplerate
	Circuit c(SR96);
	//Set Fuzz and Vol settings
	c.setFuzz(fuzzLow);
	c.setVol(volLow);

	//Create the testPass flag used to store result of matrixChecker
	bool testPass;
	testPass = th.matrixChecker(matlabSettingsLow_SR96, c.getSystemMatrix());
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}


/*
Test the system matrix against expected values (from matlab) with High settings for fuzz vol and sample rate 44100
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixHigh_SR441) {
	//Create an instance of Circuit with default Samplerate
	Circuit c(SR441);
	//Set Fuzz and Vol settings
	c.setFuzz(fuzzHigh);
	c.setVol(volHigh);

	//Create the testPass flag used to store result of matrixChecker
	bool testPass;
	testPass = th.matrixChecker(matlabSettingsHigh_SR441, c.getSystemMatrix());
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}

/*
Test the system matrix against expected values (from matlab) with High settings for fuzz vol and sample rate 48000
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixHigh_SR48) {
	//Create an instance of Circuit with default Samplerate
	Circuit c(SR48);
	//Set Fuzz and Vol settings
	c.setFuzz(fuzzHigh);
	c.setVol(volHigh);

	//Create the testPass flag used to store result of matrixChecker
	bool testPass;
	testPass = th.matrixChecker(matlabSettingsHigh_SR48, c.getSystemMatrix());
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);


}

/*
Test the system matrix against expected values (from matlab) with High settings for fuzz vol and sample rate 96000
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixHigh_SR96) {
	//Create an instance of Circuit with default Samplerate
	Circuit c(SR96);
	//Set Fuzz and Vol settings
	c.setFuzz(fuzzHigh);
	c.setVol(volHigh);

	//Create the testPass flag used to store result of matrixChecker
	bool testPass;
	testPass = th.matrixChecker(matlabSettingsHigh_SR96, c.getSystemMatrix());
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);


}




