
//===============================================================
//FileName:
//          matchTemplate.cpp
//Date:
//          2019/11/27
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>
#define WINDOW_NAME1 "��ԭʼͼƬ��"        //Ϊ���ڱ��ⶨ��ĺ� 
#define WINDOW_NAME2 "��ƥ�䴰�ڡ�"        //Ϊ���ڱ��ⶨ��ĺ� \

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
	//��1�����ֲ�������ʼ��
	Mat srcImage;
	g_srcImage_.copyTo(srcImage);

//------------------------------------------------------------------------

	//��2����ʼ�����ڽ������ľ���
	int resultImage_rows = g_srcImage_.rows - g_templateImage.rows + 1;
	int resultImage_cols = g_srcImage_.cols - g_templateImage.cols + 1;
	g_resultImage.create(resultImage_rows, resultImage_cols, CV_32FC1);

//------------------------------------------------------------------------

	//��3������ƥ��ͱ�׼��
	//����1����������ͼ��8λ��32λ
	//����2��ģ�壬���ԭͼƬ����һ�����������ͣ��ҳߴ粻�ܴ���ԭͼ��
	//����3���ȽϽ����ӳ��ͼ�񡣵�ͨ����32λ������ͼ��
			//ͼ��ߴ�ʱW*H��template�ߴ�ʱw*h
			//�˲���		---->	resultΪ(W-w+1)*(H-h+1)
	//����4��ƥ�䷽��
	matchTemplate(g_srcImage_, g_templateImage, g_resultImage, g_nMatchMethod);
	normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());

//------------------------------------------------------------------------

	//��4��ͨ������ minMaxLoc ��λ��ƥ���λ��
	double minValue; double maxValue; Point minLocation; Point maxLocation;
	Point matchLocation;
	minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());

//------------------------------------------------------------------------

	//��5�����ڷ��� SQDIFF �� SQDIFF_NORMED, ԽС����ֵ���Ÿ��ߵ�ƥ����. ������ķ���, ��ֵԽ��ƥ��Ч��Խ��

	if (g_nMatchMethod == TM_SQDIFF || g_nMatchMethod == TM_SQDIFF_NORMED)
	{
		matchLocation = minLocation;
	}
	else
	{
		matchLocation = maxLocation;
	}

	//��6�����Ƴ����Σ�����ʾ���ս��
	rectangle(srcImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows), Scalar(0, 0, 255), 2, 8, 0);
	rectangle(g_resultImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows), Scalar(0, 0, 255), 2, 8, 0);

	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, g_resultImage);

}

//------------------------------------------------------------------------

int main( int argc, char** argv)
{

	//��1������ԭͼ���ģ���
	g_srcImage_ = imread("C:/Users/sualab/Desktop/1.jpg", 1);
	g_templateImage = imread("C:/Users/sualab/Desktop/2.jpg", 1);

//------------------------------------------------------------------------

	//��2����������
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);

//------------------------------------------------------------------------
	//��3������������������һ�γ�ʼ��
	createTrackbar("����", WINDOW_NAME1,&g_nMatchMethod, g_nMaxTrackbarNum, on_Matching);
	on_Matching(0, 0);

//------------------------------------------------------------------------


    waitKey(0);
    
    return 0;
}