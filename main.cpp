#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>

#include "ARCfmt.h"
#include "ARCfmt.cpp"

using namespace std;

int readImageHeader(char[], int&, int&);
int readImage(char[], Image&);
int writeImage(char[], Image&);

int main(int argc, char *argv[])
{
	int H, W;
	int temp_position;
	int choice = 1;
	int temp_red;
	int temp_green;
	int temp_blue;


	readImageHeader(argv[1], H, W);

    	// Allocate memory for the image
	Image image(H,W);

	// Read image
	readImage(argv[1], image);
    
    switch(argv[2]){
    	case 0:
    		grayScaleHistogram(image, argv[4]);
    	case 1:
    		maxMin(image);
    	case 2: 
    		mask(image, argv[4]);

    }
	// Print menu
	while(0 <= choice && choice < 5)
	{
        	cout << "Option menu:" << endl;
		cout << "[0] Quit" << endl;
        
		if(argc == 2) // One input image
		{
			cout << "[1] Set the red value of a pixel" << endl;
			cout << "[2] Set the green value of a pixel" << endl;		
			cout << "[3] Set the blue value of a pixel" << endl;
			cout << "[4] Set the value of a pixel" << endl << endl;
        	}
        	else
		{
			cout << "ERROR" << endl;
		}
        	cin >> choice;
        
        	switch(choice)
        	{
			case 0: // [0] Quit
				cout << "Closing the program." << endl;
				return 0;
			case 1: // [1] Set the red value of a pixel
				cout << "Write the position of the pixel:" << endl;
                		cin >> temp_position;				
				cout << "Write the red value of the pixel:" << endl;
                		cin >> temp_red;
                		image.setRedPixelValue(temp_position, temp_red);
				temp_position = 0;
				temp_red = 0;
                		writeImage(argv[1], image);
                		break;
			case 2: // [2] Set the green value of a pixel
				cout << "Write the position of the pixel:" << endl;
                		cin >> temp_position;				
				cout << "Write the green value of the pixel:" << endl;
                		cin >> temp_green;
                		image.setRedPixelValue(temp_position, temp_green);
				temp_position = 0;
				temp_green = 0;
                		writeImage(argv[1], image);
                		break;
			case 3: // [3] Set the blue value of a pixel
				cout << "Write the position of the pixel:" << endl;
                		cin >> temp_position;				
				cout << "Write the blue value of the pixel:" << endl;
                		cin >> temp_blue;
                		image.setRedPixelValue(temp_position, temp_blue);
				temp_position = 0;
				temp_blue = 0;
                		writeImage(argv[1], image);
                		break;
			case 4: // [4] Set the value of a pixel
				cout << "Write the position of the pixel:" << endl;
                		cin >> temp_position;
				cout << "Write the red value of the pixel:" << endl;
                		cin >> temp_red;
				cout << "Write the green value of the pixel:" << endl;
                		cin >> temp_green;
				cout << "Write the blue value of the pixel:" << endl;
                		cin >> temp_blue;
                		image.setPixelValue(temp_position, temp_red, temp_green, temp_blue);
				temp_position = 0;
				temp_red = 0;
				temp_green = 0;
				temp_blue = 0;
                		writeImage(argv[1], image);
                		break;
			default:
                		cout << "Unexpected value: closing the program." << endl;
                		break;
        	}
    	}

    	return 0;
}


int readImage(char filename[], Image& image)
{
    	char *charImage;
	//unsigned char header;
    	ifstream ifp;

   	ifp.open(filename, ios::in | ios::binary);

    	if (!ifp)
    	{
        	cout << "Error reading file " << filename << endl;
        	exit(1);
    	}

    	//ifp.getline(header, 1);

    	charImage = (char *) new char [image.H*image.W*3];

    	ifp.read( reinterpret_cast<char *>(image.red_data), (image.H*image.W)*sizeof(char));
	ifp.read( reinterpret_cast<char *>(image.green_data), (image.H*image.W)*sizeof(char));
	ifp.read( reinterpret_cast<char *>(image.blue_data), (image.H*image.W)*sizeof(char));

    	ifp.close();

    	delete [] charImage;

    	return (1);
}

void grayScaleHistogram(Image image, int intervals){
	//Algo for grayscaling histogram
	//Create a histogram array for number of intervals (will place result in this array)
	int[] hist = new int[intervals];
	//initialising hist
	for(int i = 0; i < hist.length; i++){
		hist[i] = 0;
	}
	
	double gs = 0;
	int position;
	for(int i =0; i < image.height *image.width; i++){
		//gs formula
		gs = (double)image.red_data[i]*.3 + (double)image.blue_data[i+size]*.59 + (double)image.green_data[i+size*2];
		//determining position for pixel
		position = (int)((double)(gs)*intervals/256.0);
		hist[position] = hist[position] + 1;
	}
	// TODO: Output to a text file
	std::fstream outputFile("result.txt");
	for(int i = 0; hist.length; i++)
	{
		outputFile << hist[i] + " ";
	}
	outputFile.close();
}

