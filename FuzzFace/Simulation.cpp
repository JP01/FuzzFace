#include "Simulation.h"

//Default Constructor
Simulation::Simulation()
{
	initialiseSimulationParameters();
	setup();
}

void Simulation::setup() 
{
	simStateSpaceG = simCircuit.getStateSpaceMatrix("G");
	simStateSpaceH = simCircuit.getStateSpaceMatrix("H");

	simAlteredStateSpaceK = simCircuit.getNonlinearFunctionMatrix("altered");
	simNonLinEquationMatrix = simCircuit.getNonlinearFunctionMatrix("M");

	simSaturationCurrent = simCircuit.getSaturationCurrent();
	simThermalVoltage = simCircuit.getThermalVoltage();

}

//Initialise the matrices used in the simulation
void Simulation::initialiseSimulationParameters() {
	//Set up a 4x1 Vector pdNull and sets all vals to 0
	nonLinSolverInputNull.setZero();

	//Set up a 3x1 vector stateVector and set all vals to 0
	stateSpaceVectorMem.setZero();

	//Set up a 4x1 vector vdVector and set all vals to 0
	nonLinVoltageVector.setZero();

	//Set up a 2x1 vector inputVector and set all vals to 0
	inputVector.setZero();

	//Set up a 1xbufferSize RowVector iteration collection and set all vals to 0
	iterationCollection.resize(bufferSize);
	iterationCollection.setZero();

	//Set up a 1xbufferSize Rowvector subiteration collection and set all vals to 0
	subIterationCollection.resize(bufferSize);
	subIterationCollection.setZero();

	//set up a NumNonLin x bufferSize Matrix current collection and set all vals to 0
	currentCollection.resize(numNonLin, bufferSize);
	currentCollection.setZero();

	//Set up a numNonLin x bufferSize Matrix auxSignalCollection and set all vals to 0
	auxSignalCollection.resize(numNonLin, bufferSize);
	auxSignalCollection.setZero();


}

//Sets the buffersize to the specified number of samples
void Simulation::setBufferSize(int bufferSize) {
	Simulation::bufferSize = bufferSize;
}

double Simulation::process(double channelData) {

	inputVector(0) = channelData; //sets the input vector equal to the input channelData

	//Prepare the nonlinear solver
	nonLinSolverInput = (simAlteredStateSpaceK.inverse())*(simStateSpaceG*stateSpaceVectorMem + simStateSpaceH*inputVector);
	nrms = 1.;
	iteration = 0;
	subIteration = 0;

	while (nrms > tols && iteration < maxIterations) {
		calcTemp = simSaturationCurrent*matrixExp(nonLinVoltageVector / simThermalVoltage);
		nonLinTransistorFunction = addToEveryValue(calcTemp, -simSaturationCurrent);
		
	}
	
	return output; //returns the processed sample
}

// Add valueToAdd to every value in the matrix input
Eigen::MatrixXd Simulation::addToEveryValue(Eigen::MatrixXd input, double valueToAdd) {
	//For each value in the matrix, add valueToAdd
	for (int row = 0; row < input.rows(); row++) {
		for (int col = 0; col < input.cols(); col++) {
			double temp = 0;
			temp = input(row, col);
			temp = temp + valueToAdd;
			input(row, col) = temp;
		}
	}
	return input;
}

//Return the exponential of each value in matrix
Eigen::MatrixXd Simulation::matrixExp(Eigen::MatrixXd input) {
	//For each value in the matrix, change it to exp(value)
	for (int row = 0; row < input.rows(); row++) {
		for (int col = 0; col < input.cols(); col++) {
			double temp = 0;
			temp = input(row, col);
			temp = exp(temp);
			input(row, col) = temp;
		}
	}
	return input;
}

//Default Destructor
Simulation::~Simulation()
{
}
