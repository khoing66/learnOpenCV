
//===============================================================
//FileName:
//          H-S-Histogram.cpp
//Date:
//          2019/11/26
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main26( int argc, char** argv)
{

	//【1】载入源图，转化为HSV颜色模型
	Mat hsvImage;
    Mat srcImage = imread("C:/Users/sualab/Desktop/1.jpg");
	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);

//------------------------------------------------------------------------
	//【2】参数准备
	//将色调量化为30个等级，将饱和度量化为32个等级
	int hueBinNum = 30;//色调的直方图直条数量
	int saturationBinNum = 32;//饱和度的直方图直条数量
	int histSize[] = { hueBinNum, saturationBinNum };
	
	// 定义色调的变化范围为0到179
	float hueRanges[] = { 0, 180 };

	//定义饱和度的变化范围为0（黑、白、灰）到255（纯光谱颜色）
	float saturationRanges[] = { 0, 256 };

	const float* ranges[] = { hueRanges, saturationRanges };

	MatND dstHist;//多维数组
	
	//参数准备，calcHist函数中将计算第0通道和第1通道的直方图
	int channels[] = { 0, 1 };

//------------------------------------------------------------------------

	//【3】正式调用calcHist，进行直方图计算
	//参数1：const Mat* 类型的images, 需要图片有相同的深度，
	//参数2：int  图片的数目
	//参数3：通道索引  （数组，里面包含通道的索引，例如：int channels[] = { 0, 1 };）
	//参数4: mask,要统计图像某个局部区域的直方图只需要构建一副掩模图像 ，必须为8位，并且与image[i]有同样大小的尺寸。将要统计的部分设置成白色，其余部分为黑色，就构成了一副掩模图像。然后把这个掩模图像传给函数就可以了。
	//参数5：输出的直方图，一个二维数组
	//参数6：int 直方图的维度，必须是正数，
	//参数7：const int*   存放每个维度直方图尺寸的数组(包含多少直条）
	//参数8：const float**每一维数值的取值范围数组  ranges[] = {  { 0, 180 }, { 0, 256 } };
	//参数9：bool类型的uniform，指示直方图是否均匀的标识符，默认true
	//参数10：累计标识符，false表示直方图在配置阶断会被清零

	calcHist(&hsvImage, 1, channels, Mat(), dstHist, 2, histSize, ranges, true, false);

//------------------------------------------------------------------------
	
	//【4】为绘制直方图准备参数
	double maxValue = 0;//最大值

	//参数1：输入的单通道阵列，一个二维数组
	//参数2：double* 类型的minVal 返回最小值的指针，无需返回设为Null
	//参数3：double* 类型的maxVal 返回最大值的指针，无需返回设为Null
	//参数4: Point* 类型的minLoc 返回最小位置的指针（二维情况下），无需返回设为Null
	//参数5：Point* 类型的maxLoc 返回最大位置的指针（二维情况下），无需返回设为Null
	//参数6：InputArray 类型的mask，用于选择子阵列的可选掩膜
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);//查找数组和子数组的全局最大值存入maxValue中

	int scale = 10;//sacle为一个bin,例如(0,10]为一个bin
	Mat histImg = Mat::zeros(saturationBinNum * scale, hueBinNum * 10, CV_8UC3);


//------------------------------------------------------------------------

	//【5】双层循环，进行直方图绘制
	for (int hue = 0; hue < hueBinNum; hue++)
		for (int saturation = 0; saturation < saturationBinNum; saturation++)
		{
			float binValue = dstHist.at<float>(hue, saturation);//直方图组距的值
			int intensity = cvRound(binValue / maxValue * 255);//强度 //255为最大值对应的纵坐标值

			//正式进行绘制
			rectangle(histImg, Point(hue * scale, saturation * scale),
				Point((hue + 1) * scale - 1, (saturation + 1) * scale - 1),
				Scalar::all(intensity), FILLED);
		}

//------------------------------------------------------------------------

	//【6】显示效果图
	imshow("素材图", srcImage);
	imshow("H-S 直方图", histImg);

	waitKey();

 

    return 0;
}