#include "Simulation.h"

//Default Constructor with default values for samplerate and vcc
Simulation::Simulation() : Simulation(DEFAULT_SR, DEFAULT_VCC) {};

//Constructor with Args
Simulation::Simulation(double _sampleRate, double _vcc)
{
	//set sampleRate to _sampleRate
	sampleRate = _sampleRate;

	//set vcc to _vcc
	vcc = _vcc;

	//Sets up the statespace matrices used in the simulation
	setup();

	//Initialise the matrices used in simulation
	initialiseSimulationParameters();

	//Get the system to a steady State
	getSteadyState();
}


void Simulation::setup() 
{
	//Calls the Circuit method to refresh matrices
	refreshAll();

	//Sets up the state space matrices
	simStateSpaceA = getStateSpaceMatrix("A");
	simStateSpaceB = getStateSpaceMatrix("B");
	simStateSpaceC = getStateSpaceMatrix("C");
	simStateSpaceD = getStateSpaceMatrix("D");
	simStateSpaceE = getStateSpaceMatrix("E");
	simStateSpaceF = getStateSpaceMatrix("F");
	simStateSpaceG = getStateSpaceMatrix("G");
	simStateSpaceH = getStateSpaceMatrix("H");

	simPSI = getNonlinearFunctionMatrix("psi");
	simAlteredStateSpaceK = getNonlinearFunctionMatrix("alteredStateSpaceK");
	simNonLinEquationMatrix = getNonlinearFunctionMatrix("nonLinEquationMatrix");

	simSaturationCurrent = getSaturationCurrent();
	simThermalVoltage = getThermalVoltage();
		
}

