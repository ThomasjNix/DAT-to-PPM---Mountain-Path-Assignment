/*
*  P4.h
*
*  Created on: October 19, 2017
*  Author: Thomas Nix
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
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
};


/* Main function, sets the input file and calls functions associated with
	reading, altering, and writing PPM information
*/
int main() {
	
		// Define files
		string inFileName = "yosemite.ppm";
		string outFileName = "yosemite_output.ppm";
		Pixel *redPixel = new Pixel;
	
		Image yosemite (inFileName);
		yosemite.read(inFileName);
		
		for (int i = 0; i < 20; i++){
			yosemite.setImagePixel((yosemite.getWidth()/2)+i, (yosemite.getHeight()/2));
		}
		
		
		yosemite.write(outFileName);

	
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























