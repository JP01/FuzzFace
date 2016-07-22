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
		vol = 0.9;
		fuzz = 0.9;

		std::cout << "Circuit Created" << std::endl;
	
		//Create Circuit Matrices
		updateCircuitMatrices();
		initialiseIncidentMatrices();
		setupSystemMatrix();
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
	capMatrix << (2*c1)/T, (2*c2)/T, (2*c3)/T;

	//Convert the matrices to diagonal matrices
	diagResMatrix = resMatrix.asDiagonal();
	diagCapMatrix = capMatrix.asDiagonal();

	
}

void Circuit::initialiseIncidentMatrices() {
	
	//The incident matrix for the resistors
	incidentResistors << 
		0, 0,-1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0,-1, 1, 0, 0, 0, 0,
		0, 0, 0, 1, 0,-1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1,-1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		0, 1, 0, 0, 0, 0,-1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1,-1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0, 0;

	incidentCapacitors <<
		1,-1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0,-1, 0;

	incidentVoltage <<
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0,-1, 0, 0, 0, 0, 0, 0;

	incidentNonlinearities <<
		0, -1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, -1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, -1, 0, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, -1, 0, 1, 0, 0, 0;

	incidentOutput <<
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1;
}

void Circuit::setupSystemMatrix() {
	
}

/* Returns the current diagonal resistor matrix */

/* create the setter for the diagon capacitor matrix*/

/* Returns the current diagonal capacitor matrix*/


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
