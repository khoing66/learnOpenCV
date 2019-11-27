
//===============================================================
//FileName:
//          ests.cpp
//Date:
//          2019/11/25
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================



#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main24(int argc, char** argv)
{


	Mat im_src = imread("C:/Users/sualab/Desktop/cow.jpg");
	Mat im_src2 = imread("C:/Users/sualab/Desktop/airplane.jpg");

	Mat roi = im_src(Rect(200, 250, im_src.cols-200, im_src.rows-250));

	circle(roi, Point(20, 20), 20, Scalar(0, 0, 255), 2);
	
	 


	//Create a window
	namedWindow("Image", 1);

	//show the image 
	imshow("Image", im_src);
	waitKey(0);



	return 0;
}