/*
*  P4-2.h
*  UNC Charlotte, ITCS 3112
*  Dr. K. Subramanian
*
*  Completed on: October 26th, 2017
*  Author: Thomas Nix
*/

// Included dependencies
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <cstring>
using namespace std;

// Struct for a Pixel, containing the RGB triplet values
struct Pixel{
	int RVal, GVal, BVal;
};

// Stream input overrider to read directly into pixels
ifstream& operator>>(ifstream& inContent, Pixel& pix){
	inContent >> pix.RVal;
		inContent >> pix.GVal;
			inContent >> pix.BVal;
	return inContent;
}

/* Image class containing methods to interact with an array associated with a given image */
class Image{
	private:
		int width, height;
		Pixel *image_array;
		string inputFile;
	public:
		Image();
		Image(string input_file);
		Image(int w, int h);
		~Image();
		
		int getWidth();
		void setWidth(int w);
		
		int getHeight();
		void setHeight(int h);
		
		Pixel getImagePixel(int col, int row);
		void setImagePixel(int col, int row);
		
		void read(string inFile);
		void write(string outFile);
		
		void write(Pixel *arrayIn, string outFile);
		
		void toGrayscale(string inFileName);
		void flipHorizontal(string inFileName);
		void negativeBlue(string inFileName);
		void flattenRed(string inFileName);
};


/* Main function, sets the input file and calls functions associated with
	reading, altering, and writing PPM information
*/
int main() {
	// Define files
		string inFileName;
		cout << "Please enter a file name that satisfies the following conditions:\n1. Must either be in this directory or a relative directory must be given\n2. File must exist and be a PPM file\n3. DO NOT INCLUDE .ppm! For Example.ppm, write Example" << endl;
		cout << "File name: ";
		cin >> inFileName;
		string inFileNameExt = inFileName + ".ppm";
		
		int userChoice;
		cout << "\n\nPlease choose an option for how you would like to modify this file (enter the number listed). The output will be created in this directory." << endl;
		cout << "1. Grayscale\n2. Blue negative\n3. Flatten red\n4. Horizontal flip" << endl;
		cout << "Choice: ";
		cin >> userChoice;
		
		Image userImage (inFileNameExt);
		userImage.read(inFileNameExt);
		
		switch(userChoice){
			case 1: 
				userImage.toGrayscale(inFileName);
				break;
			case 2: 
				userImage.negativeBlue(inFileName);
				break;
			case 3: 
				userImage.flattenRed(inFileName);
				break;
			case 4: 
				userImage.flipHorizontal(inFileName);
				break;
			default:
				cout << "Input not recognized, please rereun the program.";
				break;
		}
	
}

/**
      *  Default constructor initializes nothing because it will never be used
      */
Image::Image(){}


/**
      *  Constructor to initialize file name, the only one I actually will use
      *  @param  input_file : The file to be used for input
      */
Image::Image(string input_file){
	inputFile = input_file;
}

/**
      *  Constructor to initialize the width and height, that I will also not use
      */
Image::Image(int w, int h){
	width = w;
	height = h;
}

/**
      *  This is a destructor, whatever that is, I don't know but there it is
      */
Image::~Image(){}

/**
      *  Returns the width of the image
      */
int Image::getWidth(){
	return width;
}

/**
      *  Sets the width of the image
      *  @param  w : The width to set
      */
void Image::setWidth(int w){
	width = w;
}

/**
      *  Returns the height of the image
      */
int Image::getHeight(){
	return height;
}

/**
      *  Sets the height of the image
      *  @param  h : The width to set
      */
void Image::setHeight(int h){
	height = h;
}

/**
      *  Gets the pixel at a specific point in the image
      *  @param  col : The column specified to retrieve
      *  @param  row : The row specified to retrieve
      */
Pixel Image::getImagePixel(int col, int row){
		return image_array[(row*width)+col];

}

/**
      *  Sets the pixel at a specific point in the image
      *  @param  col : The column specified to retrieve
      *  @param  row : The row specified to retrieve
      */
void Image::setImagePixel(int col, int row){
	image_array[(row*width)+col].RVal = 255;
	image_array[(row*width)+col].GVal = 0;
	image_array[(row*width)+col].BVal = 0;
}

/**
      *  reads the image and sets the value of the points in the image in the image array
      *  @param  inFile : The file to read from
      */
void Image::read(string inFile){
	ifstream inReg(inFile);
	string tempVar;
	int whArr[2];		
	
	for (int i = 0; i < 2; i++){
		if (i == 0){
			getline(inReg, tempVar);
		}
		getline(inReg, tempVar, ' ');
		whArr[i] = stoi(tempVar);	
	}
	inReg.close();
	
	int area = whArr[0]*whArr[1];
	setWidth(whArr[0]);
	setHeight(whArr[1]);
	
	image_array = new Pixel[area];
	
	int counter = 0;
	ifstream inVal(inFile);
	string tempString;
	
	getline(inVal, tempString);
	getline(inVal, tempString, ' ');
	getline(inVal, tempString);
	
	
	int percentageValue = 0;
	int pixelCounter = 0;
	while (pixelCounter < area){
		getline(inVal, tempString);
		Pixel p;
		for (int i = 0; i < 5; i++){
			inVal >> p;
			image_array[pixelCounter] = p;

			if (pixelCounter % (area/100) == 0){
				percentageValue = (pixelCounter/(area/100));
				cout << "Loading file into array, please wait..." << percentageValue << "%" << endl;
			}
					pixelCounter++;
		}
	};
	
	inVal.close();
	
}

