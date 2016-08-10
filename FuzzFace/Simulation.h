#pragma once
#include "Eigen/Dense"
#include "MyMatrixTypes.h"
#include "Circuit.h"
#include <math.h>
#include <vector>
#include<ctime>

/* PI */
#define PI 3.141592653589793 //23846 - extra digits of precision
/* default vcc = 9*/
#define DEFAULT_VCC 9.

class Simulation : public Circuit
{
public:
	//Default Constructor
	Simulation();

	//Constructor with samplerate and vcc as arguement
	Simulation(double _sampleRate, double _vcc);

	//Default Destructor
	~Simulation();

	//Refresh and setup the statespace matrices used in the simulation
	void setup();

	//Sets the buffer size
	void setBufferSize(int bufferSize);

	//Takes the current sample as an arguement along with vcc and processes it, returning the new data.
	//channelData is used as the name to be implemented with JUCE API channelData variable name
	double processSample(double channelData, double _vcc);


	/*Testable Intermediate calculation values (UNUSED)*/
	/*Return the intermediate calculation variable at the index "selection".
	Where Selection: 
	1 - stateSpaceVector         
	2-  stateSpaceVectorMem
	3 - nonLinVoltageVector      
	4 - nonLinVoltageVectorMem
	5 - nonLinVoltageVectorPrev   
	6 - nonLinVoltageVectorNew
	7 - inputVector
	8 - nonLinSolverInput
	9 - nonLinTransistorFunction
	10 - nonLinTransistorFunctionAltered
	11 - nodalDKNonlinearG
	12 - nodalDKNonlinearGNew
	13 - nodalDKNonlinearGAltered
	14 - nonLinearCurrent
	15 - newtonStep
	16 - newtonStepTemp
	17 - calcTemp        
	Eigen::MatrixXd getCalculationVariable(int selection);
	*/
private:
	//Buffer size in samples, defaulted to...??
	int bufferSize;

	//Gets the system to a steady state ready for processing
	void getSteadyState();

	/* Input */
	//VCC voltage
	double vcc = 9; //steady state voltage
	double durfade = 0.1; //duration of the faded power up
	int MM; //integer rounded value used during the powerup phase
	Eigen::VectorXd win; //hanning window
	Eigen::VectorXd vccv; //power up voltage used in initial setup
	Eigen::VectorXd powerUpTimeVector; //time vector used in the powerup phase

	//Sin Input
	Eigen::VectorXd dummyData;//Dummy data used in the powerup phase
	const double sinFreq = 200;  //Frequency of the input sin signal
	const double sinAmp = 0.2;   //Amp of input signal

	const int maxIterations = 10;
	const int maxSubIterations = 10;

	//Specified tolerance in nonlinear voltage vd
	const double tol = 1e-10;
	const double tols = tol*tol;


	StateSpaceA simStateSpaceA;
	StateSpaceB simStateSpaceB;
	StateSpaceC simStateSpaceC;
	StateSpaceD simStateSpaceD;
	StateSpaceE simStateSpaceE;
	StateSpaceF simStateSpaceF;
	StateSpaceG simStateSpaceG;
	StateSpaceH simStateSpaceH;
	NonlinearFunctionMatrix simPSI, simAlteredStateSpaceK, simNonLinEquationMatrix;

	double simSaturationCurrent, simThermalVoltage;
	

	/*Simulation Preparations*/

	double nrms;	//newton rhapson solver value

	int iteration; 	//number of iterations per sample
	int subIterationTotal; //total number of subiterations occuring in a sample
	int subIterCounter;  //used in the damped newton iterations to determine sub iterations per iteration

	Eigen::Vector3d stateSpaceVector; //(MATLAB - x)
	Eigen::Vector3d stateSpaceVectorMem; //memorised state vector, 3x1 vector (MATLAB - xz)
	
	Eigen::Vector4d nonLinVoltageVector; //discrete nonlinear voltage vector. 4x1 vector (MATLAB - vd)
	Eigen::Vector4d nonLinVoltageVectorMem; //memorised nonlinear voltage vector, 4x1 vector (MATLAB - vdz)
	Eigen::Vector4d nonLinVoltageVectorPrev; //previous value --- MATLAB = vd0
	Eigen::Vector4d nonLinVoltageVectorNew; //new vd vector -- MATLAB = vdnew

	Eigen::Vector2d inputVector; //input vector, 2x1 vector (MATLAB - u)
	Eigen::Vector4d nonLinSolverInput; //input vector used in calculation of the nonlinear equation (MATLAB - pd)

	Eigen::Vector4d nonLinTransistorFunction; //MATLAB - f
	Eigen::Matrix4d nonLinTransistorFunctionAltered; //Matlab - fd
	Eigen::Vector4d nodalDKNonlinearG; //the nonlinear function from the Nodal DK method (i.e. g = p + K*f - v) (MATLAB - g)
	Eigen::Vector4d nodalDKNonlinearGNew; //Matlab - gnew
	Eigen::Vector4d nodalDKNonlinearGtemp; //Matlab (used as temp value for gnew = M*vdnew + IS*(exp(vdnew/VT) - 1) - pd;)
	Eigen::Matrix4d nodalDKNonlinearGAltered; //MATLAB - gd
	Eigen::Vector4d nonLinearCurrent; //the nonlinear currents through the transistor (i.e. i = f(v)) .... f and i basically have the same purpose so there is redundancy. (MATLAB - i)
	
	Eigen::Vector4d newtonStep; //the newston Step, used in simulation, MATLAB - STEP
	Eigen::Vector4d newtonStepTemp; //temp term used in simulation, adjusted step which works to keep max subiterations within the limit MATLAB - STP

	Eigen::Vector4d calcTemp; //temporary term used in simulation calculation (MATLAB - TERM)

	//Eigen::Vector2d outputVector;
	double output; //output of the model (MATLAB - y)

	//Dynamically Sized Vectors, (unknown size at compile time)
	Eigen::RowVectorXd iterationCollection;  //iteration collection vector, collects the number of iterations to solve the current sample
	Eigen::RowVectorXd subIterationCollection; //sub-iteration collection vector, collects the number of iterations to solve the current sample
	Eigen::MatrixXd currentCollection; //nonlinear current collection array
	Eigen::MatrixXd auxSignalCollection; //auxiliary signal collection vector

	void initialiseSimulationParameters();

	//Helper Functions used in the simulation calculations
	Eigen::MatrixXd matrixExp(Eigen::MatrixXd input);  //Return the exponential of each value in matrix
	Eigen::MatrixXd Simulation::addToEveryValue(Eigen::MatrixXd input, double valueToAdd); // Add valueToAdd to every value in the matrix input

};
