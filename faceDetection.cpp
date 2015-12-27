/*
	Face Detection
	
	Parameter 1: Image
	
	This program uses a trained cascade classifier to detect faces
	in an image, and then outlines the faces in rectangles. 
	
	By Andrew Miloslavsky,
	   Himanshu Tanwar,
	   Manpreet Singh,
	   Yulia Emelyanova,
	   Jaber Janet
*/

#include <opencv2/core/core.hpp>
#include <opencv2/viz/vizcore.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

void detect( const cv::Mat frame, cv::CascadeClassifier face_cascade );

int main( int argc, const char** argv ){

	cv::Mat frame;
	frame = cv::imread( argv[1], CV_LOAD_IMAGE_COLOR );
	
	const std::string face_cascade_classifier = "trained_face_feature.xml";
	cv::CascadeClassifier face_cascade;

	// Attempt to load the face cascade classifier
	if( !face_cascade.load( face_cascade_classifier ) ){

		std::cout << "Error loading image\n"; 
		return -1; 
	}
	else std::cout << "Image saved. Check this directory.\n";
	
	if( !frame.empty() ) detect( frame, face_cascade );
	
	return 0;
}

/*
	Detects faces on an image and displays it to the screen.
*/
void detect( const cv::Mat frame, cv::CascadeClassifier face_cascade ){

	std::vector< cv::Rect > faces;
	cv::Mat frame_gray;
	
	// Create gray scale duplicate image
	cv::cvtColor( frame, frame_gray, CV_BGR2GRAY );
	
	// Run detection
	face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size( 24, 24 ) );
	
	// Iterate through all detected faces
	for( int i = 0; i < faces.size(); i++ ){
		
		// Draw rectangle over each face
		cv::rectangle( 
					frame, 
					cv::Point( faces[i].x, faces[i].y ), 
					cv::Point( faces[i].x + faces[i].width, 
					faces[i].y + faces[i].height ), 
					cv::Scalar( 0, 0, 255 ), // red
					+1, 
					4 
				);
	}
	
	cv::imwrite( "output.pgm", frame ); // Save image
}
