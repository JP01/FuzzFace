#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "Circuit.h"
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "Eigen/Dense"

/*Helper Functions*/

const int totalRows = 12;  //number of rows in the matlab matrix
const int totalCols = 12;  //number of columns in the matlab matrix

//Read matrix data from a file and return it as a vector of type T
template<typename T>
std::vector<T> readMatrixData(std::string fileName)
{
	std::ifstream infile(fileName, std::ios::in);  //the input data
	std::vector<T> data;  //the return vector

						  //check file can be opened / is opened
	if (!infile.is_open())
	{
		//print error if one occurs
		std::cerr << "Threre was a problem opening the input file!\n" << fileName << std::endl;
	}
	else //if no error then...
	{
		double num = 0.0; //initialise the num variable
		while (infile >> num)  //store values from textfile while data exists
		{
			data.push_back(num);
		}
	}

	//return the vector storing the data from the file
	return data;
}

/*Checks the input data against the systemMatrix with input values of fuzz vol and samplerate*/
bool systemMatrixChecker(std::string matlabData, double fuzz, double vol, double sampleRate) {
	/*TestCase setup*/
	//Create an instance of circuit
	Circuit c(sampleRate);
	c.setFuzz(fuzz);
	c.setVol(vol);

	Eigen::Matrix<double, totalRows, totalCols> circuitSystemMatrix;

	//set the circuitSystemMatrix equal to the result of c.getSystemMatrix()
	circuitSystemMatrix = c.getSystemMatrix();

	//create a vector to store the matlab generated matrix
	std::vector<double> matlabResults;
	//put the matlab results into the vector
	matlabResults = readMatrixData<double>(matlabData);


	/* Test case processing */
	int resultIndex = 0; //the index from the vector matlabResults
	bool testPass = true; //Boolean flag used to determine the outcome of the testcase

						  //Loop through all values of matlabResults and circuitSystemMatrix, Check corresponding values are equal and output error if not
	for (int row = 0; row < totalRows; row++)
	{
		for (int col = 0; col < totalCols; col++) {
			//Check if the value at matlabResult[resultIndex] is equal to the corresponding value in the c.getSystemMatrix()
			if (matlabResults[resultIndex] != circuitSystemMatrix(row, col)) {
				//if false, print error and erronious data
				std::cout << "An error occured, " << matlabResults[resultIndex] << " does not equal " << circuitSystemMatrix(row, col) << std::endl;
				//set the testPass to false, letting Boost know the testcase has failed
				testPass = false;
			}

			resultIndex++;  //increment the resultIndex to move to next value in the matlabResults vector
		}

	}

	return testPass;
}

/*
Use System matrix values from Matlab with default settings to create testMatrix
Algorithm:

Output system matrix to a file from matlab
Parse file data into a 12x12 array/matrix

	for each element in 12x12
	{
		if testMatrix(i,o) == systemMatrix(i,o)
			continue;
		else 
			print("An error occured, " << testMatrix(i,o) << " does not equal " << systemMatrix(i,o);
	}



*/


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




/*
Test the system matrix against expected values (from matlab) with default settings for fuzz vol and sample rate 44100
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixDefault_SR441) {
	bool testPass;
	testPass = systemMatrixChecker(matlabSettingsDefault_SR441, fuzzDefault, volDefault, SR441);
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}

/*
Test the system matrix against expected values (from matlab) with default settings for fuzz vol and sample rate 48000
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixDefault_SR48) {
	bool testPass;
	testPass = systemMatrixChecker(matlabSettingsDefault_SR48, fuzzDefault, volDefault, SR48);
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}

/*
Test the system matrix against expected values (from matlab) with default settings for fuzz vol and sample rate 96000
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixDefault_SR96) {
	bool testPass;
	testPass = systemMatrixChecker(matlabSettingsDefault_SR96, fuzzDefault, volDefault, SR96);
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}


/*
Test the system matrix against expected values (from matlab) with Low settings for fuzz vol and sample rate 44100
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixLow_SR441) {
	bool testPass;
	testPass = systemMatrixChecker(matlabSettingsLow_SR441, fuzzLow, volLow, SR441);
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}

/*
Test the system matrix against expected values (from matlab) with Low settings for fuzz vol and sample rate 48000
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixLow_SR48) {
	bool testPass;
	testPass = systemMatrixChecker(matlabSettingsLow_SR48, fuzzLow, volLow, SR48);
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}

/*
Test the system matrix against expected values (from matlab) with Low settings for fuzz vol and sample rate 96000
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixLow_SR96) {
	bool testPass;
	testPass = systemMatrixChecker(matlabSettingsLow_SR96, fuzzLow, volLow, SR96);
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}


/*
Test the system matrix against expected values (from matlab) with High settings for fuzz vol and sample rate 44100
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixHigh_SR441) {
	bool testPass;
	testPass = systemMatrixChecker(matlabSettingsHigh_SR441, fuzzHigh, volHigh, SR441);
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}

/*
Test the system matrix against expected values (from matlab) with High settings for fuzz vol and sample rate 48000
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixHigh_SR48) {
	bool testPass;
	testPass = systemMatrixChecker(matlabSettingsHigh_SR48, fuzzHigh, volHigh, SR48);
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}

/*
Test the system matrix against expected values (from matlab) with High settings for fuzz vol and sample rate 96000
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixHigh_SR96) {
	bool testPass;
	testPass = systemMatrixChecker(matlabSettingsHigh_SR96, fuzzHigh, volHigh, SR96);
	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);

}