/**
      *  Writes the information in the image array to the file
      *  @param  inFile : The file to read from
      */
void Image::write(string outFile){
	ofstream newFile;
	newFile.open(outFile);
	newFile << "P3" << "\n";
	newFile << width << " " << height << "\n";
	newFile << "255" << endl;
	
	for (int i = 0; i < width*height; i++){
	newFile << " ";
	newFile << image_array[i].RVal << "  " <<
			 image_array[i].GVal << "  " <<
			  image_array[i].BVal << " ";
			  
			  if (i % 5 == 4 || i == 4){
			  	newFile << "\n";
			  }
	}
	
	delete[] image_array;
}

/**
      *  Writes the information in the passed in array to the file
      *  @param  arrayIn : The array to write
      *  @param  inFile : The file to read from
      */
void Image::write(Pixel *arrayIn, string outFile){
	ofstream newFile;
	newFile.open(outFile);
	newFile << "P3" << "\n";
	newFile << width << " " << height << "\n";
	newFile << "255" << endl;
	
	for (int i = 0; i < width*height; i++){
	newFile << " ";
	newFile << arrayIn[i].RVal << "  " <<
			 arrayIn[i].GVal << "  " <<
			  arrayIn[i].BVal << " ";
			  
			  if (i % 5 == 4 || i == 4){
			  	newFile << "\n";
			  }
	}
	
	delete[] arrayIn;
}

/**
      *  Rewrites a pixel to be grayscale following the formula grayVal = (R*0.299)+(G*0.587)+(B*0.114)
      *  @param  inFileName : File name to be modified and written with
      */
	void Image::toGrayscale(string inFileName){
		
		// Create temporary copy for operations
		int area = width*height;
		Pixel *holderArr = new Pixel[area];
		memcpy(holderArr, image_array, area*sizeof(Pixel));
		
		// Write new values to temporary array as gray values
		for (int i = 0; i < area; i++){
			float grayValue = ((holderArr[i].RVal*0.299) + (holderArr[i].GVal*0.587) + (holderArr[i].BVal*0.114));
			holderArr[i].RVal = (int)grayValue;
			holderArr[i].GVal = (int)grayValue;
			holderArr[i].BVal = (int)grayValue;
		}


		// Write out file
		string outFileName = inFileName + "_gray.ppm";
		cout << "\n\nWriting to " << outFileName << "..." << endl;
		write(holderArr, outFileName);
	}
	
	
/**
    *  Flips pixels in each row horizontally
    *  @param  inFileName : File name to be modified and written with
    */
void Image::flipHorizontal(string inFileName){

		// Create copy of array and new array to hold stored information
		int area = width*height;
		Pixel *holderArr = new Pixel[area];
		Pixel *newArr = new Pixel[area];
		memcpy(holderArr, image_array, area*sizeof(Pixel));
		
		// Loop through each row
		for (int h = 0; h < height; h++){
			for (int w = 0; w < (width); w++){		
				// Assign new values to newArr based on the opposite index given the center of each row in holderArr
				int rowStart = (h*width);
				int rowEnd = (h*width)+width-1;
				int currentPosition = rowStart + w;
				newArr[currentPosition] = holderArr[rowEnd - w];
			}
		}
		
		
		// Write out file
		string outFileName = inFileName + "_hflip.ppm";
		cout << "\n\nWriting to " << outFileName << "..." << endl;
		write(newArr, outFileName);
}
	
/**
    *  Rewrites the blue value of a pixel about the maximum value (Ex: 100 would become 155, 250 would become 5, etc.)
    *  @param  inFileName : File name to be modified and written with
    */
void Image::negativeBlue(string inFileName){
		
		// Create temporary copy for operations
		int area = width*height;
		Pixel *holderArr = new Pixel[area];
		memcpy(holderArr, image_array, area*sizeof(Pixel));
		
		// Write new values to temporary array as gray values
		for (int i = 0; i < area; i++){
			holderArr[i].BVal = 255-holderArr[i].BVal;
		}
		
		// Write out file
		string outFileName = inFileName + "_negBlue.ppm";
		cout << "\n\nWriting to " << outFileName << "..." << endl;
		write(holderArr, outFileName);

}
	
	
/**
    *  Sets the red value of a pixel to 0
    *  @param  inFileName : File name to be modified and written with
    */
void Image::flattenRed(string inFileName){
	// Create temporary copy for operations
		int area = width*height;
		Pixel *holderArr = new Pixel[area];
		memcpy(holderArr, image_array, area*sizeof(Pixel));
		
		// Write new values to temporary array as gray values
		for (int i = 0; i < area; i++){
			holderArr[i].RVal = 0;
		}
		
		// Write out file
		string outFileName = inFileName + "_flatRed.ppm";
		cout << "\n\nWriting to " << outFileName << "..." << endl;
		write(holderArr, outFileName);
}



















