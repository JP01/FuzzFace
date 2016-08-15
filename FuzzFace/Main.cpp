#include <iostream>
#include "Circuit.h"
#include "Simulation.h"
#include <fstream>

//Write matrix data to a file
void writeMatrixData(Eigen::MatrixXd inputMatrix, std::string fileName) {
	std::ofstream myfile(fileName);

	//checks file open
	if (myfile.is_open())
	{
		myfile << inputMatrix;
		myfile.close();
	}
	//error message if file unable to open
	else {
		std::cout << "Unable to open file";
	}
}

//Write matrix data to a file includes sample number
void writeVectorData(Eigen::MatrixXd inputMatrix, std::string fileName) {
	std::ofstream myfile(fileName);

	//checks file open
	if (myfile.is_open())
	{
		//for each element in input vector, write the sample number and output the value
		for (int i = 0; i < inputMatrix.size(); i++)
		{
			myfile << "Sample " << i + 1 << ": " << inputMatrix(i) << std::endl;
		}
		myfile.close();

	}
	//error message if file unable to open
	else {
		std::cout << "Unable to open file";
	}
}

//Helper Method to generate sin input
Eigen::VectorXd generateSin(double _sampleRate, double _frequency, double _duration, double _amplitude) {
	//Create a vector to store sin input and time vector
	Eigen::VectorXd sinWaveVector;
	Eigen::VectorXd timeVector;
	//Attributes of the input sin wave

	//Number of samples rounded up to the nearest whole integer
	double numberOfSamples = ceil(_sampleRate * _duration);

	//Resize the input vectors
	sinWaveVector.resize(numberOfSamples);
	timeVector.resize(numberOfSamples);

	//input the data into the vector
	for (int i = 0; i < numberOfSamples - 1; i++) {
		timeVector(i) = i*(1 / _sampleRate);
		sinWaveVector(i) = _amplitude * sin(2 * PI*_frequency*timeVector(i));
	}

	return sinWaveVector;
}

void main() {
	std::cout << "Main program" << std::endl;
	double sampleRate = 96000;
	double frequency = 100;
	double duration = 1;
	double amplitude = 0.1;
	double vcc = 9;

	Eigen::VectorXd sinInput;
	Eigen::VectorXd systemOutput;

	//Instance of simulation
	Simulation s(sampleRate, vcc);

	//generate the sinwave input
	sinInput = generateSin(sampleRate, frequency, duration, amplitude);

	//Resize the output to match the input
	systemOutput.resizeLike(sinInput);

	//*set up timing signatures
	time_t timer;
	time_t timeBefore = time(&timer);
	std::cout << "timeBefore processBuffer = " << timeBefore << std::endl;

	systemOutput = s.processBuffer(sinInput);

	//Output the time taken to process the buffer
	time_t timeAfter = time(&timer);
	std::cout << "timeAfter processBuffer = " << timeAfter << std::endl;
	std::cout << "Time taken to compute the buffer: " << timeAfter - timeBefore << " seconds" << std::endl;

	writeMatrixData(sinInput, "cppSinInput.txt");
	writeVectorData(sinInput, "cppSinInputWithSampleNum.txt");
	writeVectorData(systemOutput, "outputWithSampleNumber.txt");
	writeMatrixData(systemOutput, "output.txt");

	//compare with matlab result	
} 

