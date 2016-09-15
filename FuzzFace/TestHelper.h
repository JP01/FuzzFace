#pragma once
//Helper Class used in testing, contains methods for matrix reading and checking

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "Circuit.h"
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "Eigen/Dense"
#include "Simulation.h"


const double ERROR = 1e-5; //acceptable error used when comparing matlab data to plugin data
const double acceptableErrorPercentage = 0.001; //acceptable % error in values

/*
Use matrix values from Matlab with default settings to create testMatrix
Algorithm:

Output system matrix to a file from matlab
Parse file data into a Vector

for each element in Vector
{
if testMatrix(indexValue) == systemMatrix(i,o)
continue;
else
print("An error occured, " << testMatrix(i,o) << " does not equal " << systemMatrix(i,o);
}

*/


class TestHelper
{
public:
	TestHelper();
	~TestHelper();

	const double acceptableError = ERROR;

	//Set the path to the folder where the matlab results are stored
	std::string folder = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/";

	//Read matrix data from a file and return it as a vector of type double
	std::vector<double> readMatrixData(std::string fileName);
	
	//Write matrix data to a file
	void writeMatrixData(Eigen::MatrixXf inputMatrix, std::string fileName);

	//Write vector data to file, includes sample number
	void writeVectorData(Eigen::MatrixXf inputMatrix, std::string fileName);

	//Takes a data set produced from matlab and a matrix of doubles and compares them, returns true if they are the same, starting at sample index startingIndex (USED FOR TESTING THE 
	//SIMULATION.CPP AS THE FIRST ~9000 SAMPLES MAY BE INNACURATE)
	bool matrixChecker(std::string matlabData, Eigen::MatrixXf inputMatrix, int startingIndex);

	//Takes a data set produced from matlab and a matrix of floats and compares them, returns true if they are the same (USED FOR MOST TESTS)
	bool matrixCheckerFloat(std::string matlabData, Eigen::MatrixXf inputMatrix);
	//matrix checker for doubles
	bool matrixChecker(std::string matlabData, Eigen::MatrixXd inputMatrix);

	//Helper Method to generate sin input
	Eigen::VectorXf generateSin(double _sampleRate, double _frequency, double _duration, double _amplitude);
	


};

