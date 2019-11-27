
//===============================================================
//FileName:
//          compareHist.cpp
//Date:
//          2019/11/27
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================


#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main30( int argc, char** argv)
{

//------------------------------------------------------------------------

	//【1】声明储存基准图像 和 另外两张对比图像的矩阵( RGB 和 HSV )
	Mat srcImage_base, hsvImage_base;
	Mat srcImage_test1, hsvImage_test1;
	Mat srcImage_test2, hsvImage_test2;
	Mat hsvImage_halfDown;

	//【2】载入基准图像(srcImage_base) 和两张测试图像srcImage_test1、srcImage_test2，并显示
	srcImage_base = imread("C:/Users/sualab/Desktop/1.jpg", 1);
	srcImage_test1 = imread("C:/Users/sualab/Desktop/2.jpg", 1);
	srcImage_test2 = imread("C:/Users/sualab/Desktop/3.jpg", 1);
	//显示载入的3张图像
	imshow("基准图像", srcImage_base);
	imshow("测试图像1", srcImage_test1);
	imshow("测试图像2", srcImage_test2);


//------------------------------------------------------------------------
	// 【3】将图像由BGR色彩空间转换到 HSV色彩空间
	cvtColor(srcImage_base, hsvImage_base, COLOR_BGR2HSV);
	cvtColor(srcImage_test1, hsvImage_test1, COLOR_BGR2HSV);
	cvtColor(srcImage_test2, hsvImage_test2, COLOR_BGR2HSV);


//------------------------------------------------------------------------

	//【4】创建包含基准图像下半部的半身图像(HSV格式)
	hsvImage_halfDown = hsvImage_base(Range(hsvImage_base.rows / 2, hsvImage_base.rows - 1), Range(0, hsvImage_base.cols - 1));
		//srcImage_base(rowRange,colRange)
//------------------------------------------------------------------------
	
	//【5】初始化计算直方图需要的实参
	int h_bins = 50; int s_bins = 60;
	int histSize[] = { h_bins, s_bins };

	// hue色调 的取值范围从0到256, saturation饱和度 的取值范围从0到180 
	//这里最大180并不代表不能取180以上的值，而是统计直方图的范围到180，（0,180）x坐标的范围
	float h_ranges[] = { 0, 256 };
	float s_ranges[] = { 0, 180 };
	const float* ranges[] = { h_ranges, s_ranges };
	// 使用第0和第1通道
	int channels[] = { 0, 1 };

//------------------------------------------------------------------------
	// 【6】创建储存直方图的 MatND 类的实例:
	//MatND是存储直方图的一种数据结构

	MatND baseHist;
	MatND halfDownHist;
	MatND testHist1;
	MatND testHist2;

//------------------------------------------------------------------------

	// 【7】计算基准图像，两张测试图像，半身基准图像的HSV直方图:


	calcHist(&hsvImage_base, 1, channels, Mat(), baseHist, 2, histSize, ranges, true, false);
	normalize(baseHist, baseHist, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsvImage_halfDown, 1, channels, Mat(), halfDownHist, 2, histSize, ranges, true, false);
	normalize(halfDownHist, halfDownHist, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsvImage_test1, 1, channels, Mat(), testHist1, 2, histSize, ranges, true, false);
	normalize(testHist1, testHist1, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsvImage_test2, 1, channels, Mat(), testHist2, 2, histSize, ranges, true, false);
	normalize(testHist2, testHist2, 0, 1, NORM_MINMAX, -1, Mat());

//------------------------------------------------------------------------


	//【8】按顺序使用4种对比标准将基准图像的直方图与其余各直方图进行对比:
	for (int i = 0; i < 4; i++)
	{
		//进行图像直方图的对比
		int compare_method = i;
		double base_base = compareHist(baseHist, baseHist, compare_method);
		double base_half = compareHist(baseHist, halfDownHist, compare_method);
		double base_test1 = compareHist(baseHist, testHist1, compare_method);
		double base_test2 = compareHist(baseHist, testHist2, compare_method);

		//输出结果
		printf(" 方法 [%d] 的匹配结果如下：\n\n 【基准图 - 基准图】：%f, 【基准图 - 半身图】：%f,【基准图 - 测试图1】： %f, 【基准图 - 测试图2】：%f \n-----------------------------------------------------------------\n"
			, i
			, base_base
			, base_half
			, base_test1
			, base_test2);

	}

	//方法0和2 表示值越大相似度越高
	//方法1和3 表示值越小相似度越高

		//1.相关系数的标准(method = CV_COMP_CORREL) 值越大，相关度越高，最大值为1，最小值为0

		//2 卡方系数的标准(method = CV_COMP_CHISQR) 值越小，相关度越高，最大值无上界，最小值0

		//3 相交系数的标准(method = CV_COMP_INTERSECT)值越大，相关度越高，最大值为9.455319，最小值为0

		//4 巴氏系数的标准(method = CV_COMP_BHATTACHARYYA) 值越小，相关度越高，最大值为1，最小值为0

//------------------------------------------------------------------------

	printf("检测结束。");
	waitKey(0);
	return 0;

}