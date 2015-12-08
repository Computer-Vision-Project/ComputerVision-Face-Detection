/*
	Haar Feature Detection
	
	This program detects uses Haar features to detect possible features
	of a face. It collects data in a 24 x 24 window, and processes it
	using Integral Imaging to efficiently calculate the integral. 
	
	By Andrew Miloslavsky,
	   Himanshu Tanwar,
	   Manpreet Singh,
	   Yulia Emelyanova,
	   Jaber Janet
*/

#include <iostream>
#include <vector>
#include <math.h>
#include "Image.h"

std::vector< std::vector< double > > calculateHaarFeatures( int window[][24] );
void calculateFirstWindow( const Image& image );
void calculateAllWindows( const Image& image );
void printFeatures( std::vector< std::vector< double > > );
void getWindow( const Image& image, int window[][24], int r, int c );

int main ( int argc, char** argv ){

	if( argc < 2 ) return -1;
	
	const char* IMAGE = argv[ 1 ];

	Image *im = new Image();
	readImage( im, IMAGE );

	calculateFirstWindow( *im ); // Calculate first window Haar features.

	//calculateAllWindows( *im );

	return 0;
}

void calculateFirstWindow( const Image& image ){
	
	/*
		Various window sizes have been used for Face Detection.
		Commonly they range from 16x16 to 32x32.
		24x24 generally provided the most stable detection.
	*/
	int window[24][24]; // 24 x 24 window
	
	getWindow( image, window, 0, 0 );
	
	// Calculate Haar Images
	std::vector< std::vector< double > > 
		features = calculateHaarFeatures( window );
	
	printFeatures( features ); // Output feature stats
}

/*
	Calculate the Haar features each 24 x 24 window for the image.
	Output the results.
*/
void calculateAllWindows( const Image& im ){

	int rows = im.getNRows(),
		cols = im.getNCols();

	int window[24][24]; // 24 x 24 window

	for( int h = 0; h < rows - 24; h++ ){
		for( int w = 0; w < cols - 24; w++ ){
			
			getWindow( im, window, h, w );
			
			// Calculate Haar Images
			std::vector< std::vector< double > > 
				features = calculateHaarFeatures( window );
			
			printFeatures( features ); // Output feature stats
		}
	}
}

/*
	Calculates the Haar features each 24 x 24 window for the image.
*/
std::vector< std::vector< double > > 
calculateHaarFeatures( int window[][24] ){
	
	// Haar features ( A, B, C, D, E )
	std::vector<double> a; // feature a
	std::vector<double> b; // feature b
	std::vector<double> c; // feature c
	std::vector<double> d; // feature d
	std::vector<double> e; // feature e
	
	std::vector< std::vector< double > > result;
	
	int s1, s2, s3, s4;
	s1 = s2 = s3 = s4 = 0;
	for (int i = 1; i <= 24; i++){
		for (int j = 1; j <= 24; j++){
		
			// Haar feature type (a)
			for (int h = 0; (i+h-1) <= 24; h++){
				for (int w = 0; (j+2*w-1) <= 24; w++){
				
					s1 = window[i][i+h-1]*window[j][j+w-1]; // Black portion
					s2 = window[i][i+h-1]*window[j+w][j+2*w-1]; // White portion
					
					a.push_back( s1 - s2 ); // add 'a' feature
				}
			}
			
			// Haar feature type (b)
			for (int h = 0; (i+h-1) <= 24; h++){
				for (int w = 0; (j+3*w-1) <= 24; w++){
				
					s1 = window[i][i+h-1]*window[j][j+w-1]; // Black portion
					s2 = window[i][i+h-1]*window[j+w][j+2*w-1]; // White portion
					s3 = window[i][i+h-1]*window[j+2*w][j+3*w-1]; // White portion
					
					b.push_back( s1-s2+s3 ); // add 'b' feature 
				}
			}
			
			// Haar feature type (c)
			for (int h = 0; (i+2*h-1) <= 24; h++){
				for (int w = 0; (j+w-1) <= 24; w++){
				
					s1 = window[i][i+h-1]*window[j][j+w-1]; // Black portion
					s2 = window[i+h][i+2*h-1]*window[j][j+w-1]; // White portion
					
					c.push_back( s1-s2 ); // add 'c' feature
				}
			}
			
			// Haar feature type (d)
			for (int h = 0; (i+3*h-1) <= 24; h++){
				for (int w = 0; (j+w-1) <= 24; w++){
				
					s1 = window[i][i+h-1]*window[j][j+w-1]; // Black portion
					s2 = window[i+h][i+2*h-1]*window[j][j+w-1]; // White portion
					s3 = window[i+2*h][i+3*h-1]*window[j][j+w-1]; // White portion
					
					d.push_back( s1-s2+s3 ); // add 'd' feature
				}
			}
			
			// Haar feature type (e)
			for (int h = 0; (i+2*h-1) <= 24; h++){
				for (int w = 0; (j+2*w-1) <= 24; w++){
				
					s1 = window[i][i+h-1]*window[j][j+w-1]; // Black portion
					s2 = window[i+h][i+2*h-1]*window[j][j+w-1]; // White portion
					s3 = window[i][i+h-1]*window[j+w][j+2*w-1]; // Black portion
					s4 = window[i+h][i+2*h-1]*window[j+w][j+2*w-1]; // White portion
					
					e.push_back( s1-s2-s3+s4 ); // add 'e' feature
				}
			}
		}
	}
	
	// Collect all the features	
	result.push_back( a );
	result.push_back( b );
	result.push_back( c );
	result.push_back( d );
	result.push_back( e );
	
	return result; // Return the features
}

/*
	Prints the features for a given window.
*/
void printFeatures( std::vector< std::vector< double > > features ){
				
	int featureCount = 0;

	char feature = 'A';

	for( int k = 0; k < features.size(); k++ ){
		
		featureCount += features[k].size();
		std::cout << "Feature: " << feature++ << ": " << features[ k ].size() << std::endl;
	}
		
	std::cout << "Total Features: " << featureCount << std::endl;
}

/*
	Gets the window for coordinate [r,c]
*/
void getWindow( const Image& im, int window[][24], int r, int c ){
	
	// Gather window data
	for ( int i = r; i < r+24; i++ )
		for ( int j = c; j < c+24; j++ )
			window[i][j] = im.getPixel( i,j );
}