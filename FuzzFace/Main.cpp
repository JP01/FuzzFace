#include <iostream>
#include "Circuit.h"
#include "Simulation.h"
#define tableSize 44100



void main() {
	std::cout << "Main program" << std::endl;

	Circuit c;
	Simulation s;
	double fuzz = 0.5;
	double vol = 0.5;
	fuzz = c.getFuzz();
	vol = c.getVol();

	std::cout << "The current fuzz is : " << fuzz << std::endl;
	std::cout << "The current vol is : " << vol << std::endl;


	double twoPi = 3.14159 * 2;

	double samples[tableSize];
	double increment = twoPi / tableSize;
	double currentPhase = 0.0;

	Eigen::VectorXd t(tableSize);

	double T = 1 / 44100.;

	//populate the sin wave sample data
	for (int i = 0; i < tableSize - 1; i++)
	{
		t(i) = i*T;
		samples[i] = 0.2 * sin(twoPi * 100 * t(i));
	}

	for (int i = 0; i < 10; i++) {
		
		std::cout << s.process(samples[i]) << std::endl;
	}

	

	
	

	//std::cout << "The output is : " << answer << std::endl;
}