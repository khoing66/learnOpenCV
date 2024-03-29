
//===============================================================
//FileName:
//          convexhull.cpp
//Date:
//          2019/11/25
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main22( int argc, char** argv)
{

    
    Mat im_src = imread("C:/Users/sualab/Desktop/sample.jpg");

//------------------------------------------------------------------------

	// declare images 
	Mat gray, blur_image, threshold_output;

//------------------------------------------------------------------------

	// convert to grayscale 
	cvtColor(im_src, gray, COLOR_BGR2GRAY);

//------------------------------------------------------------------------
	
	// add blurring to the input image
	blur(gray, blur_image, Size(3, 3));

//------------------------------------------------------------------------
	// binary threshold the input image
	threshold(gray, threshold_output, 200, 255, THRESH_BINARY);


//------------------------------------------------------------------------
	// show source image
	namedWindow("Source", WINDOW_AUTOSIZE);
	imshow("Source", im_src);

//------------------------------------------------------------------------
	// Convex Hull implementation


	Mat src_copy = im_src.clone();

//------------------------------------------------------------------------

	// contours vector  
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;

//------------------------------------------------------------------------

	// find contours for the thresholded image
	findContours(threshold_output, contours, hierarchy, RETR_TREE,
		CHAIN_APPROX_SIMPLE, Point(0, 0));

//------------------------------------------------------------------------

	// create convex hull vector
	vector< vector<Point> > hull(contours.size());

//------------------------------------------------------------------------

	// find convex hull for each contour
	for (int i = 0; i < contours.size(); i++)
		convexHull(Mat(contours[i]), hull[i], false);//求每个轮廓的凸包点

//------------------------------------------------------------------------

	// create empty black image
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);

//------------------------------------------------------------------------

	// draw contours and convex hull on the empty black image 
	for (int i = 0; i < contours.size(); i++) {
		Scalar color_contours = Scalar(0, 255, 0); // color for contours : blue
		Scalar color = Scalar(255, 255, 255); // color for convex hull : white
		// draw contours
		drawContours(drawing, contours, i, color_contours, 2, 8, vector<Vec4i>(), 0, Point());
		// draw convex hull
		drawContours(drawing, hull, i, color, 2, 8, vector<Vec4i>(), 0, Point());
	}

//------------------------------------------------------------------------


	namedWindow("Output", WINDOW_AUTOSIZE);
	imshow("Output", drawing);
	imwrite("C:/Users/sualab/Desktop/sampleMark.jpg", drawing);




	




    //show the image
    imshow("Image", im_src);
    waitKey(0);
    


    return 0;
}