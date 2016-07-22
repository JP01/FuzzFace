#include <iostream>
#include "Circuit.h"

void main() {

	Circuit c;
	
	std::cout << "Main program" << std::endl;
	std::cout << "The current fuzz is : " << c.getFuzz() << std::endl;
	std::cout << "The current vol is : " << c.getVol() << std::endl;

	

}