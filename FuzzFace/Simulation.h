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


private:
	//Buffer size in samples, defaulted to...??
	int bufferSize;

	//VCC voltage
	double vcc;
	
	const int maxIterations = 100;

	//Specified tolerance in nonlinear voltage vd
	const double tol = 1e-10;
	const double tols = tol*tol;

	Circuit simCircuit;
	StateSpaceG simStateSpaceG;
	StateSpaceH simStateSpaceH;
	NonlinearFunctionMatrix simAlteredStateSpaceK, simNonLinEquationMatrix;

	double simSaturationCurrent, simThermalVoltage;
	

	/*Simulation Preparations*/

	double nrms;	//newton rhapson solver value

	int iteration, subIteration; 	//number of iterations and sub iterations

	Eigen::Vector3d stateSpaceVector; //(MATLAB - x)
	Eigen::Vector3d stateSpaceVectorMem; //memorised state vector, 3x1 vector (MATLAB - xz)
	
	Eigen::Vector4d nonLinVoltageVector; //discrete nonlinear voltage vector. 4x1 vector (MATLAB - vd)
	Eigen::Vector4d nonLinVoltageVectorMem; //memorised nonlinear voltage vector, 4x1 vector (MATLAB - vdz)
	Eigen::Vector4d nonLinVoltageVectorPrev; //previous value

	Eigen::Vector2d inputVector; //input vector, 2x1 vector (MATLAB - u)
	Eigen::Vector4d nonLinSolverInput; //input vector used in calculation of the nonlinear equation (MATLAB - pd)
	Eigen::Vector4d nonLinSolverInputNull; //null vector for nonLinSolverInput, 4x1 vector (MATLAB - pdnull)

	Eigen::Vector4d nonLinTransistorFunction; //MATLAB - f
	Eigen::Vector4d nonLinTransistorFunctionAltered; //Matlab - fd
	Eigen::Vector4d nodalDKNonlinearG; //the nonlinear function from the Nodal DK method (i.e. g = p + K*f - v) (MATLAB - g)
	Eigen::Vector4d nodalDKNonlinearGAltered; //MATLAB - gd
	Eigen::Vector4d nonLinearCurrent; //the nonlinear currents through the transistor (i.e. i = f(v)) .... f and i basically have the same purpose so there is redundancy. (MATLAB - i)
	
	Eigen::Vector4d calcTemp; //temporary term used in simulation calculation (MATLAB - TERM)

	double output; //output of the model (MATLAB - y)

	//Dynamically Sized Vectors, (unknown size at compile time)
	Eigen::RowVectorXd iterationCollection;  //iteration collection vector, collects the number of iterations to solve the current sample
	Eigen::RowVectorXd subIterationCollection; //sub-iteration collection vector, collects the number of iterations to solve the current sample
	Eigen::MatrixXd currentCollection; //nonlinear current collection array
	Eigen::MatrixXd auxSignalCollection; //auxiliary signal collection vector

	void initialiseSimulationParameters();

	//takes the current sample as an arguement and processes it, returning the new data.
	//channelData is used as the name to be implemented with JUCE API channelData variable name
	double process(double channelData); 


	//Helper Functions used in the simulation calculations
	Eigen::MatrixXd matrixExp(Eigen::MatrixXd input);  //Return the exponential of each value in matrix
	Eigen::MatrixXd Simulation::addToEveryValue(Eigen::MatrixXd input, double valueToAdd); // Add valueToAdd to every value in the matrix input

};
