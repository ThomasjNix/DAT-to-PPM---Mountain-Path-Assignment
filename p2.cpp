/*
 * Thomas Nix
 * ITCS 3112
 * Professor Subramanian
 * Completed 9/13/2017 
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
void createPPM(int *valueArr, string fileName, string fileType, int *widthHeightArr, int maxValue, int startingPoint);
void createValArr(int *valArr, int* widthHeightArr, int& maxNum, string fileName);
int findPath(int *valueArr, int* widthHeightArr, int currentPoint, int lineCounter);

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
	int startingPoint = 0;
	cout << "\n\nPlease enter P3 or P6: ";
	cin >> fileType;
	cout << "Please enter a source file name (include .dat): ";
	cin >> fileName;
	cout << "Please enter an output file name (include .ppm): ";
	cin >> outputFileName;
	cout << "Please enter a starting row: ";
	cin >> startingPoint;
	cout << endl;




	// Width and height retrieval and array storage
	ifstream inReg(fileName);
	string tempVar;
	int whArr[2];		
	for (int i = 0; i < 2; i++){
		getline(inReg, tempVar, ' ');
		whArr[i] = stoi(tempVar);
		
	}
	inReg.close();

	// Adjust starting point based on row
	startingPoint = startingPoint * whArr[0];

	
	// Initialize the value array and maximum value, make call to createValArr() with pointers to set values
	int valArr[whArr[0]*whArr[1]];
	int maxNum;
	createValArr(valArr, whArr, maxNum, fileName);
	
	
	// Function calls to find path and create PPM file
	findPath(valArr, whArr, startingPoint, 0);
	createPPM(valArr, outputFileName, fileType, whArr, maxNum, startingPoint); 

	
}

/*
* createPPM creates a PPM file with the specified values, as well as maps the points decided by the findPath() function
* Parameters:
	*valueArr : Pointer to array of values
	fileName : Name of file (for output)
	*widthHeightArr : Pointer to the array of file-specified width and height
	maxValue : Value passed of maximum value in array
	startingPoint : Only used to show user data after file is created
*/
void createPPM(int *valueArr, string fileName, string fileType, int *widthHeightArr, int maxValue, int startingPoint){

	// Open ofstream, create file and write header based on passed in information
	ofstream newFile;
	newFile.open(fileName);
	newFile << fileType << "\n";
	newFile << widthHeightArr[0] << " " << widthHeightArr[1] << "\n";

	// Use 255 as maximum value for RGB triplers (255 = white)
	newFile << "255" << '\n';
	for (int i = 1; i < widthHeightArr[0]*widthHeightArr[1]+1; i++){

		// Create double for fractional use
		// If valArr[i] == -1 this represents it is a point on the path decided in findPath(), and the RGB triplet is set to red (255,0,0)
		// Otherwise the value based on the maximum value and explicitly parsed to an integer (rounded) is used for grayscale value
		// Print rgbVal to file, with newline if last point in file
		double currentVal = double(valueArr[i]);
		int printVal;
		string rgbVal;
		if (valueArr[i] == -1){
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
	newFile.close();
	
	cout << "File Name:\t" << fileName << endl;
	cout << "File Type:\t" << fileType << endl;
	cout << "Start Point:\t" << startingPoint << endl;
	cout << "Max Value:\t" << maxValue << endl;
	cout << "File created successfully." << endl;
}


/*
 * createValArr() takes pointers to the value array, widthHeight array, and maximum number integer and 
 * computes fills the value array with values from the file as well as sets the maximum value from the file
 * Parameters: 
	*valArr: Pointer to array of values 
	*widthHeightArr: Pointer to array of file-specified width and height
	&maxNum: Pointer to integer to hold maximum number once it's found 
	fileName: Name of the file to search 
*/
void createValArr(int *valArr, int* widthHeightArr, int& maxNum, string fileName){
	ifstream inVal(fileName);
	int lineCounter = 0;
	maxNum = 0;
	string tempString;
	while(!inVal.eof() && lineCounter < widthHeightArr[0]*widthHeightArr[1]-1){
		if (lineCounter == 0){
			getline(inVal, tempString);
			lineCounter++;
		}else{
			getline(inVal, tempString);
			istringstream is(tempString); 
			int n;
			while (is >> n){
				valArr[lineCounter] = n;
				if (n > maxNum){
					maxNum = n;
				}
				lineCounter++;	
			}			
		}
	}
}


/*
 * findPath is the method used to navigate the value array and find the local points of least change in elevation (value)
 * Points decided to be optimal locally are set to have -1 value for conditional RGB value change in createPPM()
 * This function is recursive, and returns 0 when the end condition is met
 * Parameters:
	*valueArr : Pointer to array of values
	*widthHeightArr : Pointer to the array of file-specified width and height
	currentPoint : Initially the point set by the user and passed in recursive callbacks to continue pathfinding
	lineCounter : used to check if end of line is met 
*/
int findPath(int *valueArr, int *widthHeightArr, int currentPoint, int lineCounter){

	// Value declarations
	int arrLength = (widthHeightArr[0]*widthHeightArr[1]);
	int topVal;
	int botVal;
	int nextVal;

	// End condition met
	if (lineCounter == widthHeightArr[0]-1){
		valueArr[currentPoint] = -1;	
		return 0;
	// End condition not met
	}else{
			// If current point is not at topmost row
			if (currentPoint - widthHeightArr[0]+ 1 >= 0){

				// If current point is not at bottom most row
				if (currentPoint + widthHeightArr[0] + 1 <= arrLength){
					
					// Calculate absolute change in altitude (value) for each possible point
					topVal = abs(valueArr[currentPoint] - valueArr[currentPoint - widthHeightArr[0] + 1]);
					botVal = abs(valueArr[currentPoint] - valueArr[currentPoint + widthHeightArr[0] + 1]);
					nextVal = abs(valueArr[currentPoint] - valueArr[currentPoint + 1]);

					// Compare each value, and recursively call back findPath() with chosen point, passing the value array, widthHeight array, current point, and line counter
					if (topVal <= botVal){
						if (topVal <= nextVal){
							valueArr[currentPoint] = -1;
							lineCounter++;
							findPath(valueArr, widthHeightArr, currentPoint-widthHeightArr[0]+1, lineCounter);
						}else{
							valueArr[currentPoint] = -1;
							lineCounter++;
							findPath(valueArr, widthHeightArr, currentPoint+1, lineCounter);
						}
				// If current point is at bottom most row
				}else{
					// Calculate absolute change in altitude (value) for each possible point
					topVal = abs(valueArr[currentPoint] - valueArr[currentPoint - widthHeightArr[0] + 1]);
					nextVal = abs(valueArr[currentPoint] - valueArr[currentPoint + 1]);

					// Compare each value, and recursively call back findPath() with chosen point, passing the value array, widthHeight array, current point, and line counter
					if (botVal <= nextVal){
						valueArr[currentPoint] = -1;
						lineCounter++;
						findPath(valueArr, widthHeightArr, currentPoint+widthHeightArr[0]+1, lineCounter);
					}else{
						valueArr[currentPoint] = -1;
						lineCounter++;
						findPath(valueArr, widthHeightArr, currentPoint+1, lineCounter);
					}
				}	
			// If current point is at topmost row		
			}else{
				// Calculate absolute change in altitude (value) for each possible point
				botVal = abs(valueArr[currentPoint] - valueArr[currentPoint + widthHeightArr[0] + 1]);
				nextVal = abs(valueArr[currentPoint] - valueArr[currentPoint + 1]);

				// Compare each value, and recursively call back findPath() with chosen point, passing the value array, widthHeight array, current point, and line counter
				if (botVal <= nextVal){
					valueArr[currentPoint] = -1;
					lineCounter++;
					findPath(valueArr, widthHeightArr, currentPoint+widthHeightArr[0]+1, lineCounter);
				}else{
					valueArr[currentPoint] = -1;
					lineCounter++;
					findPath(valueArr, widthHeightArr, currentPoint+1, lineCounter);
				}	
			}
		
		}
	}
}




