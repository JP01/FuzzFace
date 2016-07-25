#include <boost/test/unit_test.hpp>
#include <iostream>
#include "Circuit.h"

/*
Using system matrix values obtained from matlab.
Where:
Fuzz = 0.6;
Vol = 0.4;
Samplerate = 44100;
*/


/*
Use System matrix values from Matlab with default settings to create testMatrix
*/
BOOST_AUTO_TEST_CASE(testRefreshSystemMatrix) {
	Eigen::Matrix<double, 12, 12> testMatrix;
	testMatrix <<
	0.19404,-0.19404,0,0,0,0,0,0,0,0,1,0,
	-0.19404,0.19405,0,0,0,0,-1.00E-05,0,0,0,0,0,
	0,0,3.0303E-05,-3.0303E-05,0,0,0,0,0,0,0,0,
	0,0,-3.0303E-05,0.00306061,0,-0.0030303,0,0,0,0,0,-1,
	0,0,0,0,0.000121951,-0.000121951,0,0,0,0,0,0,
	0,0,0,-0.0030303,-0.000121951,0.00403425,0,0,-0.000882,0,0,0,
	0,-1.00E-05,0,0,0,0,0.00167667,-0.00166667,0,0,0,0,
	0,0,0,0,0,0,-0.00166667,1.76817,0,0,0,0,
	0,0,0,0,0,-0.000882,0,0,0.000885333,-3.33333E-06,0,0,
	0,0,0,0,0,0,0,0,-3.33333E-06,8.33333E-06,0,0,
	1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,-1,0,0,0,0,0,0,0,0;


	Circuit c;
	if (testMatrix == c.getSystemMatrix()) {
		std::cout << "Passed";
	}
	else {
		std::cout << "Fail";
	}
	

}
