
//===============================================================
//FileName:
//          clacBackProject.cpp
//Date:
//          2019/11/27
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat g_srcImage; Mat g_hsvImage; Mat g_hueImage;
int g_bins = 30;//直方图组距,越大，特征点越多。就是多个个bin
//------------------------------------------------------------------------

void on_BinChange(int, void*)
{
	//【1】参数准备
	MatND hist;
	int histSize = MAX(g_bins, 2);//分成多少个bin

	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };

	//【2】计算直方图并归一化
	calcHist(&g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	//【3】计算反向投影
	MatND backproj;

	//参数1：输入的数组，所有的矩阵必须有相同的尺寸和深度（图片）
	//参数2：第一个参数输入的矩阵数，输入图像的个数
	//参数3：需要统计的通道索引 int* 
	//参数4：输入的直方图
	//参数5：输出的反向投影图,为单通道，并和原图有相同的大小和尺寸
	//参数6：每一维数组的取值范围
	//参数7：double scale 输出方向投影可选的缩放因子，默认值1
	//参数8：直方图是否均匀的标识符，有默认值true
	calcBackProject(&g_hueImage, 1, 0, hist, backproj, &ranges, 1, true);

	//------------------------------------------------------------------------

		//【4】显示反向投影
	imshow("反向投影图", backproj);

	//------------------------------------------------------------------------

		//【5】绘制直方图的参数准备
	int w = 400; int h = 400;
	int bin_w = cvRound((double)w / histSize);
	Mat histImg = Mat::zeros(w, h, CV_8UC3);

	//------------------------------------------------------------------------

		//【6】绘制直方图
	for (int i = 0; i < g_bins; i++)
	{
		rectangle(histImg, Point(i * bin_w, h), Point((i + 1) * bin_w, h - cvRound(hist.at<float>(i) * h / 255.0)), Scalar(100, 123, 255), -1);
	}

	//------------------------------------------------------------------------

		//【7】显示直方图窗口
	imshow("直方图", histImg);
}

//------------------------------------------------------------------------

int main31( int argc, char** argv)
{

	//【1】读取源图像，并转换到 HSV 空间
	g_srcImage = imread("C:/Users/sualab/Desktop/cow.jpg", 1);
	if (!g_srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定图片存在~！ \n"); return false; }
	cvtColor(g_srcImage, g_hsvImage, COLOR_BGR2HSV);
 
 //------------------------------------------------------------------------
	g_hueImage.create(g_hsvImage.size(), g_hsvImage.depth());
	int ch[] = { 0, 0 };
	//0通道 -- 到  -- 0通道

	//重排图像通道
	//参数1：输入的数组，所有的矩阵必须有相同的尺寸和深度（图片）
	//参数2：第一个参数输入的矩阵数，输入图像的个数
	//参数3：输出的数组，所有的矩阵必须有相同的尺寸和深度（图片）
	//参数4：第三个参数输出的矩阵数，输出图像的个数
	mixChannels(&g_hsvImage, 1, &g_hueImage, 1, ch, 1);

/*
//应用实例(以下代码演示mixChannels的使用）
//------------------------------------------------------------------------
	//将一个4通道的RGBA图像转化为3通道BGR和一个单独的Alpha通道
	Mat rgba(100, 100, CV_8UC4, Scalar(1, 2, 3, 4));
	Mat bgr(rgba.rows, rgba.cols, CV_8UC3);
	Mat alpha(rgba.rows, rgba.cols, CV_8UC1);


	Mat out[] = { bgr , alpha };
	//将rgba[0] -->bgr[2] , rgba[1] --> bgr[1]
	//将rgba[2] -->bgr[0] , rgba[3] --> alpha[0]

	int from_to[] = { 0,2, 1,1, 2,0, 3,3 };
	mixChannels(&rgba, 1, out, 2, from_to, 4);
*/
//------------------------------------------------------------------------

	//【3】创建 Trackbar 来输入bin的数目
	namedWindow("test", WINDOW_AUTOSIZE);
	createTrackbar("色调组距 ", "test", &g_bins, 180, on_BinChange);
	on_BinChange(0, 0);//进行一次初始化

	//【4】显示效果图
	imshow("test", g_srcImage);

    waitKey(0);
    


    return 0;
}

