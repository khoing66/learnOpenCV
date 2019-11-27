
//===============================================================
//FileName:
//          homegraphy2.cpp
//Date:
//          2019/11/23
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;



struct userdata {
	Mat im;
	vector<Point2f> points;
};

void mouseHandler(int event, int x, int y, int flags, void* data_ptr)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		userdata* data = ((userdata*)data_ptr);
		circle(data->im, Point(x, y), 3, Scalar(0, 255, 255), 5, CV_AA);
		imshow("Image", data->im);
		if (data->points.size() < 4)
		{
			data->points.push_back(Point2f(x, y));
		}
	}

}


int main8( int argc, char** argv)
{

    //原图像
    Mat im_src = imread("C:/Users/sualab/Desktop/book1.jpg");


	//目标图
	Size size(300, 400);
	Mat im_dst = Mat::zeros(size, CV_8UC3);


//------------------------------------------------------------------------

	// Create a vector of points.
	vector<Point2f> pts_dst;
	pts_dst.push_back(Point2f(0, 0));
	pts_dst.push_back(Point2f(size.width - 1, 0));
	pts_dst.push_back(Point2f(size.width - 1, size.height - 1));
	pts_dst.push_back(Point2f(0, size.height - 1));



//------------------------------------------------------------------------

	//Create a window
	namedWindow("Image", 1);

//------------------------------------------------------------------------


	Mat im_temp = im_src.clone();

	userdata data;
	data.im = im_temp;


//------------------------------------------------------------------------

	//set the callback function for any mouse event
	setMouseCallback("Image", mouseHandler, &data);//会把data传给调用函数，函数可以对data进行更改


//------------------------------------------------------------------------



	 //show the image
	imshow("Image", im_temp);
	waitKey(0);

//------------------------------------------------------------------------


	Mat tform = findHomography(data.points, pts_dst);
	warpPerspective(im_src, im_dst, tform, size);




//------------------------------------------------------------------------

	imshow("Image", im_dst);
	waitKey(0);

    

    return 0;
}
