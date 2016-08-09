#include "Simulation.h"

//Default Constructor
Simulation::Simulation()
{
	initialiseSimulationParameters();
	setup();
}

void Simulation::setup() 
{
	simCircuit.refreshAll();
	simStateSpaceA = simCircuit.getStateSpaceMatrix("A");
	simStateSpaceB = simCircuit.getStateSpaceMatrix("B");
	simStateSpaceC = simCircuit.getStateSpaceMatrix("C");
	simStateSpaceD = simCircuit.getStateSpaceMatrix("D");
	simStateSpaceE = simCircuit.getStateSpaceMatrix("E");
	simStateSpaceF = simCircuit.getStateSpaceMatrix("F");
	simStateSpaceG = simCircuit.getStateSpaceMatrix("G");
	simStateSpaceH = simCircuit.getStateSpaceMatrix("H");

	simPSI = simCircuit.getNonlinearFunctionMatrix("psi");
	simAlteredStateSpaceK = simCircuit.getNonlinearFunctionMatrix("alteredStateSpaceK");
	simNonLinEquationMatrix = simCircuit.getNonlinearFunctionMatrix("nonLinEquationMatrix");

	simSaturationCurrent = simCircuit.getSaturationCurrent();
	simThermalVoltage = simCircuit.getThermalVoltage();

}

//Initialise the matrices used in the simulation
void Simulation::initialiseSimulationParameters() {

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
	inputVector(1) = vcc;

	//Prepare the nonlinear solver
	nonLinSolverInput = (simAlteredStateSpaceK.inverse())*(simStateSpaceG*stateSpaceVectorMem + simStateSpaceH*inputVector); //define input to the Nonlinear equation --- MATLAB pd
	nonLinVoltageVectorPrev = nonLinVoltageVectorMem;	
	nrms = 1.;
	iteration = 0;
	subIteration = 0;

	nonLinVoltageVector = nonLinVoltageVectorPrev;
	
	while (nrms > tols && iteration < maxIterations) {

		calcTemp = simSaturationCurrent*matrixExp(nonLinVoltageVector / simThermalVoltage); //temp term             --- MATLAB  TERM = IS*exp(vd/VT)
		nonLinTransistorFunction = addToEveryValue(calcTemp, -simSaturationCurrent);        //the function value f  --- MATLAB  f = TERM - IS; 
		nonLinTransistorFunctionAltered = (calcTemp/simThermalVoltage).asDiagonal();        //the Jacobian of f     --- MATLAB  fd = diag(TERM/VT); 
		nodalDKNonlinearG = (simNonLinEquationMatrix * nonLinVoltageVector) + nonLinTransistorFunction - nonLinSolverInput;  //the function value g  --- MATLAB  g = M*vd + f - pd;         
		nodalDKNonlinearGAltered = simNonLinEquationMatrix + nonLinTransistorFunctionAltered;  //the Jacobian of g --- MATLAB  gd = M + fd;
		newtonStep = nodalDKNonlinearGAltered.partialPivLu().solve(nodalDKNonlinearG); //the newton step --- MATLAB STEP = gd\g
		nonLinVoltageVectorNew = nonLinVoltageVector - newtonStep; //MATLAB vdnew = vd - STEP
		nodalDKNonlinearGNew = simNonLinEquationMatrix * nonLinVoltageVectorNew + simSaturationCurrent * (addToEveryValue((matrixExp(nonLinVoltageVectorNew / simThermalVoltage)), -1)) - nonLinSolverInput; // matlab -   gnew = M*vdnew + IS*(exp(vdnew/VT) - 1) - pd; 
		newtonStepTemp = newtonStep; //initialise the temp value for capping subiterations
	
		
		while
			((nodalDKNonlinearGNew.transpose() * nodalDKNonlinearGNew > nodalDKNonlinearG.transpose() * nodalDKNonlinearG) && subIteration < maxSubIterations)
		{
			subIteration += 1; //increment the subiterations
			newtonStepTemp = (pow(2, -subIteration)) * newtonStep; //adjust the step, --- MATLAB STP = (2^(-m))*STEP;
			nonLinVoltageVectorNew = nonLinVoltageVector - newtonStepTemp; //update the voltage vector ---- MATLAB vdnew = vd-STP
			nodalDKNonlinearGNew = simNonLinEquationMatrix * nonLinVoltageVectorNew + simSaturationCurrent * (addToEveryValue((matrixExp(nonLinVoltageVectorNew / simThermalVoltage)), -1)) - nonLinSolverInput; // matlab -   gnew = M*vdnew + IS*(exp(vdnew/VT) - 1) - pd; 

		}

		nrms = newtonStepTemp.transpose() * newtonStepTemp; //squared norm
		nonLinVoltageVector = nonLinVoltageVectorNew; //update the voltage vector with the new values
		
		iteration += 1; //increment the iteration number
			
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
