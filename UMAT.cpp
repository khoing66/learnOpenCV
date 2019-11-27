
//===============================================================
//FileName:
//          UMAT.cpp
//Date:
//          2019/11/25
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//Transparent API UMAT
// It makes sense to use the Transparent API only when you are doing a few expensive operations on the image.Otherwise the overhead of moving the image to the GPU dominates the timing.
int main21( int argc, char** argv)
{

	UMat img, gray;
	imread("image.jpg", IMREAD_COLOR).copyTo(img);//我们要做的就是将Mat映像复制到UMat（统一矩阵）类，然后使用标准的OpenCV函数。


//------------------------------------------------------------------------

	cvtColor(img, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, Size(7, 7), 1.5);
	Canny(gray, gray, 0, 50);

//------------------------------------------------------------------------

	imshow("edges", gray);
	waitKey();
	return 0;
    


//------------------------------------------------------------------------
	//Convert Mat to UMat.There are a couple of ways of doing this in C++.
	//Mat mat = imread("image.jpg", IMREAD_COLOR);
	//// Copy Mat to UMat
	//UMat umat;
	//mat.copyTo(umat);


}