//Initialise the matrices used in the simulation
void Simulation::initialiseSimulationParameters() {

	//Set up a 3x1 vector stateVector and set all vals to 0
	stateSpaceVectorMem.setZero();

	//Set up a 4x1 vector vdVector and set all vals to 0
	nonLinVoltageVectorMem.setZero();

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

//Get the system to steady state ready for processing
void Simulation::getSteadyState() {

	//zero input used as signal for warmup phase
	double zeroInput = 0;

	//MM value is used to get to steady state
	MM = durfade * sampleRate;

	//TM = 1./MM	
	//Declare the variable TM used in the time vector
	double T = 1 / sampleRate;

	//Resize the vccv vector to match MM
	vccv.resize(MM);
	//Resize the win vector to match 2*MM
	win.resize(2*MM);
	//Resize the powerUpTimeVector to MM
	powerUpTimeVector.resize(MM);


	/*VCCV Hanning multiplier to achieve steady state*/
	//Hanning win multiplier
	for (int i = 0; i < 2*MM; i++) {
		//calculate the hanning value at angle "i" 
		double multiplier = 0.5*(1 - cos((2 * PI * i) / (2*MM - 1)));
		//set the value at index win(i) equal to the multiplier
		win(i) = multiplier;
	}


	//Population loop, populates the vcc powerUpTimeVector and dummyData
	for (int i = 0; i < MM; i++) {
		//Multiply vcc by the ramp up section to get ramp up voltage
		//Multiply the hanning value by max voltage vcc at index "i" and input into vccv
		vccv(i) = win(i) * vcc;

		//t = (0:MM)*T 
		//Populate the time vector
		powerUpTimeVector(i) = i*T;
	}
	

	//*set up timing signatures
	time_t timer; 
	time_t timeBefore = time(&timer);
	std::cout << "timeBefore = " << timeBefore << std::endl;

	//process until steady state is reached
	for (int i = 0; i < MM; i++) {
		processSample(zeroInput, vccv(i));
	}
	
	//Output the time taken to get steady state
	time_t timeAfter = time(&timer);
	std::cout << "timeAfter = " << timeAfter << std::endl;
	std::cout << "Time taken to compute "<< MM <<" samples = " << timeAfter - timeBefore << " seconds" << std::endl;

	std::cout << "SteadyState Reached, now processing" << std::endl;
	}

//Process the incoming sample
double Simulation::processSample(double _channelData, double _vcc) {

	inputVector(0) = _channelData; //sets the input vector equal to the input channelData
	inputVector(1) = _vcc;

	//Prepare the nonlinear solver
	nonLinSolverInput = (simAlteredStateSpaceK.inverse())*(simStateSpaceG*stateSpaceVectorMem + simStateSpaceH*inputVector); //define input to the Nonlinear equation --- MATLAB pd
	
	//set initial value of nonLinVoltageVector as the memorised vector
	nonLinVoltageVectorPrev = nonLinVoltageVectorMem;	

	nrms = 1.; //sets the nrms high to begin with 
	iteration = 0;
	subIterationTotal = 0;

	nonLinVoltageVector = nonLinVoltageVectorPrev; //sets the nonlinVoltageVector as the memorised vector

	
	while (nrms > tols && iteration < maxIterations) {
		//TERM = IS*exp(vd/VT);
		calcTemp = simSaturationCurrent * matrixExp(nonLinVoltageVector / simThermalVoltage); 
		//f = TERM - IS;
		nonLinTransistorFunction = addToEveryValue(calcTemp, -simSaturationCurrent); 
		//fd = diag(TERM/VT);
		nonLinTransistorFunctionAltered = (calcTemp / simThermalVoltage).asDiagonal();        
		//g = M*vd + f - pd;
		nodalDKNonlinearG = (simNonLinEquationMatrix * nonLinVoltageVector)  //M*vd
						+ nonLinTransistorFunction                           //+ f
						- nonLinSolverInput;                                 //- pd              
		
		//gd = M + fd;
		nodalDKNonlinearGAltered = simNonLinEquationMatrix + nonLinTransistorFunctionAltered; 
		//STEP = gd\g;
		newtonStep = nodalDKNonlinearGAltered.partialPivLu().solve(nodalDKNonlinearG);  

		//vdnew = vd - STEP;
		nonLinVoltageVectorNew = nonLinVoltageVector - newtonStep;              
		//gnew = M*vdnew
		nodalDKNonlinearGNew = simNonLinEquationMatrix * nonLinVoltageVectorNew;              
		//gnew = M*vdnew + IS*(exp(vdnew/VT) - 1) - pd;
		nodalDKNonlinearGNew = nodalDKNonlinearGNew +                                                        //M*vdnew + 
			(simSaturationCurrent* (addToEveryValue(matrixExp(nonLinVoltageVector / simThermalVoltage), -1)))//IS*(exp(vdnew/VT) - 1)
			- nonLinSolverInput;                                                                             //-pd
		
		//m = 0
		subIterCounter = 0;       

		while (((nodalDKNonlinearGNew.transpose()*nodalDKNonlinearGNew) > (nodalDKNonlinearG.transpose()*nodalDKNonlinearG)) && subIterCounter < maxSubIterations)
		{
			//m = m+1
			subIterCounter++;
			//STP = (2^(-m))*STEP;    % adjusted step 
			newtonStepTemp = (2 ^ (-subIterCounter))*newtonStep;
			//vdnew = vd - STP
			nonLinVoltageVectorNew = nonLinVoltageVector - newtonStepTemp;

			//std::cout << "OLD: " << newtonStep << std::endl << " NEW: " << newtonStepTemp << std::endl;

			nodalDKNonlinearGNew = simNonLinEquationMatrix * nonLinVoltageVectorNew;              //gnew = M*vdnew

			nodalDKNonlinearGNew = nodalDKNonlinearGNew + (simSaturationCurrent*
				(addToEveryValue(matrixExp(nonLinVoltageVector / simThermalVoltage), -1)));       //M*vdnew + IS*(exp(vdnew/VT) - 1)

			nodalDKNonlinearGNew = nodalDKNonlinearGNew - nonLinSolverInput;                      //gnew = M*vdnew + IS*(exp(vdnew/VT) - 1) - pd;
																								  
		}

		nrms = newtonStepTemp.transpose()*newtonStepTemp;  //squared norm used to limit iterations
		nonLinVoltageVector = nonLinVoltageVectorNew;  //set the nonLinVoltageVector to the new value after calculation
		subIterationTotal += subIterCounter;  //keep track of the subiterations
		iteration++; //keep track of the iterations
	}
	

	//Update nonlinear currents, state and output
	nonLinearCurrent = simPSI * (simSaturationCurrent*(addToEveryValue(matrixExp(nonLinVoltageVector/simThermalVoltage), -1)));   //  i = PSI*(IS*(exp(vd/VT) - 1));
	stateSpaceVector = (simStateSpaceA * stateSpaceVectorMem) + (simStateSpaceB*inputVector) + (simStateSpaceC*nonLinearCurrent); //  x = A*xz + B*u + C*i;
	output = ((simStateSpaceD*stateSpaceVectorMem) + (simStateSpaceE*inputVector) + (simStateSpaceF*nonLinearCurrent))(0);           //  y = D*xz + E*u + F*i 
	//when declaring output  = RHS, the RHS is technically an Eigen Vector of size 1x1, so you must use the (0) to select the value at index 0

	stateSpaceVectorMem = stateSpaceVector;  //xz = x;   Memorise the stateSpaceVector
	nonLinVoltageVectorMem = nonLinVoltageVector; //vdz = vd;   Memorise the nonLinVoltageVector


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
