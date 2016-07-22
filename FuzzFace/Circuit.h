#pragma once
// Header file for the Circuit.cpp class which contains
// all the circuit parameters
#include "Eigen/Dense"

class Circuit
{
	public: //access control
		//Default Constructor
		Circuit();
		//Constructor with samplerate as an argument
		Circuit(double sampleRate);
		//Default Destructor
		~Circuit();

		/*Accessors and Mutators*/
		void setFuzz(double fuzzVal);
		double getFuzz();
		void setVol(double volVal);
		double getVol();

		//Populate the circuit matrices
		void updateCircuitMatrices();


	private: //access control
		double fuzz;  //value for the fuzz parameter
		double vol;   //value for the vol parameter

		//Sample period
		double T;

		//Resistors
		double r1, r2, r3, r4, r5, r6, r7, r8;

		//Capacitors
		double c1, c2, c3;

		/*Circuit matrices*/
		//Resistor Matrix
		Eigen::Matrix<double, 1, 8> resMatrix;
		Eigen::MatrixXd diagResMatrix;
		//Capacitor Matrix
		Eigen::Matrix<double, 1, 3> capMatrix;
		Eigen::MatrixXd diagCapMatrix;
		
};