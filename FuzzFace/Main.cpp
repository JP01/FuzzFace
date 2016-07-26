#include <iostream>
#include "Circuit.h"





void main() {
	std::cout << "Main program" << std::endl;

	Circuit c;
	double fuzz = 0.5;
	double vol = 0.5;
	fuzz = c.getFuzz();
	vol = c.getVol();

	std::cout << "The current fuzz is : " << fuzz << std::endl;
	std::cout << "The current vol is : " << vol << std::endl;

}