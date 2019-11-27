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
//		cout << "ͼƬ������" << endl;
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
////��ɫת�Ҷȣ���ʵ����ȡ����ͨ�������ص㲻ͬ�����ĺͣ�
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
////ֱ��ͼ���⻯
//Mat HistEq(Mat& srcImage)
//{
//	int rows = srcImage.rows;
//	int cols = srcImage.cols;
//	Mat resultImage(rows, cols, srcImage.type());
//
//	int Hist[256]; //���ÿ�����ظ���---------------------------(px,Px_num)
//	double HistP[256];//���ÿ�����ظ���ռ�����ظ����ı���-------��px,p)
//	double HistPSum[256];//��Ÿ�px֮ǰ���и���֮��--------------(px,sum_pxBeforePoint_p)
//	int EqHist[256];//���һ���任���px��Ӧ��
////------------------------------------------------------------------------
//	//��ʼ��
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
//	//��ÿ�����ص�Ƶ��
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
//	//ÿ�����صĸ���
//	for (i = 0; i < 256; i++)
//	{
//		HistP[i] = (double)Hist[i] / (rows * cols);
//	}
//
////------------------------------------------------------------------------
//
//	//ÿ�����ص��ۼƸ���
//	HistPSum[0] = HistP[0];
//	for (i = 1; i < 256; i++)
//	{
//		HistPSum[i] = HistP[i] + HistPSum[i - 1];
//		//����pxֵΪ128�����ظ�������ֻ��0.01(����ֻ��һ��128������ֵ�����ص�)
//		//��֮ǰ���ۼƸ�����Ӻ�ֵ�����ϲ��䡣��������127���ۼƸ�����ͬ��
//		//����*255�ͻ���127����ֵ
//		//�൱�����ص�����Ƚ��ٵ�ֱ�ӱ������������ص�����Ƚ϶������ֵ
//		//�����ͻ���ʧϸ�ڡ�
//	}
//
////------------------------------------------------------------------------
//
//	//ֱ��ͼ���⻯֮���ֵ
//	for (i = 0; i < 256; i++)
//	{
//		EqHist[i] = cvRound((double)HistPSum[i] * 255);
//	}
//	for (i = 0; i < rows; i++)
//	{
//		for (j = 0; j < cols; j++)
//		{
//			resultImage.at<uchar>(i, j) = EqHist[(int)srcImage.at<uchar>(i, j)];//�Ѷ�Ӧ����ֵ������ԭͼ��
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

    
	// ��1������Դͼ�� 
	Mat srcImage, dstImage;
	srcImage = imread("C:/Users/sualab/Desktop/cow.jpg", 1);
	if (!srcImage.data) { printf("��ȡͼƬ������ȷ��Ŀ¼���Ƿ���imread����ָ��ͼƬ����~�� \n"); return false; }

//------------------------------------------------------------------------
	// ��2��תΪ�Ҷ�ͼ����ʾ����
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	imshow("ԭʼͼ", srcImage);

//------------------------------------------------------------------------
	// ��3������ֱ��ͼ���⻯

	//����1����Ϊ8λ��ͨ����ͼ��
	//����2�����ͼ�񣬺�ԭͼƬ��һ���ĳߴ������
	equalizeHist(srcImage, dstImage);


//------------------------------------------------------------------------

	// ��4����ʾ���
	imshow("����ֱ��ͼ���⻯���ͼ", dstImage);

	// �ȴ��û������˳�����
	waitKey(0);

    return 0;
}



