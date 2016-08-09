#pragma once
#include "Eigen/Dense"
#include "MyMatrixTypes.h"
#include "Circuit.h"
#include <math.h>




class Simulation
{
public:
	Simulation();
	~Simulation();
	void setup();
	void setBufferSize(int bufferSize);

	//takes the current sample as an arguement and processes it, returning the new data.
	//channelData is used as the name to be implemented with JUCE API channelData variable name
	double process(double channelData);

	

private:
	//Buffer size in samples, defaulted to...??
	int bufferSize;

	//VCC voltage
	double vcc = 0;
	
	const int maxIterations = 100;
	const int maxSubIterations = 10;

	//Specified tolerance in nonlinear voltage vd
	const double tol = 1e-10;
	const double tols = tol*tol;

	Circuit simCircuit;

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
	int m;  //used in the damped newton iterations to determine sub iterations

	int iteration, subIteration; 	//number of iterations and sub iterations

	Eigen::Vector3d stateSpaceVector; //(MATLAB - x)
	Eigen::Vector3d stateSpaceVectorMem; //memorised state vector, 3x1 vector (MATLAB - xz)
	
	Eigen::Vector4d nonLinVoltageVector; //discrete nonlinear voltage vector. 4x1 vector (MATLAB - vd)
	Eigen::Vector4d nonLinVoltageVectorMem; //memorised nonlinear voltage vector, 4x1 vector (MATLAB - vdz)
	Eigen::Vector4d nonLinVoltageVectorPrev; //previous value --- MATLAB vd0
	Eigen::Vector4d nonLinVoltageVectorNew; //new vd vector -- matlab vdnew

	Eigen::Vector2d inputVector; //input vector, 2x1 vector (MATLAB - u)
	Eigen::Vector4d nonLinSolverInput; //input vector used in calculation of the nonlinear equation (MATLAB - pd)

	Eigen::Vector4d nonLinTransistorFunction; //MATLAB - f
	Eigen::Matrix4d nonLinTransistorFunctionAltered; //Matlab - fd
	Eigen::Vector4d nodalDKNonlinearG; //the nonlinear function from the Nodal DK method (i.e. g = p + K*f - v) (MATLAB - g)
	Eigen::Vector4d nodalDKNonlinearGNew; //Matlab - gnew
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
