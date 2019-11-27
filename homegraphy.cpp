
//===============================================================
//FileName:
//          homegraphy.cpp
//Date:
//          2019/11/23
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;


//把原图中点围住的区域覆盖到目标图上。在输出图上进行展示
int main7()
{

	//原图
	Mat im_src = imread("C:/Users/sualab/Desktop/book2.jpg");
	
	//原图中书的四个点
	vector<Point2f> pts_src;
	pts_src.push_back(Point2f(141, 131));
	pts_src.push_back(Point2f(480, 159));
	pts_src.push_back(Point2f(493, 630));
	pts_src.push_back(Point2f(64, 601));

//------------------------------------------------------------------------

	//目标图
	Mat im_dst = imread("C:/Users/sualab/Desktop/book1.jpg");

	//目标图中的四个点
	vector<Point2f> pts_dst;
	pts_dst.push_back(Point2f(318, 256));
	pts_dst.push_back(Point2f(534, 372));
	pts_dst.push_back(Point2f(316, 670));
	pts_dst.push_back(Point2f(73, 473));


//------------------------------------------------------------------------

	//计算 单应矩阵(homegraphy)
	Mat h = findHomography(pts_src, pts_dst);

//------------------------------------------------------------------------

	//输出图
	Mat im_out;
	warpPerspective(im_src, im_out, h, im_dst.size());



//------------------------------------------------------------------------
	imwrite("C:/Users/sualab/Desktop/im_out.jpg",im_out);

	waitKey(0);
	
	




	return 0;
}

