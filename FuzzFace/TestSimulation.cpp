#define BOOST_TEST_MAIN
#include "TestHelper.h"

/*Test Cases to test each value and intermediate calculation value in the simulation class 
by comparing with Matlab results */

//As the matlab results are based on a loop, while this project uses real time, all matlab results
//are obtained from the first iteration of the simulation loop (IE the first sample) (WIP)
// Possibly test when input = 0 and when input = 1;
TestHelper th;
double sampleRate = 44100*2;
double frequency = 100;
double duration = 0.4;
double amplitude = 0.1;
double vcc = 9;

Eigen::VectorXd sinInput;
Eigen::VectorXd systemOutput;

//location of matlab output files
std::string matlab_F06_V04_output = "C:/Users/the_m/Desktop/Masters Project Docs/PluginCreation/FuzzFace/FuzzFace/matlab_F06_V04_output.txt";


//Test the setting of the nonLinSolverInput variable;
//Should be comparable to the matlab result for "pd"
BOOST_AUTO_TEST_CASE(testOutputDefaultFuzzVol) {
	
	//Instance of simulation
	Simulation s(sampleRate,vcc);
	//generate the sin input
	sinInput = th.generateSin(sampleRate, frequency, duration, amplitude);
	//Resize the output to match the input
	systemOutput.resizeLike(sinInput);
		
	//process the buffer
	systemOutput = s.processBuffer(sinInput);

	/*
	//compare with matlab result
	bool testPass;
	testPass = th.matrixChecker(matlab_F06_V04_output, systemOutput);

	BOOST_CHECK_EQUAL(testPass, true);
	*/
	
}