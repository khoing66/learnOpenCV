
//===============================================================
//FileName:
//          matchTemplate.cpp
//Date:
//          2019/11/27
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>
#define WINDOW_NAME1 "【原始图片】"        //为窗口标题定义的宏 
#define WINDOW_NAME2 "【匹配窗口】"        //为窗口标题定义的宏 \

//------------------------------------------------------------------------

using namespace cv;
using namespace std;

//------------------------------------------------------------------------

Mat g_srcImage_; Mat g_templateImage; Mat g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;


//------------------------------------------------------------------------
void on_Matching(int, void*)
{
	//【1】给局部变量初始化
	Mat srcImage;
	g_srcImage_.copyTo(srcImage);

//------------------------------------------------------------------------

	//【2】初始化用于结果输出的矩阵
	int resultImage_rows = g_srcImage_.rows - g_templateImage.rows + 1;
	int resultImage_cols = g_srcImage_.cols - g_templateImage.cols + 1;
	g_resultImage.create(resultImage_rows, resultImage_cols, CV_32FC1);

//------------------------------------------------------------------------

	//【3】进行匹配和标准化
	//参数1：待搜索的图像，8位或32位
	//参数2：模板，需和原图片有以一样的数据类型，且尺寸不能大于原图像
	//参数3：比较结果的映射图像。单通道、32位浮点型图像
			//图像尺寸时W*H，template尺寸时w*h
			//此参数		---->	result为(W-w+1)*(H-h+1)
	//参数4：匹配方法
	matchTemplate(g_srcImage_, g_templateImage, g_resultImage, g_nMatchMethod);
	normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());

//------------------------------------------------------------------------

	//【4】通过函数 minMaxLoc 定位最匹配的位置
	double minValue; double maxValue; Point minLocation; Point maxLocation;
	Point matchLocation;
	minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());

//------------------------------------------------------------------------

	//【5】对于方法 SQDIFF 和 SQDIFF_NORMED, 越小的数值有着更高的匹配结果. 而其余的方法, 数值越大匹配效果越好

	if (g_nMatchMethod == TM_SQDIFF || g_nMatchMethod == TM_SQDIFF_NORMED)
	{
		matchLocation = minLocation;
	}
	else
	{
		matchLocation = maxLocation;
	}

	//【6】绘制出矩形，并显示最终结果
	rectangle(srcImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows), Scalar(0, 0, 255), 2, 8, 0);
	rectangle(g_resultImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows), Scalar(0, 0, 255), 2, 8, 0);

	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, g_resultImage);

}

//------------------------------------------------------------------------

int main( int argc, char** argv)
{

	//【1】载入原图像和模板块
	g_srcImage_ = imread("C:/Users/sualab/Desktop/1.jpg", 1);
	g_templateImage = imread("C:/Users/sualab/Desktop/2.jpg", 1);

//------------------------------------------------------------------------

	//【2】创建窗口
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);

//------------------------------------------------------------------------
	//【3】创建滑动条并进行一次初始化
	createTrackbar("方法", WINDOW_NAME1,&g_nMatchMethod, g_nMaxTrackbarNum, on_Matching);
	on_Matching(0, 0);

//------------------------------------------------------------------------


    waitKey(0);
    
    return 0;
}