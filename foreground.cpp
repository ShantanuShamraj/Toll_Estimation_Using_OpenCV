/*------------------------------------------------------------------------------------------*\
   This file contains material supporting chapter 10 of the cookbook:  
   Computer Vision Programming using the OpenCV Library. 
   by Robert Laganiere, Packt Publishing, 2011.

   This program is free software; permission is hereby granted to use, copy, modify, 
   and distribute this source code, or portions thereof, for any purpose, without fee, 
   subject to the restriction that the copyright notice may not be removed 
   or altered from any source or altered source distribution. 
   The software is released on an as-is basis and without any warranties of any kind. 
   In particular, the software is not guaranteed to be fault-tolerant or free from failure. 
   The author disclaims all warranties with regard to this software, any use, 
   and any consequent failure, is purely the responsibility of the user.
 
   Copyright (C) 2010-2011 Robert Laganiere, www.laganiere.name
\*------------------------------------------------------------------------------------------*/
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include"black.cpp"
using namespace cv;
using namespace std;

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>

#include "videoprocessor.h"
#include "BGFGSegmentor.h"

int main()
{
         int n = 0;                                                               //*********
        char filename[200];                                                      //*********
        string window_name = "video | q or esc to quit";                         //********* 
        cout << "Press space to save a picture. q or esc to quit" << endl;       //********* 
      //namedWindow(window_name, CV_WINDOW_KEEPRATIO); //resizable window;       //*********
        Mat frame1;                                                             

        
	// Open the video file
    cv::VideoCapture capture("pro.mkv");
	// check if video successfully opened
	if (!capture.isOpened())
		return 0;

	// current video frame
	cv::Mat frame; 

	cv::Mat foreground;
	// foreground binary image
         cv::namedWindow("Extracted Foreground",CV_WINDOW_NORMAL);

	cv::resizeWindow("Extracted Foreground",400,300);
         cv::moveWindow("Extracted Foreground",850,425);
 
         cv::namedWindow("Src",CV_WINDOW_NORMAL);
 cv::moveWindow("Src",850,45);
	 cv::resizeWindow("Src",400,300);
         
         
	cv::BackgroundSubtractorMOG mog;

	bool stop(false);
	// for all frames in video
	while (!stop) {

		// read next frame if any
		if (!capture.read(frame))
			break;

		// update the background
		// and return the foreground
		mog(frame,foreground,0.01);

		// Complement the image
		cv::threshold(foreground,foreground,128,255,cv::THRESH_BINARY_INV);



  
          









		// show foreground
		cv::imshow("Extracted Foreground",foreground);

int width=frame.cols;
int height=frame.rows;
 // red line, which is not anti-aliased


  //cv::line(frame, cv::Point(width/4,0), cv::Point(width/4,height), cv::Scalar(0,200,0), 50, 50);  

cv::imshow("Src",frame);

               char key = (char) waitKey(50); //delay N millis, usually long enough to display and capture input
              switch (key)
              {
                case 'q':
                case 'Q':
                case 27: //escape key
                    return 0;
                case ' ': //Save an image
                    sprintf(filename, "filename%.3d.jpg", n++);
                    imwrite(filename, foreground);
                    fun(filename);                    
			cout << "Saved " << filename << endl;
                    break;
                default:
                    break;
            }

		//introduce a delay
		 //or press key to stop
		//if (cv::waitKey(10)>=0)
		//stop= true;
	}

	cv::waitKey();

	// Create video procesor instance
	VideoProcessor processor;

	// Create background/foreground segmentor 
	BGFGSegmentor segmentor;
	segmentor.setThreshold(25);

	// Open video file
	processor.setInput("../bike.avi");

	// set frame processor
	processor.setFrameProcessor(&segmentor);

	// Declare a window to display the video
	//processor.displayOutput("Extracted Foreground");

	// Play the video at the original frame rate
	processor.setDelay(1000./processor.getFrameRate());

	// Start the process
	processor.run();

	cv::waitKey();
}
