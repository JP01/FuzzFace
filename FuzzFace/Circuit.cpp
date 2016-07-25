#include "Circuit.h"
#include <iostream>
#include "Eigen/Dense"

/*Default Constructor*/
//Circuit::Circuit() { std::cout << "Circuit Created!" << std::endl; };

/*Calls the default constructor with default 44.1k Hz sample rate */
Circuit::Circuit() : Circuit(44100.) {};

/*Constructor which takes sampleRate as an arguement and initialises the sampling period T to 1./sampleRate */
Circuit::Circuit(double sampleRate) :T(1./sampleRate){

		//Initialise controllable paramaters
		setVol(0.9);
		setFuzz(0.9);

		std::cout << "Circuit Created" << std::endl;
	
		//Initialise the incident matrices
		initialiseIncidentMatrices();

		//Initialise the system matrix
		refreshSystemMatrix();
}

/*Function to populate the circuit matrices*/
void Circuit::updateCircuitMatrices() {
	
	//Update the resistor values
	r4 = (1 - vol)*500e3;
	r5 = vol*500e3;
	r7 = fuzz*1e3;
	r8 = (1 - fuzz)*1e3;

	//prep the resistor values for input into the diagonal matrix
	resMatrix << 1 / r1, 1 / r2, 1 / r3, 1 / r4, 1 / r5, 1 / r6, 1 / r7, 1 / r8;

	//prep the capacitor values for input into diagonal matrix
	capMatrix << c1,c2,c3;
	capMatrix = (2 * capMatrix) / T;
	
	//Convert the matrices to diagonal matrices
	diagResMatrix = resMatrix.asDiagonal();
	diagCapMatrix = capMatrix.asDiagonal();

	
}

/* Function used to refresh the system matrix, call when fuzz or vol is changed */
void Circuit::refreshSystemMatrix() {
	//Update the circuit matrices
	updateCircuitMatrices();
	
	//Update the matrix systemRes with the resistor element of the system Matrix
	systemRes = (incidentResistors.transpose())*diagResMatrix*incidentResistors;

	//Update the matrix systemCap with the capacitor element of the system Matrix
	systemCap = (incidentCapacitors.transpose())*diagCapMatrix*incidentCapacitors;

	//Construct system matrix
	systemMatrix.block(0, 0, numNodes, numNodes) = systemRes + systemCap;  //sets the first 10x10 top left matrix to be the sum of systemRes and systemCap matrices
	systemMatrix.block(0, numNodes, numNodes, numInputs) = incidentVoltage.transpose();  //sets the 10x2 matrix starting at (0,10) equal to the transpose of incidentVoltage matrix
	systemMatrix.block(numNodes, 0, numInputs, numNodes) = incidentVoltage;  //sets the 2x10 matrix starting at (10,0) equal to the incidentVoltage matrix
	systemMatrix.block(numNodes, numNodes, numInputs, numInputs).setZero();  //sets the last 2x2 matrix in the bottom right corner to 0

	std::cout << systemMatrix << std::endl;


}

/* Create a setter for the Fuzz parameter, when input is outside the allowable range 0 > fuzzVal >= 1, default to 0.6 */
void Circuit::setFuzz(double fuzzVal) {
	//Checks fuzzVal is within allowable range
	if (fuzzVal > 0 && fuzzVal <= 1) {
		fuzz = fuzzVal;
	}
	else {
		//Defaults value to 0.6 and prints a message
		std::cout << "Fuzz out of range, defaulted to 0.6" << std::endl;
		fuzz = 0.6;
	}
}

/* Returns the current value for the fuzz setting */
double Circuit::getFuzz() 
{
	return fuzz;
}

/* Create a setter for the Vol parameter, when input is outside the allowable range 0 > volVal >= 1, default to 0.4 */
void Circuit::setVol(double volVal) {
	//Checks volVal is within allowable range
	if (volVal > 0 && volVal <= 1) {
		vol = volVal;
	}
	else {
		//Defaults value to 0.4 and prints a message
		std::cout << "Vol out of range, defaulted to 0.4" << std::endl;
		vol = 0.4;
	}
}

/* Returns the current value for the vol setting*/
double Circuit::getVol() 
{
	return vol;
}

/*Default Destructor */
Circuit::~Circuit() {
	//Cleanup
	std::cout << "Circuit Destroyed"<< std::endl;
}
