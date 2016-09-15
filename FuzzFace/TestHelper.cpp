#include "TestHelper.h"

//Default Constructor
TestHelper::TestHelper()
{
}

//Default Destructor
TestHelper::~TestHelper()
{
}


//Read matrix data from a file and return it as a vector of type double
std::vector<double> TestHelper::readMatrixData(std::string fileName)
{
	std::ifstream infile(fileName, std::ios::in);  //the input data
	std::vector<double> data;  //the return vector

	//check file can be opened or is opened
	if (!infile.is_open())
	{
		//print error if one occurs
		std::cerr << "There was a problem opening the input file!  -- " << fileName << std::endl;
	}
	else //if no error then...
	{
		double num = 0.0; //initialise the num variable
		while (infile >> num)  //store values from textfile while data exists
		{
			data.push_back(num); //Adds a new element at the end of the vector, after its current last element
		}
	}

	//Close the resource
	infile.close();
	//return the vector storing the data from the file
	return data;
}

//Write matrix data to a file
void TestHelper::writeMatrixData(Eigen::MatrixXf inputMatrix, std::string fileName) {
	std::ofstream myfile(fileName);

	//checks file open
	if (myfile.is_open())
	{
		//write the matrix to the file
		myfile <<  inputMatrix;
		//close the resource
		myfile.close();
	}
	//error message if file unable to open
	else {
		std::cout << "Unable to open file";
	}
}

//Write matrix data to a file includes sample number
void TestHelper::writeVectorData(Eigen::MatrixXf inputMatrix, std::string fileName) {
	std::ofstream myfile(fileName);

	//checks file open
	if (myfile.is_open())
	{
		//for each element in input vector, write the sample number and output the value
		for (int i = 0; i < inputMatrix.size(); i++)
		{	
			//Write the data at index 1 to the file with sample number i displayed
			myfile << "Sample " << i + 1 << ": " << inputMatrix(i) << std::endl;
		}
		//close the resource
		myfile.close();

	}
	//error message if file unable to open
	else {
		std::cout << "Unable to open file";
	}
}

//Takes a data set produced from matlab and a matrix of doubles and compares them, returns true if they are the same, starting at sample index startingIndex (USED FOR TESTING THE 
//SIMULATION.CPP AS THE FIRST ~9000 SAMPLES MAY BE INNACURATE)
bool TestHelper::matrixChecker(std::string matlabData, Eigen::MatrixXf inputMatrix, int startingIndex) 
{
	//Initialise the total rows and cols for looping 
	int totalRows = inputMatrix.rows();
	int totalCols = inputMatrix.cols();
	
	//create a vector to store the matlab generated matrix
	std::vector<double> matlabResults;

	//put the matlab results into the vector
	matlabResults = readMatrixData(matlabData);

	/* Test case processing */
	int resultIndex = 0; //the index from the vector matlabResults
	bool testPass = true; //Boolean flag used to determine the outcome of the testcase

	//Loop through all values of matlabResults and inputMatrix, Check corresponding values are equal and output error if not
	for (int row = 0; row < totalRows; row++)
	{
		for (int col = 0; col < totalCols; col++) {
				
			if (resultIndex > startingIndex) {
				/*Check each value for any differences, if there is a difference print an error message */
				double difference = 0;
				difference = matlabResults[resultIndex] - inputMatrix(row, col);

				//If the difference is greater than acceptableError then output error and fail the test 
				if (abs(difference) * 100 / inputMatrix(row, col) > acceptableErrorPercentage) {
					//Increase precision, used for error checking
					std::cout.precision(32);
					//if false, print error and erronious data
					std::cout << "\nAn error occured at sample: " << resultIndex << ".\nMatlab Result: \t" << matlabResults[resultIndex] << "\nEigen Result: \t" << inputMatrix(row, col) << "\n The difference is : " << difference << std::endl;
					//set the testPass to false, letting Boost know the testcase has failed
					testPass = false;
				}
			}
			resultIndex++;  //increment the resultIndex to move to next value in the matlabResults vector
		}
	}
	return testPass;
}

