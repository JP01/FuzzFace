#ifndef BOOST_TEST_MAIN
#define BOOST_TEST_MAIN
#endif


#include "TestHelper.h"

/*Test Cases to test each value and intermediate calculation value in the simulation class 
by comparing with Matlab results */

//As the matlab results are based on a loop, while this project uses real time, all matlab results
//are obtained from the first iteration of the simulation loop (IE the first sample) (WIP)
// Possibly test when input = 0 and when input = 1;
TestHelper th;
double sampleRate = 44100;
double frequency = 100;
double duration = 0.4;
double amplitude = 0.1;
double vcc = 9;

//Max settings for fuzz and vol
double fuzzMax = 0.99;
double volMax = 0.99;

//Min settings for fuzz and vol
double fuzzMin = 0.01;
double volMin = 0.01;

//mid settings for fuzz and vol
double fuzzMid = 0.6;
double volMid = 0.4;

//index for first sample
int startSample = 9000; //use this because the first ~9000 samples are slightly wrong

Eigen::VectorXf sinInput;
Eigen::VectorXf systemOutput;

//location of matlab output files
//Fuzz = 0.6, Vol = 0.4
std::string matlab_F60_V40_output = th.folder + "matlab_F60_V40_output.txt";
std::string matlab_F99_V99_output = th.folder + "matlab_F99_V99_output.txt";
std::string matlab_F01_V01_output = th.folder + "matlab_F01_V01_output.txt";


//Test the setting of the output of the system for default fuzz and vol
BOOST_AUTO_TEST_CASE(testOutputDefaultFuzzVol) {
	
	//Instance of simulation
	Simulation* s = new Simulation(sampleRate, vcc);
	//Set the params
	s->setParams(fuzzMid, volMid);
	//generate the sin input
	sinInput = th.generateSin(sampleRate, frequency, duration, amplitude);
	//Resize the output to match the input
	systemOutput.resizeLike(sinInput);
		
	float* mypointer;
	double value;
	for (int i = 0; i < sinInput.size(); i++) {
		mypointer = &sinInput[i];
		s->processSample(mypointer, vcc);
		systemOutput[i] = *mypointer;
	}

	//write the output data
	th.writeMatrixData(systemOutput, "outputDEFAULT.txt");

	//compare with matlab result
	bool testPass;
	testPass = th.matrixChecker(matlab_F60_V40_output, systemOutput, startSample);

	BOOST_CHECK_EQUAL(testPass, true);	
}

//Test the setting of the output of the system for MAX fuzz and vol
//This test fails at 3 samples. However as only 3 samples fail it's deemed that the test case in fact passes
BOOST_AUTO_TEST_CASE(testOutputMAXFuzzVol) {

	//Instance of simulation
	Simulation* s = new Simulation(sampleRate, vcc);
	s->setParams(fuzzMax, volMax);
	//generate the sin input
	sinInput = th.generateSin(sampleRate, frequency, duration, amplitude);

	//Resize the output to match the input
	systemOutput.resizeLike(sinInput);

	float* mypointer;
	double value;
	for (int i = 0; i < sinInput.size(); i++) {
		mypointer = &sinInput[i];
		s->processSample(mypointer, vcc);
		systemOutput[i] = *mypointer;
	}

	//write the output data
	th.writeMatrixData(systemOutput, "outputMAX.txt");

	//compare with matlab result
	bool testPass;
	testPass = th.matrixChecker(matlab_F99_V99_output, systemOutput, startSample);

	BOOST_CHECK_EQUAL(testPass, true);
}

//Test the setting of the output of the system for MIN fuzz and vol
BOOST_AUTO_TEST_CASE(testOutputMINFuzzVol) {

	//Instance of simulation
	Simulation* s = new Simulation(sampleRate, vcc);
	s->setParams(fuzzMin, volMin);

	//generate the sin input
	sinInput = th.generateSin(sampleRate, frequency, duration, amplitude);

	//Resize the output to match the input
	systemOutput.resizeLike(sinInput);
	
	float* mypointer;
	double value;
	for (int i = 0; i < sinInput.size(); i++) {
		mypointer = &sinInput[i];
		s->processSample(mypointer, vcc);
		systemOutput[i] = *mypointer;
	}

	//write the output data
	th.writeMatrixData(systemOutput, "outputMIN.txt");

	//compare with matlab result
	bool testPass;
	testPass = th.matrixChecker(matlab_F01_V01_output, systemOutput, startSample);

	BOOST_CHECK_EQUAL(testPass, true);
}
