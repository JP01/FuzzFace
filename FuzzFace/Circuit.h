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
		//Fuzz
		void setFuzz(double fuzzVal);
		double getFuzz();
		//Vol
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
		const double r1 = 33e3;
		const double r2 = 8.2e3;
		const double r3 = 330;
		const double r6 = 100e3;
		double r4, r5, r7, r8;        //variable vals

		//Capacitors
		const double c1 = 2.2e-6;
		const double c2 = 20e-6;
		const double c3 = 10e-9;

		//PNP Bipolar Junction Transistor
		const double forwardGain = 200;
		const double reverseGain = 2;
		const double thermalVoltage = 25.8e-3;
		const double saturationCurrent = 1e-14;

		/*Circuit matrices*/
		//Resistor Matrices
		Eigen::Matrix<double, 1, 8> resMatrix;  //1row 8col - resistor matrix
		Eigen::MatrixXd diagResMatrix;          //diagonal - resistor matrix
	
		//Capacitor Matrices
		Eigen::Matrix<double, 1, 3> capMatrix;  //1row 3col - capacitor matrix
		Eigen::MatrixXd diagCapMatrix;          //diagonal - capacitor matrix
		
		//Incident Matrices
		const static int numNodes = 10;  //10 Nodes
		const static int numRes = 8;  //Number of Resistors
		const static int numCap = 3;  //Number of Capacitors
		const static int numInputs = 2;  //Number of inputs
		const static int numNonLin = 4; //Number of nonlinearities
		const static int numOutputs = 1; //Number of outputs
		
		/*One time setup of incident matrices, this is performed in the constructor and sets up the incident matrices*/
		void Circuit::initialiseIncidentMatrices() {

			//The incident matrix for the resistors
			incidentResistors <<
				0, 0, -1, 1, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, -1, 1, 0, 0, 0, 0,
				0, 0, 0, 1, 0, -1, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 1, -1,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				0, 1, 0, 0, 0, 0, -1, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 1, -1, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 1, 0, 0;

			incidentCapacitors <<
				1, -1, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
				0, 0, 0, 0, 0, 1, 0, 0, -1, 0;

			incidentVoltage <<
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, -1, 0, 0, 0, 0, 0, 0;

			incidentNonlinearities <<
				0, -1, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, -1, 0, 0, 0, 0, 0, 0, 0,
				0, 0, -1, 0, 0, 0, 1, 0, 0, 0,
				0, 0, 0, 0, -1, 0, 1, 0, 0, 0;

			incidentOutput <<
				0, 0, 0, 0, 0, 0, 0, 0, 0, 1;
		}


		Eigen::Matrix<double, numRes, numNodes> incidentResistors;    //incident resistor matrix
		Eigen::Matrix<double, numCap, numNodes> incidentCapacitors;   //incident capacitor matrix
		Eigen::Matrix<double, numInputs, numNodes> incidentVoltage;   //incident voltage matrix
		Eigen::Matrix<double, numNonLin, numNodes> incidentNonlinearities;  //incident nonlinearity matrix
		Eigen::Matrix<double, numOutputs, numNodes> incidentOutput;  //incident output matrix
	
		//Setup functions for the system matrix
		Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> systemRes;  //Resistor matrix used in calculation of system matrix
		Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> systemCap;  //Capacitor matrix used in calculation of system matrix
		

		Eigen::Matrix<double, numNodes+numInputs, numNodes + numInputs> systemMatrix;  //Create a 12x12 system matrix
		
		void refreshSystemMatrix();  //function to setup and refrseh the system matrix

};