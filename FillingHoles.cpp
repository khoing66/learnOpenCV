
//===============================================================
//FileName:
//          FillingHoles.cpp
//Date:
//          2019/11/23
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


//读入图像。
//二值化图像以获得二进制图像。(1-->2)
//从像素（0，0）进行填充(2--3)  (像素（0,0）连接到背景，进行泛洪操作来提取背景。不受泛洪操作影响的像素必须在边界内）
//反转填充的图像（3-->4)（即，黑色变成白色，白色变成黑色）。
//使用“或”运算将二值化图像与倒流填充（4）图像组合，以获得最终的前景蒙版，

int main9( int argc, char** argv)
{

    //读入图像
	Mat im_in = imread("C:/Users/sualab/Desktop/nickel.jpg", IMREAD_GRAYSCALE);


//------------------------------------------------------------------------

	//二值化
	//大于或等于220 设为0
	//小于220 设为255
	Mat im_th;
	threshold(im_in, im_th, 220, 255, THRESH_BINARY_INV);

//------------------------------------------------------------------------
	//从0，0 开始漫水填充
	Mat im_floodFill = im_th.clone();
	floodFill(im_floodFill, Point(0, 0), Scalar(255));


//------------------------------------------------------------------------

	//反转图像
	Mat im_floodfill_inv;
	bitwise_not(im_floodFill, im_floodfill_inv);

//------------------------------------------------------------------------

	//或 操作
	Mat im_out = (im_th | im_floodfill_inv);

//------------------------------------------------------------------------
	
// Display images
	imshow("Thresholded Image", im_th);
	imshow("Floodfilled Image", im_floodFill);
	imshow("Inverted Floodfilled Image", im_floodfill_inv);
	imshow("Foreground", im_out);
	waitKey(0);
    


    return 0;
}