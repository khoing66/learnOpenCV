
//===============================================================
//FileName:
//          dft.cpp
//Date:
//          2019/11/26
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================


#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main25( int argc, char** argv)
{

	//【1】以灰度模式读取原始图像并显示
    Mat srcImage = imread("C:/Users/sualab/Desktop/backGround.jpg", IMREAD_GRAYSCALE);


//------------------------------------------------------------------------
	// 【2】将输入图像延扩到最佳的尺寸，边界用0补充


	//为了提高离散傅里叶变换的运行速度，一般都是图像2、3、5的整数倍，需要扩充图像
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);

	//将添加的像素初始化为0.
	Mat padded;
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

 
 //------------------------------------------------------------------------
	//【3】为傅立叶变换的结果(实部和虚部)分配存储空间。
	//将planes数组组合 合并成一个多通道的数组complexI

	//傅里叶变换的结果是复数，会有两个图像，此外频域范围远远超过空间值，所以转成float中，
	Mat planes[] = { Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);


//------------------------------------------------------------------------
	//【4】进行就地离散傅里叶变换
	dft(complexI, complexI);

//------------------------------------------------------------------------

	//【5】将复数转换为幅值，即=> log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
		//复数包含实数部分(Re) 和虚数部分(Im)
	split(complexI, planes); // 将多通道数组complexI分离成几个单通道数组，planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	
	//求幅值，参数1:实部，参数2：虚部， 参数3：和参数1有同样的大小和类型
	magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude  
	Mat magnitudeImage = planes[0];



//------------------------------------------------------------------------

	//【6】进行对数尺度(logarithmic scale)缩放

	//傅里叶变换的幅度值范围大到不适合在屏幕上显示。为了在屏幕中凸显高低变化的连续性。log(1+m)
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);//求自然对数

//------------------------------------------------------------------------

	//【7】剪切和重分布幅度图象限

	//因为在第二步延伸了图像，
	//若有奇数行或奇数列，进行频谱裁剪      
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
	//重新排列傅立叶图像中的象限，使得原点位于图像中心  
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));   // ROI区域的左上
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));  // ROI区域的右上
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));  // ROI区域的左下
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy)); // ROI区域的右下
	//交换象限（左上与右下进行交换）
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	//交换象限（右上与左下进行交换）
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

//------------------------------------------------------------------------

	//【8】归一化，用0到1之间的浮点值将矩阵变换为可视的图像格式

	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

//------------------------------------------------------------------------

	//【9】显示效果图
	imshow("频谱幅值", magnitudeImage);
	waitKey();
  

	//图像最明亮的像素放到中间，然后逐渐变暗，在边缘上的像素最暗，这样可以发现图像中亮、暗像素的百分比。（即为频域中的振幅A的强度）



    return 0;
}