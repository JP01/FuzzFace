#pragma once
// Header file for the Circuit.cpp class which contains
// all the circuit parameters
#include "Eigen/Dense"
#include <iostream>

class Circuit
{
	public: //access control
		const double defaultFuzz = 0.6; //Default value for fuzz
		const double defaultVol = 0.4;  //Default value for volume

		//Default Constructor
		Circuit();

		//Constructor with samplerate as an argument
		Circuit(double sampleRate);
		//Default Destructor
		~Circuit();

		/*Accessors and Mutators*/
		//Fuzz
		void setFuzz(double fuzzVal);   //function used to set fuzz paramater
		double getFuzz();                //returns the fuzz parameter

		//Vol
		void setVol(double volVal);     //function used to set volume parameter
		double getVol();                 //returns the volume parameter

		//StateSpaceMatrices
		Eigen::MatrixXd getStateSpaceMatrix(std::string input);  //Returns the statespace matrix corresponding to the input string, used in testing
		
		//Nonlinear Function Matrices
		Eigen::MatrixXd getNonlinearFunctionMatrix(std::string input); //Returns the nonlinear function matrix corresponding to the input string, used in testing

		//System Matrix 
		//Refreshes the system matrix with new fuzz and vol values then returns the system matrix
		Eigen::Matrix<double, 12, 12> getSystemMatrix() { refreshSystemMatrix();  return systemMatrix; }

		//Refresh All matrices, call when paramater change needs to be implemented
		void refresh() {  refreshSystemMatrix(); refreshNonLinStateSpace(); refreshNonlinearFunctions(); }



	private: //access control
		double fuzz;  //value for the fuzz parameter
		double vol;   //value for the vol parameter
		
		//Sample period
		double T;

		//Resistors Values
		const double r1 = 33e3;
		const double r2 = 8.2e3;
		const double r3 = 330;
		const double r6 = 100e3;
		double r4, r5, r7, r8;        //variable Resistors

		//Capacitors Values
		const double c1 = 2.2e-6;
		const double c2 = 20e-6;
		const double c3 = 10e-9;

		//PNP Bipolar Junction Transistor Values
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
		
		//Populate the circuit matrices
		void updateCircuitMatrices();

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
	
		/**
		* State Space Matrices
		*/
		//Setup functions for the system matrix
		Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> systemRes;  //Resistor matrix used in calculation of system matrix
		Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> systemCap;  //Capacitor matrix used in calculation of system matrix
		
		Eigen::Matrix<double, numNodes+numInputs, numNodes + numInputs> systemMatrix;  //Create a 12x12 system matrix
		
		void refreshSystemMatrix();  //function to setup and refrseh the system matrix

		//Setup functions for nonlinear state space terms
		Eigen::Matrix<double, 3, 3> A;    
		Eigen::Matrix<double, 3, 2> B;
		Eigen::Matrix<double, 3, 4> C;
		Eigen::Matrix<double, 1, 3> D;
		Eigen::Matrix<double, 1, 2> E;
		Eigen::Matrix<double, 1, 4> F;
		Eigen::Matrix<double, 4, 3> G;
		Eigen::Matrix<double, 4, 2> H;
		Eigen::Matrix<double, 4, 4> K;

		void refreshNonLinStateSpace();


		/*
		*   Nonlinear function matrices
		*/
		Eigen::Matrix<double, 4, 4> psi;
		Eigen::Matrix<double, 4, 4> phi;
		Eigen::Matrix<double, 4, 4> M;
		Eigen::Matrix<double, 4, 4> Kd;


		void refreshNonlinearFunctions();
};