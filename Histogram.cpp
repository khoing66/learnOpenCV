
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

	//��1������ԭͼ����ʾ
	Mat srcImage = imread("C:/Users/sualab/Desktop/1.jpg", IMREAD_GRAYSCALE);
	imshow("ԭͼ", srcImage);
	if (!srcImage.data) { cout << "fail to load image" << endl; 	return 0; }

//------------------------------------------------------------------------

	//��2���������
	MatND dstHist;       
	int dims = 1;
	float hranges[] = { 0, 255 };
	const float* ranges[] = { hranges };   // ������ҪΪconst����
	int size = 256;
	int channels = 0;

//------------------------------------------------------------------------


	//��3������ͼ���ֱ��ͼ
	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);    

//------------------------------------------------------------------------

	int scale = 1;

	Mat dstImage(size * scale, size, CV_8U, Scalar(0));


	//��4����ȡ���ֵ����Сֵ
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);  

//------------------------------------------------------------------------

	//��5�����Ƴ�ֱ��ͼ
	int hpt = saturate_cast<int>(0.9 * size);//����ѡ��ͼ�ߵ�90%��Ϊֱ��ͼ�����ֵ
	for (int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i);         
		int realValue = saturate_cast<int>((binValue / maxValue) * hpt);
		rectangle(dstImage, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realValue), Scalar(255));
	}
	imshow("һάֱ��ͼ", dstImage);
	waitKey(0);
	return 0;
}