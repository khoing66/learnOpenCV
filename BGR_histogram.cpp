
//===============================================================
//FileName:
//          BGR_histogram.cpp
//Date:
//          2019/11/27
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main28(int argc, char** argv)
{

	//【1】载入素材图并显示
	Mat srcImage = imread("C:/Users/sualab/Desktop/red.png");
	imshow("素材图", srcImage);

	vector<Mat> imgs;
	split(srcImage, imgs);
	Mat b = imgs[0];
	Mat g = imgs[1];
	Mat r = imgs[2];

//------------------------------------------------------------------------

		//【2】参数准备
	int bins = 256;
	int hist_size[] = { bins };
	float range[] = { 0, 256 };
	const float* ranges[] = { range };
	MatND redHist, greenHist, blueHist;
	int channels_b[] = { 0 };

//------------------------------------------------------------------------


	//【3】进行直方图的计算（蓝色分量部分）
	calcHist(&srcImage, 1, channels_b, Mat(), //不使用掩膜
		blueHist, 1, hist_size, ranges,
		true, false);

//------------------------------------------------------------------------

	//【4】进行直方图的计算（绿色分量部分）
	int channels_g[] = { 1 };
	calcHist(&srcImage, 1, channels_g, Mat(), // do not use mask
		greenHist, 1, hist_size, ranges,
		true, // the histogram is uniform
		false);

//------------------------------------------------------------------------

	//【5】进行直方图的计算（红色分量部分）
	int channels_r[] = { 2 };
	calcHist(&srcImage, 1, channels_r, Mat(), // do not use mask
		redHist, 1, hist_size, ranges,
		true, // the histogram is uniform
		false);

//------------------------------------------------------------------------
	////也可以直接得到三维数组的直方图陈列矩阵
	//int channels[3];
	//channels[0] = 0;
	//channels[1] = 1;
	//channels[2] = 2;

	//Mat hist;
	//calcHist(&srcImage, 1, channels, Mat(), hist, 3, hist_size, ranges);

//------------------------------------------------------------------------
//绘制直方图


//------------------------------------------------------------------------

	//参数准备
	double maxValue_red, maxValue_green, maxValue_blue;
	minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
	minMaxLoc(greenHist, 0, &maxValue_green, 0, 0);
	minMaxLoc(redHist, 0, &maxValue_red, 0, 0);

	int scale = 1;
	int histHeight = 256;
	Mat histImage = Mat::zeros(histHeight, bins * 3, CV_8UC3);

//------------------------------------------------------------------------

	//正式开始绘制
	for (int i = 0; i < bins; i++)
	{	
		//------------------------------------------------------------------------
		
		//参数准备
		float binValue_blue = blueHist.at<float>(i);
		float binValue_green = greenHist.at<float>(i);
		float binValue_red = redHist.at<float>(i);

		int intensity_blue = cvRound((binValue_blue / maxValue_blue) * histHeight);  //要绘制的高度
		int intensity_green = cvRound((binValue_green / maxValue_green) * histHeight );  //要绘制的高度
		int intensity_red = cvRound((binValue_red / maxValue_red) * histHeight);  //要绘制的高度
		
		//------------------------------------------------------------------------
		
		//绘制蓝色分量的直方图
		rectangle(histImage, Point(i * scale, histHeight - 1),
			Point((i + 1) * scale - 1, histHeight - intensity_blue),
			Scalar(255, 0, 0));
		
		//------------------------------------------------------------------------
		
		//绘制绿色分量的直方图
		rectangle(histImage, Point((i + bins) * scale, histHeight - 1),
			Point((i + bins + 1) * scale - 1, histHeight - intensity_green),
			Scalar(0, 255, 0));
		
		//------------------------------------------------------------------------
		
		//绘制红色分量的直方图
		rectangle(histImage, Point((i + bins * 2) * scale, histHeight - 1),
			Point((i + bins * 2 + 1) * scale - 1, histHeight - intensity_red),
			Scalar(0, 0, 255));

	}
	
	//------------------------------------------------------------------------
	
	//在窗口中显示出绘制好的直方图
	imshow("图像的BGR直方图", histImage);
	waitKey(0);


    return 0;
}