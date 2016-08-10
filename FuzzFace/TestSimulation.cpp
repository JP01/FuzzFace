#define BOOST_TEST_MAIN
#include "TestHelper.h"

/*Test Cases to test each value and intermediate calculation value in the simulation class 
by comparing with Matlab results */

//As the matlab results are based on a loop, while this project uses real time, all matlab results
//are obtained from the first iteration of the simulation loop (IE the first sample) (WIP)
// Possibly test when input = 0 and when input = 1;



//Test the setting of the nonLinSolverInput variable with input 0.5;
//Should be comparable to the matlab result for "pd"
BOOST_AUTO_TEST_CASE(testInitialNonLinSolverInputMed) {
	Simulation s;
	//Input the data to the system
	s.process();

	//return the specified variable
	s.getCalculationVariable(8);

	//compare with matlab result

}