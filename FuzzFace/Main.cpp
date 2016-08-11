#include <iostream>
#include "Circuit.h"
#include "Simulation.h"




void main() {
	std::cout << "Main program" << std::endl;
	double sampleRate = 44100;
	double vcc = 9;
	Simulation s(sampleRate, vcc);

	//Create a vector to store sin input and time vector
	Eigen::VectorXd sinWaveInput;
	Eigen::VectorXd timeVector;
	//Attributes of the input sin wave
	double durationOfSin = 0.4;
	double amplitude = 0.01;
	double frequency = 100;

	//Number of samples 
	int numberOfSamples = sampleRate * durationOfSin;

	//Resize the input vectors
	sinWaveInput.resize(numberOfSamples);
	timeVector.resize(numberOfSamples);

	//input the data into the vector
	for (int i = 0; i < numberOfSamples-1; i++) {
		timeVector(i) = i*(1/sampleRate);
		sinWaveInput(i) = amplitude * sin(2 * PI*frequency*timeVector(i));
	}


	//process the first few samples
	for (int i = 0; i < numberOfSamples; i++) {
		std::cout<< "Sample: " << i << ", output = " << s.processSample(sinWaveInput(i), vcc) << std::endl;
	}
	

	
} 