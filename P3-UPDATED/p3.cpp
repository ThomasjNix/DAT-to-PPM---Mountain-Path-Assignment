/*
 * Thomas Nix
 * ITCS 3112
 * Professor Subramanian
 * Completed 9/26/2017 
 */

//Included dependancies
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
using namespace std;

// Function declarations
void createPPM(int **valueArr, string fileName, string fileType, int *widthHeightArr, int maxValue, int *startingPoint, int numPoints);
void createValArr(int ***valueArr, int *widthHeightArr, int& maxNum, string fileName);
int findPath(int **valueArr, int* widthHeightArr, int row, int col);

// Starting method main
// Driver function, main property declaration
int main() {

	// Present user with information critical to proper file read
	cout << "\n\nNOTICE: Please make sure that the file you wish to read is in the same directory as this .cpp file!" << endl;
	cout << "If the file is in a subdirectory, please make sure to specify with \"./subdirectory/filename.dat\" (not including quotes)" << endl;
	// File info initialization and input ( with default values)
	string fileName = "colorado1.dat";
	string outputFileName = "colorado1.ppm";
	string fileType = "P3";
	int numRows;
	cout << "\n\nPlease enter P3 or P6: ";
	cin >> fileType;
	cout << "Please enter a source file name (include .dat): ";
	cin >> fileName;
	cout << "Please enter an output file name (include .ppm): ";
	cin >> outputFileName;
	cout << "How many rows would you like to enter? ";
	cin >> numRows; 
	
	// Width and height retrieval and array storage
	ifstream inReg(fileName);
	string tempVar;
	int whArr[2];		
	for (int i = 0; i < 2; i++){
		getline(inReg, tempVar, ' ');
		whArr[i] = stoi(tempVar);	
	}
	inReg.close();
	
	// Create array of starting points for future use
	int startingPoints[numRows];
	for (int i = 0; i < numRows; i++){
		cout << "Please enter a starting row (Between 1 and " << whArr[1] << "): ";
		cin >> startingPoints[i];
		startingPoints[i] -= 1;
	}
	
	// Initialize elevation value array
	int maxNum;
	int **elev_data = new int*[whArr[1]];
	for (int i = 0; i < whArr[1]; i++){
		elev_data[i] = new int[whArr[0]];
		for (int j = 0; j < whArr[0]; j++){
			elev_data[i][j] = 0;
		}
	}
	
	//Fill array with data
	createValArr(&elev_data, whArr, maxNum, fileName);
	
	// Path operations on per-point basis	
	for (int i = 0; i < numRows; i++){
		// Function calls to find path and create PPM file
		findPath(elev_data, whArr, 0, startingPoints[i]);
	}

	// Creates PPM with finalized value array
	createPPM(elev_data, outputFileName, fileType, whArr, maxNum, startingPoints, numRows); 

	
}

/*
* createPPM creates a PPM file with the specified values, as well as maps the points decided by the findPath() function
* Parameters:
	**valueArr : Pointer to pointer to array of array values
	fileName : Name of file (for output)
	*widthHeightArr : Pointer to the array of file-specified width and height
	maxValue : Value passed of maximum value in array
	startingPoint : Only used to show user data after file is created
	numRows: Only used for calculating the starting points
*/
void createPPM(int **valueArr, string fileName, string fileType, int *widthHeightArr, int maxValue, int *startingPoints, int numRows){

	// Open ofstream, create file and write header based on passed in information
	ofstream newFile;
	newFile.open(fileName);
	newFile << fileType << "\n";
	newFile << widthHeightArr[0] << " " << widthHeightArr[1] << "\n";

	// Use 255 as maximum value for RGB triplers (255 = white)
	newFile << "255" << '\n';
	for (int i = 0; i < widthHeightArr[1]; i++){
		for (int j = 0; j < widthHeightArr[0]; j++){
			// Create double for fractional use
			// If valArr[i] == -1 this represents it is a point on the path decided in findPath(), and the RGB triplet is set to red (255,0,0)
			// Otherwise the value based on the maximum value and explicitly parsed to an integer (rounded) is used for grayscale value
			// Print rgbVal to file, with newline if last point in file
			double currentVal = double(valueArr[i][j]);
			int printVal;
			string rgbVal;
			if (valueArr[i][j] == -1){
				rgbVal = " 255 0 0";
			}else{
				currentVal /= maxValue;
				currentVal *= 255;
				printVal = int(currentVal);
				stringstream ss;
				ss << " " << printVal << " " << printVal << " " << printVal;
				rgbVal = ss.str();
			}
			if (i % widthHeightArr[0] == 0){
				newFile << rgbVal << "\n";
			}else{
				newFile << rgbVal;
			}
		}
	
	}
	newFile.close();
	
	cout << "File Name:\t" << fileName << endl;
	cout << "File Type:\t" << fileType << endl;
	cout << "Start Point(s):\t";
	for (int i = 0; i < numRows; i++){
		if (i == numRows - 1){
			cout << startingPoints[i]+1 << endl;
		}else{
			cout << startingPoints[i]+1 << ", ";
		}
	}
	cout << "Max Value:\t" << maxValue << endl;
	cout << "File created successfully." << endl;
	
	delete [] valueArr;
}


