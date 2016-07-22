#include "Circuit.h"
#include <iostream>

double vol;
double fuzz;
//Default Constructor
Circuit::Circuit() {
	//Initialise controllable paramaters
	vol = 0.9;
	fuzz = 0.9;
	std::cout << "Circuit Created" << std::endl;
	
}

//Create a setter for the Fuzz parameter, with exception handling when input is outside the allowable range 0 > fuzz >= 1
void Circuit::setFuzz(double fuzzVal) {
	if (fuzzVal > 0 && fuzzVal <= 1) {
		fuzz = fuzzVal;
	}
	else {
		//throw some exception
	}
}

//Returns the current value for the fuzz setting
double Circuit::getFuzz() 
{
	return fuzz;
}

//Create a setter for the Vol parameter, with exception handling when input is outside the allowable range 0 > vol >= 1
void Circuit::setVol(double volVal) {
	if (volVal > 0 && volVal <= 1) {
		vol = volVal;
	}
	else {
		//throw some exception
	}
}

//Returns the current value for the vol setting
double Circuit::getVol() 
{
	return vol;
}

//Default Destructor
Circuit::~Circuit() {
	//Cleanup
	std::cout << "Circuit Destroyed"<< std::endl;
}
