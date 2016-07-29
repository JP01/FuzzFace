#pragma once
#include "Eigen/Dense"
class Simulation
{
public:
	Simulation();
	~Simulation();

	void setBufferSize(int bufferSize);

private:
	//Buffer size in samples, defaulted to...??
	int bufferSize;


	//Specified tolerance in Vd
	double tol = 1e-10;

	/*Simulation Preparations*/

	Eigen::VectorXd pdNull; //null vector for pd
	Eigen::VectorXd stateVector; //memorised state vector
	Eigen::VectorXd vdVector; //memorised vd vector
	Eigen::VectorXd inputVector; //input vector
	Eigen::RowVectorXd iterationCollection;  //iteration collection vector, collects the number of iterations to solve the current sample
	Eigen::RowVectorXd subIterationCollection; //sub-iteration collection vector, collects the number of iterations to solve the current sample
	Eigen::MatrixXd currentCollection; //nonlinear current collection array
	Eigen::MatrixXd auxSignalCollection; //auxiliary signal collection vector

	
	void initialiseSimulationParameters();



	

};
