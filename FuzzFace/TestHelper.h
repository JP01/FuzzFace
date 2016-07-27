//Helper Class used in testing, contains methods for matrix reading and checking
#pragma once

#include <iostream>
#include "Circuit.h"
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "Eigen/Dense"

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

	double acceptableError;

	//Read matrix data from a file and return it as a vector of type double
	std::vector<double> readMatrixData(std::string fileName);

	//Takes a data set produced from matlab and a matrix of doubles and compares them, returns true if they are the same
	bool matrixChecker(std::string matlabData, Eigen::MatrixXd inputMatrix);
};

