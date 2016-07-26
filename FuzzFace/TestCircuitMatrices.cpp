//#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "Circuit.h"
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "Eigen/Dense"

/*Helper Function*/
//Read matrix data from a file and return it as a vector of type T
template<typename T>
std::vector<T> readMatrixData(std::string filename)
{
	std::ifstream infile(filename, std::ios::in);  //the input data
	std::vector<T> data;  //the return vector

						  //check file can be opened / is opened
	if (!infile.is_open())
	{
		//print error if one occurs
		std::cerr << "Threre was a problem opening the input file!\n";
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
Test the system matrix against expected values (from matlab) with default settings for fuzz vol and sample rate
*/
BOOST_AUTO_TEST_CASE(testSystemMatrixDefaultFuzzVolSR) {
	/*TestCase setup*/
	//Create an instance of circuit
	Circuit c;
	const int totalRows = 12;  //number of rows in the matlab matrix
	const int totalCols = 12;  //number of columns in the matlab matrix
	Eigen::Matrix<double, totalRows, totalCols> circuitSystemMatrix;
	
	//set the circuitSystemMatrix equal to the result of c.getSystemMatrix()
	circuitSystemMatrix = c.getSystemMatrix();
	
	//create a vector to store the matlab generated matrix
	std::vector<double> matlabResults;
	//put the matlab results into the vector
	matlabResults = readMatrixData<double>("C:/Users/the_m/Desktop/Masters Project Docs/Matlab/systemMatrixFromMatlab_F_06_V_04_SR_44100.txt");


	/* Test case processing */
	int resultIndex = 0; //the index from the vector matlabResults
	bool testPass = true; //Boolean flag used to determine the outcome of the testcase
	
	//Loop through all values of matlabResults and circuitSystemMatrix, Check corresponding values are equal and output error if not
	for (int row = 0; row < totalRows; row++)
	{
		for (int col = 0; col < totalCols; col++) {
			//Check if the value at matlabResult[resultIndex] is equal to the corresponding value in the c.getSystemMatrix()
			if (matlabResults[resultIndex] == circuitSystemMatrix(row, col)) {
				std::cout << "Pass\n";  //if true then print pass
			}
			else {
				//if false, print error and erronious data
				std::cout << "An error occured, " << matlabResults[resultIndex] << " does not equal " << circuitSystemMatrix(row, col) << std::endl;
				//set the testPass to false, letting Boost know the testcase has failed
				testPass = false;
			}

			resultIndex++;  //increment the resultIndex to move to next value in the matlabResults vector
		}

	}

	//If testPass is true, then pass the test case. If testPass has been set to false, then fail the testcase
	BOOST_CHECK_EQUAL(testPass, true);



}