//Takes a data set produced from matlab and a matrix of floats and compares them, returns true if they are the same
bool TestHelper::matrixCheckerFloat(std::string matlabData, Eigen::MatrixXf inputMatrix)
{
	//Initialise the total rows and cols for looping 
	int totalRows = inputMatrix.rows();
	int totalCols = inputMatrix.cols();

	//create a vector to store the matlab generated matrix
	std::vector<double> matlabResults;

	//put the matlab results into the vector
	matlabResults = readMatrixData(matlabData);

	/* Test case processing */
	int resultIndex = 0; //the index from the vector matlabResults
	bool testPass = true; //Boolean flag used to determine the outcome of the testcase

	
	//Loop through all values of matlabResults and inputMatrix, Check corresponding values are equal and output error if not
	for (int row = 0; row < totalRows; row++)
	{
		for (int col = 0; col < totalCols; col++) {

			/*Check each value for any differences, if there is a difference print an error message */
			double difference = 0;
			difference = matlabResults[resultIndex] - inputMatrix(row, col);

			//If the difference is greater than acceptableError then output error and fail the test 

			if (abs(acceptableError)*100/inputMatrix(row,col) > 10) {
				//Increase precision, used for error checking
				std::cout.precision(32);
				//if false, print error and erronious data
				std::cout << "\nAn error occured at sample: " << resultIndex << ".\nMatlab Result: \t" << matlabResults[resultIndex] << "\nEigen Result: \t" << inputMatrix(row, col) << "\n The difference is : " << difference << std::endl;
				//set the testPass to false, letting Boost know the testcase has failed
				testPass = false;
			}

			resultIndex++;  //increment the resultIndex to move to next value in the matlabResults vector
		}
	}
	
	
	
	return testPass;
}

//Takes a data set produced from matlab and a matrix of doubles and compares them, returns true if they are the same
bool TestHelper::matrixChecker(std::string matlabData, Eigen::MatrixXd inputMatrix)
{
	//Initialise the total rows and cols for looping 
	int totalRows = inputMatrix.rows();
	int totalCols = inputMatrix.cols();

	//create a vector to store the matlab generated matrix
	std::vector<double> matlabResults;

	//put the matlab results into the vector
	matlabResults = readMatrixData(matlabData);

	/* Test case processing */
	int resultIndex = 0; //the index from the vector matlabResults
	bool testPass = true; //Boolean flag used to determine the outcome of the testcase

						  //Loop through all values of matlabResults and inputMatrix, Check corresponding values are equal and output error if not
	for (int row = 0; row < totalRows; row++)
	{
		for (int col = 0; col < totalCols; col++) {

				/*Check each value for any differences, if there is a difference print an error message */
				double difference = 0;
				difference = matlabResults[resultIndex] - inputMatrix(row, col);

				//If the difference is greater than acceptableErrorPercentage then output error and fail the test 	
				if (abs(difference) * 100 / inputMatrix(row, col) > acceptableErrorPercentage) {
					//Increase precision, used for error checking
					std::cout.precision(32);
					//if false, print error and erronious data
					std::cout << "\nAn error occured at sample: " << resultIndex << ".\nMatlab Result: \t" << matlabResults[resultIndex] << "\nEigen Result: \t" << inputMatrix(row, col) << "\n The difference is : " << difference << std::endl;
					//set the testPass to false, letting Boost know the testcase has failed
					testPass = false;
				}
			
			resultIndex++;  //increment the resultIndex to move to next value in the matlabResults vector
		}
	}
	return testPass;
}

//Helper Method to generate sin input
Eigen::VectorXf TestHelper::generateSin(double _sampleRate, double _frequency, double _duration, double _amplitude) {
	//Create a vector to store sin input and time vector
	Eigen::VectorXf sinWaveVector;
	Eigen::VectorXd timeVector;
	//Attributes of the input sin wave

	//Number of samples rounded up to the nearest whole integer
	double numberOfSamples = ceil(_sampleRate * _duration);

	//Resize the input vectors
	sinWaveVector.resize(numberOfSamples);
	timeVector.resize(numberOfSamples);

	//input the data into the vector
	for (int i = 0; i < numberOfSamples - 1; i++) {
		timeVector(i) = i*(1 / _sampleRate);
		sinWaveVector(i) = _amplitude * sin(2 * PI*_frequency*timeVector(i));
	}

	return sinWaveVector;
}
