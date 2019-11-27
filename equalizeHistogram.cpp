//
////===============================================================
////FileName:
////          equalizeHistogram.cpp
////Date:
////          2019/11/27
////Author:
////          khoing(https://blog.csdn.net/qq_45391763)
////===============================================================

//
//# include<iostream>
//# include<opencv2/highgui/highgui.hpp>
//using namespace cv;
//using namespace std;
//
//Mat HistEq(Mat& srcImage);
//Mat rgbTOgray(Mat srcImg);
//int main()
//{
//	Mat srcImg = imread("C:/Users/sualab/Desktop/cow.jpg");
//	Mat resultImg;
//	if (!srcImg.data)
//	{
//		cout << "图片不存在" << endl;
//	}
//
////------------------------------------------------------------------------
//
//	if (srcImg.channels() == 3)
//	{
//		Mat gray = rgbTOgray(srcImg);
//		resultImg = HistEq(gray);
//		imshow("gray", gray);
//		imshow("result", resultImg);
//	}
//
////------------------------------------------------------------------------
//
//	if (srcImg.channels() == 1)
//	{
//		resultImg = HistEq(srcImg);
//		imshow("gray", srcImg);
//		imshow("result", resultImg);
//	}
//	waitKey(0);
//	return 0;
//}
//
////------------------------------------------------------------------------
//
////彩色转灰度（其实就是取各个通道的像素点不同比例的和）
//Mat rgbTOgray(Mat srcImg)
//{
//	int rows = srcImg.rows;
//	int cols = srcImg.cols;
//	Mat gray(rows, cols, CV_8UC1);
//	int i, j;
//	for (i = 0; i < rows; i++)
//	{
//		for (j = 0; j < cols; j++)
//		{
//			gray.at<uchar>(i, j) = (int)(0.114 * srcImg.at<Vec3b>(i, j)[0] + 0.587 * srcImg.at<Vec3b>(i, j)[1] + 0.299 * srcImg.at<Vec3b>(i, j)[2]);
//		}
//	}
//	return gray;
//}
//
////------------------------------------------------------------------------
//
////直方图均衡化
//Mat HistEq(Mat& srcImage)
//{
//	int rows = srcImage.rows;
//	int cols = srcImage.cols;
//	Mat resultImage(rows, cols, srcImage.type());
//
//	int Hist[256]; //存放每个像素个数---------------------------(px,Px_num)
//	double HistP[256];//存放每个像素个数占总像素个数的比例-------（px,p)
//	double HistPSum[256];//存放该px之前所有概率之和--------------(px,sum_pxBeforePoint_p)
//	int EqHist[256];//存放一个变换后的px对应表
////------------------------------------------------------------------------
//	//初始化
//	int i, j;
//	for (i = 0; i < 256; i++)
//	{
//		Hist[i] = 0;
//		HistP[i] = 0.0;
//		HistPSum[i] = 0.0;
//		EqHist[i] = 0;
//	}
//
////------------------------------------------------------------------------
//
//	//求每个像素的频数
//	for (i = 0; i < rows; i++)
//	{
//		for (j = 0; j < cols; j++)
//		{
//			Hist[(int)srcImage.at<uchar>(i, j)]++;
//		}
//	}
//
////------------------------------------------------------------------------
//
//	//每个像素的概率
//	for (i = 0; i < 256; i++)
//	{
//		HistP[i] = (double)Hist[i] / (rows * cols);
//	}
//
////------------------------------------------------------------------------
//
//	//每个像素的累计概率
//	HistPSum[0] = HistP[0];
//	for (i = 1; i < 256; i++)
//	{
//		HistPSum[i] = HistP[i] + HistPSum[i - 1];
//		//例如px值为128的像素个数概率只有0.01(例如只有一个128的像素值的像素点)
//		//跟之前的累计概率相加后，值基本上不变。（这样跟127的累计概率相同）
//		//这样*255就会变成127像素值
//		//相当于像素点个数比较少的直接变成与其相近像素点个数比较多的像素值
//		//这样就会损失细节。
//	}
//
////------------------------------------------------------------------------
//
//	//直方图均衡化之后的值
//	for (i = 0; i < 256; i++)
//	{
//		EqHist[i] = cvRound((double)HistPSum[i] * 255);
//	}
//	for (i = 0; i < rows; i++)
//	{
//		for (j = 0; j < cols; j++)
//		{
//			resultImage.at<uchar>(i, j) = EqHist[(int)srcImage.at<uchar>(i, j)];//把对应的新值赋给到原图上
//		}
//	}
//
//
//	return resultImage;
//}
//
//




//------------------------------------------------------------------------




#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main29( int argc, char** argv)
{

    
	// 【1】加载源图像 
	Mat srcImage, dstImage;
	srcImage = imread("C:/Users/sualab/Desktop/cow.jpg", 1);
	if (!srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定图片存在~！ \n"); return false; }

//------------------------------------------------------------------------
	// 【2】转为灰度图并显示出来
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	imshow("原始图", srcImage);

//------------------------------------------------------------------------
	// 【3】进行直方图均衡化

	//参数1：需为8位单通道的图像
	//参数2：输出图像，和原图片有一样的尺寸和类型
	equalizeHist(srcImage, dstImage);


//------------------------------------------------------------------------

	// 【4】显示结果
	imshow("经过直方图均衡化后的图", dstImage);

	// 等待用户按键退出程序
	waitKey(0);

    return 0;
}