void maxMin (Image image)
{
	int[] result = new int[6];
	int maxR, maxB, maxG = 0;
	int minR, minB, minG = 0;
	int size = image.height*image.width;

	for (i = 0; i < size; i++)
	{
		if(image.red_data[i] > maxR)
			maxR = image.red_data[i];

		if(image.red_data[i] < minR)
			minR = image.red_data[i];

		if(image.blue_data[i+size] > maxB)
			maxB = image.blue_data[i];

		if(image.blue_data[i+size] < minB)
			minB = image.blue_data[i];

		if(image.green_data[i+size*2] > maxG)
			maxG = image.green_data[i];

		if(image.red_data[i+size*2] < minG)
			minG = image.green_data[i];
	}
	result[0] = maxR;
	result[1] = minR;
	result[2] = maxG;
	result[3] = minG;
	result[4] = maxB;
	result[5] = minB;

	// TODO: Output to a text file
	std::fstream outputFile("result.txt");
	for(int i = 0; result.length; i++)
	{
		outputFile << result[i] + " " ;
	}
	outputFile.close();
}
}
Image mask(Image image, String file)
{

	std::fstream myfile(file, std::ios_base::in);
	short a;
	int i = 0;
	int size = image.height * image.width;
	// reads each short and stores in a
	while(myfile >> a && i < size)
	{
		if(a == 0)
		{
			image.red_data[i] = 0;
			image.blue_data[i + size] = 0;
			image.green_data[i + size*2] = 0;
		}
		i++;
	}
	return image;

}

Image rotate(Image image, double deags)
{
	double pi = 3.1415926535897;
	double radians = pi*deags/180;
	int[] center = new int[2];
	
	center[0] = image.width/2;
	center[1] = image.height/2;
	
	int size = image.height * image.width;
	unsigned char[] red_data = new char[size];
	unsigned char[] blue_data = new char[size];
	unsigned char[] green_data = new char[size];
	Image result = new Image(image.height,image.width);
	int xi, yi, xf, yf;
	
	for (k = 0; k < size; k++)
    {
    	xi = k % image.width - width/2;
    	yi = k / image.width - height/2;

    	xf = cos(radians) * xi - sin(radians) * yi;
    	yf = sin(radians) * xi + cos(radians) * yi;

    	result.red_data[xf+center[0] + (yf + center[0])*image.width]  = image.red_data[k]; 
    	result.blue_data[xf+center[0] + (yf + center[0])*image.width]  = image.blue_data[k]; 
    	result.green_data[xf+center[0] + (yf + center[0])*image.width]  = image.green_data[k]; 

    }  
    return result;

}
Image selectGray(Image image, double radius)
{
	int[] center = new int[2];
	
	center[0] = image.width/2;
	center[1] = image.height/2;

	int yL = center[1] - radius;
	int yF = center[1] + radius;
	int xL = center[0] - radius;
	int xF = center[0] + radius;
	int curr = xf+center[0] + (yf + center[0])*image.width;
	while(yL <= yF)
	{
		while(xL <= xF)
		{
			if((xL - center[0])^2 _+ (yL - center[1]) < radius*radius){
				image.red_data[xL+center[0] + (yL + center[0])*image.width] = floor((double)image.red_data[xL+center[0] + (yL + center[0])*image.width]  * .3);
				image.blue_data[xL+center[0] + (yL + center[0])*image.width] = floor((double)image.blue_data[xL+center[0] + (yL + center[0])*image.width]  * .11);
				image.green_data[xL+center[0] + (yL + center[0])*image.width] = floor((double)image.green_data[xL+center[0] + (yL + center[0])*image.width]  * .59);
			}
			xL++;
		}
		yL++;
	}
	return image;
}





int readImageHeader(char filename[], int& H, int& W)
{
	char firstInteger[4], secondInteger[4];
	ifstream ifp;

   	ifp.open(filename, ios::in | ios::binary);

    	if (!ifp)
    	{
        	cout << "Error reading file " << filename << endl;
        	exit(1);
    	}

	// Read size
    	ifp.read(firstInteger, 4);
	cout << "read1" << endl;
	cout << "firstInteger: " << firstInteger << endl;
    	ifp.read(secondInteger, 4);
	cout << "read2" << endl;
	cout << "secondInteger: " << secondInteger << endl;
	//If a thread is killed, these next two lines are the cause TODO TODO TODO TODO
	H = (unsigned char) firstInteger[3]+(unsigned char) 256*firstInteger[2]+
		 (unsigned char) 256*256*firstInteger[1]+(unsigned char) 256*256*256*firstInteger[0];
	W = (unsigned char) secondInteger[3]+(unsigned char) 256*secondInteger[2]+
		(unsigned char) 256*256*secondInteger[1]+(unsigned char) 256*256*256*secondInteger[0];
	cout << "H: " << H << endl;
	cout << "W: " << W << endl;
	H = 2;
	W = 2;
	cout << "operate" << endl;
	cout << "H: " << H << endl;
	cout << "W: " << W << endl;

    	ifp.close();
	cout << "close" << endl;
    	return(1);
}


int writeImage(char filename[], Image& image)
{
	int H = image.H, W = image.W;    	
	ofstream ofp;

    	ofp.open(filename, ios::out | ios::binary);

    	if (!ofp) 
    	{
        	cout << "Can't open file " << filename << endl;
        	exit(1);
    	}

    	ofp << (unsigned char) H/256*256*256;
	ofp << (unsigned char) H/256*256;
	ofp << (unsigned char) H/256;
    	ofp << (unsigned char) H % 256;
    	ofp << (unsigned char) W/256*256*256;
	ofp << (unsigned char) W/256*256;
	ofp << (unsigned char) W/256;
    	ofp << (unsigned char) W % 256;

   	ofp.write( reinterpret_cast<char *>(image.red_data), (H*W)*sizeof(char));
    	ofp.write( reinterpret_cast<char *>(image.green_data), (H*W)*sizeof(char));
    	ofp.write( reinterpret_cast<char *>(image.blue_data), (H*W)*sizeof(char));

    	if (ofp.fail()) 
    	{
        	cout << "Can't write image " << filename << endl;
        	exit(0);
    	}

    	ofp.close();

    	return(1);
}
