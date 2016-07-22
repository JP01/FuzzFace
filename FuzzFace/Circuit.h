#pragma once
// Header file for the Circuit.cpp class which contains
// all the circuit parameters

class Circuit
{
	public: //access control
		//Constructor and Destructor
		Circuit();
		~Circuit();


		//Resistors
		const double r1 = 0;
		const double r2 = 0;
		const double r3 = 0;
		const double r4 = 0;
		const double r5 = 0;
		const double r6 = 0;
		const double r7 = 0;
		const double r8 = 0;

		//Capacitors
		const double c1 = 0;
		const double c2 = 0;
		const double c3 = 0;

		//Accessors and Mutators
		void setFuzz(double fuzzVal);
		double getFuzz();
		void setVol(double volVal);
		double getVol();

	private: //access control
		double fuzz;  //value for the fuzz parameter
		double vol;   //value for the vol parameter

		
};