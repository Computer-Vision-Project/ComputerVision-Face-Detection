#include <iostream>
#include <vector>
#include <math.h>
#include "Pgm.cpp"

using namespace std;

int main (){

	Image *im;
	im = new Image();
	readImage(im, "gma.pgm");

	int rows, cols;
	
	rows = im->getNRows();
	cols = im->getNCols();

	cout << rows << " " << cols;

	// Haar feature
	vector<double> features;
	int feature_index = 0;
	int window[24][24];
	for (int i = 0 ; i < 24; i++){
		for (int j = 0; j < 24; j++){
			window[i][j] = 0;
		}
	}
	
	for (int i = 0 ; i < 24; i++){
		for (int j = 0; j < 24; j++){
			window[i][j] = im->getPixel(i,j);
		}
	}
	int s1, s2;
	s1 = s2 = 0;
	//haar feature type (a)
	for (int i = 0 ; i < 24; i++){
		for (int j = 0; j < 24; j++){
			for (int h = 0; (i+h)-1 < 24; h++){
				for (int w = 0; (j+2*w)-1 < 24; w++){
					s1 = window[i][i+h-1]*window[j][j+w-1] ;
					s2 = window[i][i+h-1]*window[j+w][j+2*w-1] ;
					features.push_back(s1-s2);
					feature_index ++;	

				}
			}
		}
	}
	cout << endl<<features.size()<<endl;

	

	return 0;
}
   
