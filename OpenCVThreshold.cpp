
#include <iostream>
#include <opencv2/opencv.hpp>


int main3()
{

	using namespace cv;
	using namespace std;

	//1.二进制阈值（类型 = THRESH_BINARY）

	//阈值规则

	/*if (src(row, col) > thresh) {
		dst(row, col) = maxValue;
	}
	else {
		dst(row, col) = 0;
	}*/

	Mat src = imread("C:/Users/sualab/Desktop/threshold.png");

	Mat dst,dst1,dst2,dst3,dst4,dst5,dst6;
	
	double thresh = 0;
	double maxValue = 255;

	//只要图像的像素点大于thresh，就会被设为maxValue
	threshold(src, dst, thresh, maxValue, THRESH_BINARY);

	threshold(src, dst1, 127, maxValue, THRESH_BINARY);

	threshold(src, dst2, thresh, 128, THRESH_BINARY);
	

	//2.反二进制阈值（类型 = THRESH_BINARY_INV）

	//逆二进制阈值处理与二进制阈值处理相反。
	//如果相应的源像素大于阈值，则将目标像素设置为零；如果源像素小于阈值，则将目标像素设置为maxValue。

	//阈值规则

	/*if (src(row, col) > thresh) {
		dst(row, col) = 0;
	}
	else {
		dst(row, col) = maxValue;
	}*/
	//只要大于thresh的就会被设为0,反之设为maxValue
	threshold(src, dst3, thresh, maxValue, THRESH_BINARY_INV);


	//3.截断阈值（类型 = THRESH_TRUNC）

	//如果源像素值大于阈值，则将目标像素设置为阈值（thresh） 。否则，将其设置为源像素值。maxValue被忽略。
	//maxValue被忽略。
	//Truncate Threshold
	/*if (src(row, col) > thresh) {
		dst(row, col) = thresh;
	}
	else {
		dst(row, col) = src(row,col);
	}*/

	threshold(src, dst4, 127, maxValue, THRESH_TRUNC);


	//4.阈值为零（类型 = THRESH_TOZERO）

	//如果源像素值大于阈值，则将目标像素值设置为对应的源像素值。否则将其设置为零。maxValue被忽略
	// Threshold to Zero
	/*if (src(row, col) > thresh) {
		dst(row, col) = src(row,col);
	}
	else {
		dst(row, col) = 0;
	}*/

	threshold(src, dst5, thresh, maxValue, THRESH_TOZERO);




	//5.倒置阈值为零（类型 = THRESH_TOZERO_INV）

	//像素值大于阈值，则将目标像素值设置为零。否则，将其设置为源像素值。
	//maxValue被忽略

	/*if (src(row, col) > thresh) {
		dst(row, col) = 0;
	}
	else {
		dst(row, col) = src(row,col);
	}*/

	threshold(src, dst6, 127, maxValue, THRESH_TOZERO_INV);


	

	waitKey(0);
	return 0;






}

