#include "Simulation.h"



Simulation::Simulation()
{
}


Simulation::~Simulation()
{
}


void Simulation::initialiseSimulationParameters() {
	//Set up a 4x1 Vector pdNull and sets all vals to 0
	pdNull.resize(4);
	pdNull.setZero();

	//Set up a 3x1 vector stateVector and set all vals to 0
	stateVector(3);
	stateVector.setZero();

	//Set up a 4x1 vector vdVector and set all vals to 0
	vdVector(4);
	vdVector.setZero();

	//Set up a 2x1 vector inputVector and set all vals to 0
	inputVector(2);
	inputVector.setZero();

	//Set up a 1xbufferSize RowVector iteration collection

}