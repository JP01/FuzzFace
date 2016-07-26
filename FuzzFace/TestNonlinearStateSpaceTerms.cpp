#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "Circuit.h"
#include "TestHelper.h"
#include "Eigen/Dense"



BOOST_AUTO_TEST_CASE(testNonLinearMatrixA) {
	
	Circuit c;
	TestHelper th;


	std::string filePath = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/systemMatrixFromMatlab_F_60_V_40_SR_44100.txt";
	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> inputMatrix;
	inputMatrix = c.getSystemMatrix();

	bool testPass = true;
	testPass = th.matrixChecker(filePath, c.getSystemMatrix());

	BOOST_CHECK_EQUAL(testPass, true);
}