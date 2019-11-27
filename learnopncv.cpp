// learnopncv.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv2/opencv.hpp>




int main1()
{
   /* std::cout << "Hello World!\n";*/
	using namespace cv;
	using namespace std;
	Mat img = imread("C:/Users/sualab/Desktop/cow.jpg");
	if (img.empty()) {
		cout << "not" << endl;
		return 0;
	}
	imshow("test", img);
	
	Mat imgd,imgdd,imgddd,imgdddd,imgddddd,imgdddddd = img.clone();


	//边缘保留过滤器（  edgePreservingFilter） 
	//输出3通道图像
	//RECURS_FILTER（递归过滤）= 1，NORMCONV_FILTER（归一化卷积）=2。使用RECURS_FILTER选项的速度比NORMCONV_FILTER快3.5倍。
		//当不需要锐化并且速度很重要时，应使用RECURS_FILTER。
	//sigma_s	范围介于0到200之间,该参数确定平滑程度,典型的平滑滤波器将像素值替换为其相邻像素的加权和。
		//邻域越大，过滤后的图像看起来越平滑。邻域的大小与参数sigma_s成正比
	//sigma_r	范围介于0到1之间
		//不能简单地用相邻像素的加权总和代替像素的颜色,我们要用附近像素的平均值替换像素上的颜色值,
		//sigma_s和sigma_r。就像其他平滑滤镜一样，
		//sigma_s控制邻域的大小，而sigma_r（用于sigma_range）控制邻域内不同颜色的平均方式。
		//当sigma_s 取值不变时候，sigma_r 越大图像滤波效果越明显；
		//当sigma_r 取值不变时候，窗口 sigma_s 越大图像模糊效果越明显；
		//当sgma_r取值很小的时候，窗口 sigma_s 取值无论如何变化，图像双边滤波效果都不好！
	edgePreservingFilter(img, imgd, RECURS_FILTER,60,0.4);
	edgePreservingFilter(img, imgdd, NORMCONV_FILTER, 60, 0.4);

	//建议使用  RECURS_FILTER， 因为它比  NORMCONV_FILTER快得多。




	//细节增强过滤器（detailEnhance）
	//滤镜增强了细节，使图像看起来更清晰。
	
	detailEnhance(img, imgddd, 10, 0.15);




	//铅笔素描过滤器（PencilSketch）
	//输出看起来像铅笔素描。有两个输出，一个是将滤镜应用于彩色输入图像的结果，另一个是将其应用于输入图像的灰度版本的结果
	//第二个参数输出灰度图像
	//参数3:输出彩色图像
	//第五个参数shade_factor（范围0到0.1）是输出图像强度的简单缩放。值越高，结果越亮。
	pencilSketch(img, imgdddd, imgddddd, 60, 0.07);




	//程式化筛选器（程式化）Stylization Filter ( stylization )
	//输出看起来像是使用水彩画的图像。
	stylization(img, imgdddddd, 60, 0.07);







	waitKey(0);
	return 0;






}

