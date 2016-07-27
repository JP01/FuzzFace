#include "TestHelper.h"

//Default Constructor
TestHelper::TestHelper()
{
	acceptableError = 1e-14;
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
		std::cerr << "Threre was a problem opening the input file!  -- " << fileName << std::endl;
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

//Takes a data set produced from matlab and a matrix of doubles and compares them, returns true if they are the same
bool TestHelper::matrixChecker(std::string matlabData, Eigen::MatrixXd inputMatrix) 
{
	//Initialise the total rows for looping 
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
				// "-difference" accounts for the difference being a negative number
				if (difference > acceptableError || -difference > acceptableError) {
					//Increase precision, used for error checking
					std::cout.precision(32);
					//if false, print error and erronious data
					std::cout << "\nAn error occured, Matlab Result: \t" << matlabResults[resultIndex] << "\n   does not equal Eigen Result: \t" << inputMatrix(row, col) << "\n The difference is : " << difference << std::endl;
					//set the testPass to false, letting Boost know the testcase has failed
					testPass = false;
				}
			
			resultIndex++;  //increment the resultIndex to move to next value in the matlabResults vector
		}
	}
	return testPass;
}
