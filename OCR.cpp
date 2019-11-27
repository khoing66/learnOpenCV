
//===============================================================
//FileName:
//          OCR.cpp
//Date:
//          2019/11/25
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================


#include <string>
//#include <tesseract/baseapi.h>
//#include <leptonica/allheaders.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main18( int argc, char** argv)
{

    
    Mat im_src = imread("C:/Users/sualab/Desktop/cow.jpg");
	
	
    //Create a window
    namedWindow("Image", 1);

    //show the image
    imshow("Image", im_src);
    waitKey(0);
    


    return 0;
}