/*
 * createValArr() takes pointers to the value array, widthHeight array, and maximum number integer and 
 * computes fills the value array with values from the file as well as sets the maximum value from the file
 * Parameters: 
	***valArr: In value of array of values to be used for referencing array of values
	*widthHeightArr: Pointer to array of file-specified width and height
	&maxNum: Pointer to integer to hold maximum number once it's found 
	fileName: Name of the file to search 
*/
void createValArr(int ***valArr, int *widthHeightArr, int& maxNum, string fileName){
	ifstream inVal(fileName);
	int lineCounter = 0;
	maxNum = 0;
	string tempString;

	for (int i = 0; i < widthHeightArr[1]+1; i++){
		if (i == 0){
			getline(inVal, tempString);
		}else{
			getline(inVal, tempString);
			istringstream is(tempString);
			int j = 0;
			int n;
			while (is >> n){
				if (j < widthHeightArr[0]){
					//cout << "PriorVal:" << (*valArr)[i-1][j];
					(*valArr)[i-1][j] += n;
					//cout << "\tnVal:" << n << "\tArrVal:" << (*valArr)[i-1][j] << "\tIndex:" << j <<  endl;
					if (n > maxNum){
						maxNum = n;
					}	
					j++;
				}
			}			
		}
	}
}

/*
 * findPath is the method used to navigate the value array and find the local points of least change in elevation (value)
 * Points decided to be optimal locally are set to have -1 value for conditional RGB value change in createPPM()
 * This function is recursive, and returns 0 when the end condition is met
 * Parameters:
	*valueArr : In value of array of values to be used for referencing array of values
	*widthHeightArr : Pointer to the array of file-specified width and height
	row : used to reference the row that is being accessed currently
	col: used to reference the column that is being accessed currently
*/
int findPath(int **valueArr, int *widthHeightArr, int row, int col){
	int topVal;
	int botVal;
	int nextVal;
	
	// End met condition
	if (row == widthHeightArr[0]){
		valueArr[col][row] = -1;
		return 0;
	}else{
		// On top row
		if (col <= 0){
			nextVal = valueArr[col][row+1];
			botVal = valueArr[col+1][row+1];
			
			if (nextVal <= botVal){
				row += 1;
				valueArr[col][row] = -1;
				findPath(valueArr, widthHeightArr, row, col); 
			}else{
				col += 1;
				row += 1;
				valueArr[col][row] = -1;
				findPath(valueArr, widthHeightArr, row, col); 
			}
		}else{
			// On bottom row
			if (col >= widthHeightArr[1]-1){
				topVal = valueArr[col-1][row+1];
				nextVal = valueArr[col][row+1];
				
				if (topVal <= nextVal){
					col -= 1;
					row += 1;
					valueArr[col][row] = -1;
					findPath(valueArr, widthHeightArr, row, col); 
				}else{
					row += 1;
					valueArr[col][row] = -1;
					findPath(valueArr, widthHeightArr, row, col); 
				}
			}else{
				topVal = valueArr[col-1][row+1];
				nextVal = valueArr[col][row+1];
				botVal = valueArr[col+1][row+1];
				
				if (topVal <= botVal){
					if (topVal <= nextVal){
						col -= 1;
						row += 1;
						valueArr[col][row] = -1;
						findPath(valueArr, widthHeightArr, row, col); 
					}else{
						row += 1;
						valueArr[col][row] = -1;
						findPath(valueArr, widthHeightArr, row, col); 
					}
				}else{
					if (botVal <= nextVal){
						col += 1;
						row += 1;
						valueArr[col][row] = -1;
						findPath(valueArr, widthHeightArr, row, col); 
					}else{
						row += 1;
						valueArr[col][row] = -1;
						findPath(valueArr, widthHeightArr, row, col); 
					}
				}
			}
		}
	}
	
	return 0;
	
}




