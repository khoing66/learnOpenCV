
//===============================================================
//FileName:
//          Histogram.cpp
//Date:
//          2019/11/26
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main27( int argc, char** argv)
{

	//【1】载入原图并显示
	Mat srcImage = imread("C:/Users/sualab/Desktop/1.jpg", IMREAD_GRAYSCALE);
	imshow("原图", srcImage);
	if (!srcImage.data) { cout << "fail to load image" << endl; 	return 0; }

//------------------------------------------------------------------------

	//【2】定义变量
	MatND dstHist;       
	int dims = 1;
	float hranges[] = { 0, 255 };
	const float* ranges[] = { hranges };   // 这里需要为const类型
	int size = 256;
	int channels = 0;

//------------------------------------------------------------------------


	//【3】计算图像的直方图
	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);    

//------------------------------------------------------------------------

	int scale = 1;

	Mat dstImage(size * scale, size, CV_8U, Scalar(0));


	//【4】获取最大值和最小值
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);  

//------------------------------------------------------------------------

	//【5】绘制出直方图
	int hpt = saturate_cast<int>(0.9 * size);//这里选用图高的90%作为直方图的最大值
	for (int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i);         
		int realValue = saturate_cast<int>((binValue / maxValue) * hpt);
		rectangle(dstImage, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realValue), Scalar(255));
	}
	imshow("一维直方图", dstImage);
	waitKey(0);
	return 0;
}