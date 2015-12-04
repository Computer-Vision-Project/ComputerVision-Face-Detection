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
	int s1, s2, s3, s4;
	s1 = s2 = s3 = s4 = 0;
	//haar feature type (a)
	for (int i = 0 ; i < 24; i++){
		for (int j = 0; j < 24; j++){
			for (int h = 0; (i+h) < 24; h++){
				for (int w = 0; (j+2*w) < 24; w++){
					s1 = window[i][i+h]*window[j][j+w] ;
					s2 = window[i][i+h]*window[j+w][j+2*w] ;
					features.push_back(s1-s2);
					feature_index ++;	

				}
			}
		}
	}

	//haar feature type (b)
	for (int i = 0 ; i < 24; i++){
		for (int j = 0; j < 24; j++){
			for (int h = 0; (i+h) < 24; h++){
				for (int w = 0; (j+3*w) < 24; w++){
					s1 = window[i][i+h]*window[j][j+w] ;
					s2 = window[i][i+h]*window[j+w][j+2*w] ;
					s3 = window[i][i+h]*window[j+2*w][j+3*w];
					features.push_back(s1-s2+s3);
					feature_index ++;	

				}
			}
		}
	}
	//haar feature type (c)
	for (int i = 0 ; i < 24; i++){
		for (int j = 0; j < 24; j++){
			for (int h = 0; (i+2*h) < 24; h++){
				for (int w = 0; (j+w) < 24; w++){
					s1 = window[i][i+h]*window[j][j+w] ;
					s2 = window[i+h][i+2*h]*window[j][j+w] ;
					features.push_back(s1-s2);
					feature_index ++;	

				}
			}
		}
	}
	//haar feature type (d)
	for (int i = 0 ; i < 24; i++){
		for (int j = 0; j < 24; j++){
			for (int h = 0; (i+3*h) < 24; h++){
				for (int w = 0; (j+w) < 24; w++){
					s1 = window[i][i+h]*window[j][j+w] ;
					s2 = window[i+h][i+2*h]*window[j][j+w] ;
					s3 = window[i+2*h][i+3*h]*window[j][j+w];
					features.push_back(s1-s2+s3);
					feature_index ++;	

				}
			}
		}
	}
	//haar feature type (e)
	for (int i = 0 ; i < 24; i++){
		for (int j = 0; j < 24; j++){
			for (int h = 0; (i+2*h) < 24; h++){
				for (int w = 0; (j+2*w) < 24; w++){
					s1 = window[i][i+h]*window[j][j+w] ;
					s2 = window[i+h][i+2*h]*window[j][j+w] ;
					s3 = window[i][i+h]*window[j+w][j+2*w];
					s4 = window[i+h][i+2*h]*window[j+w][j+2*w];
					features.push_back(s1-s2-s3+s4);
					feature_index ++;	

				}
			}
		}
	} 
	cout << endl<<features.size()<<endl;

	

	return 0;
}
   
