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

std::string stateSpaceA = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/stateSpaceFromMatlabA.txt";
std::string stateSpaceB = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/stateSpaceFromMatlabB.txt";
std::string stateSpaceC = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/stateSpaceFromMatlabC.txt";
std::string stateSpaceD = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/stateSpaceFromMatlabD.txt";
std::string stateSpaceE = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/stateSpaceFromMatlabE.txt";
std::string stateSpaceF = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/stateSpaceFromMatlabF.txt";
std::string stateSpaceG = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/stateSpaceFromMatlabG.txt";
std::string stateSpaceH = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/stateSpaceFromMatlabH.txt";
std::string stateSpaceK = "C:/Users/the_m/Desktop/Masters Project Docs/Matlab/stateSpaceFromMatlabK.txt";


//Create an instance of Default Circuit and TestHelper
Circuit c;
TestHelper th;

/*Test the State Space Matrix A obtained from the matlab file by comparing with the corresponding C++ generated matrix */
BOOST_AUTO_TEST_CASE(testStateSpaceMatrixA) {
	//Create a matrix of doubles to store the result of c.getStateSpaceMatrix
	Eigen::MatrixXd testMatrix;
	testMatrix = c.getStateSpaceMatrix("A");

	bool testPass = true;
	testPass = th.matrixChecker(stateSpaceA, testMatrix);

	BOOST_CHECK_EQUAL(testPass, true);
}

/*Test the State Space Matrix B obtained from the matlab file by comparing with the corresponding C++ generated matrix */
BOOST_AUTO_TEST_CASE(testStateSpaceMatrixB) {
	//Create a matrix of doubles to store the result of c.getStateSpaceMatrix
	Eigen::MatrixXd testMatrix;
	testMatrix = c.getStateSpaceMatrix("B");

	bool testPass = true;
	testPass = th.matrixChecker(stateSpaceB, testMatrix);

	BOOST_CHECK_EQUAL(testPass, true);
}

/*Test the State Space Matrix C obtained from the matlab file by comparing with the corresponding C++ generated matrix */
BOOST_AUTO_TEST_CASE(testStateSpaceMatrixC) {
	//Create a matrix of doubles to store the result of c.getStateSpaceMatrix
	Eigen::MatrixXd testMatrix;
	testMatrix = c.getStateSpaceMatrix("C");

	bool testPass = true;
	testPass = th.matrixChecker(stateSpaceC, testMatrix);

	BOOST_CHECK_EQUAL(testPass, true);
}

/*Test the State Space Matrix D obtained from the matlab file by comparing with the corresponding C++ generated matrix */
BOOST_AUTO_TEST_CASE(testStateSpaceMatrixD) {
	//Create a matrix of doubles to store the result of c.getStateSpaceMatrix
	Eigen::MatrixXd testMatrix;
	testMatrix = c.getStateSpaceMatrix("D");

	bool testPass = true;
	testPass = th.matrixChecker(stateSpaceD, testMatrix);

	BOOST_CHECK_EQUAL(testPass, true);
}

/*Test the State Space Matrix E obtained from the matlab file by comparing with the corresponding C++ generated matrix */
BOOST_AUTO_TEST_CASE(testStateSpaceMatrixE) {
	//Create a matrix of doubles to store the result of c.getStateSpaceMatrix
	Eigen::MatrixXd testMatrix;
	testMatrix = c.getStateSpaceMatrix("E");

	bool testPass = true;
	testPass = th.matrixChecker(stateSpaceE, testMatrix);

	BOOST_CHECK_EQUAL(testPass, true);
}

/*Test the State Space Matrix F obtained from the matlab file by comparing with the corresponding C++ generated matrix */
BOOST_AUTO_TEST_CASE(testStateSpaceMatrixF) {
	//Create a matrix of doubles to store the result of c.getStateSpaceMatrix
	Eigen::MatrixXd testMatrix;
	testMatrix = c.getStateSpaceMatrix("F");

	bool testPass = true;
	testPass = th.matrixChecker(stateSpaceF, testMatrix);

	BOOST_CHECK_EQUAL(testPass, true);
}

/*Test the State Space Matrix G obtained from the matlab file by comparing with the corresponding C++ generated matrix */
BOOST_AUTO_TEST_CASE(testStateSpaceMatrixG) {
	//Create a matrix of doubles to store the result of c.getStateSpaceMatrix
	Eigen::MatrixXd testMatrix;
	testMatrix = c.getStateSpaceMatrix("G");

	bool testPass = true;
	testPass = th.matrixChecker(stateSpaceG, testMatrix);

	BOOST_CHECK_EQUAL(testPass, true);
}

/*Test the State Space Matrix H obtained from the matlab file by comparing with the corresponding C++ generated matrix */
BOOST_AUTO_TEST_CASE(testStateSpaceMatrixH) {
	//Create a matrix of doubles to store the result of c.getStateSpaceMatrix
	Eigen::MatrixXd testMatrix;
	testMatrix = c.getStateSpaceMatrix("H");

	bool testPass = true;
	testPass = th.matrixChecker(stateSpaceH, testMatrix);

	BOOST_CHECK_EQUAL(testPass, true);
}

/*Test the State Space Matrix K obtained from the matlab file by comparing with the corresponding C++ generated matrix */
BOOST_AUTO_TEST_CASE(testStateSpaceMatrixK) {
	//Create a matrix of doubles to store the result of c.getStateSpaceMatrix
	Eigen::MatrixXd testMatrix;
	testMatrix = c.getStateSpaceMatrix("K");

	bool testPass = true;
	testPass = th.matrixChecker(stateSpaceK, testMatrix);

	BOOST_CHECK_EQUAL(testPass, true);
}

