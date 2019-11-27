
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

	//��1������Դͼ��ת��ΪHSV��ɫģ��
	Mat hsvImage;
    Mat srcImage = imread("C:/Users/sualab/Desktop/1.jpg");
	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);

//------------------------------------------------------------------------
	//��2������׼��
	//��ɫ������Ϊ30���ȼ��������Ͷ�����Ϊ32���ȼ�
	int hueBinNum = 30;//ɫ����ֱ��ͼֱ������
	int saturationBinNum = 32;//���Ͷȵ�ֱ��ͼֱ������
	int histSize[] = { hueBinNum, saturationBinNum };
	
	// ����ɫ���ı仯��ΧΪ0��179
	float hueRanges[] = { 0, 180 };

	//���履�Ͷȵı仯��ΧΪ0���ڡ��ס��ң���255����������ɫ��
	float saturationRanges[] = { 0, 256 };

	const float* ranges[] = { hueRanges, saturationRanges };

	MatND dstHist;//��ά����
	
	//����׼����calcHist�����н������0ͨ���͵�1ͨ����ֱ��ͼ
	int channels[] = { 0, 1 };

//------------------------------------------------------------------------

	//��3����ʽ����calcHist������ֱ��ͼ����
	//����1��const Mat* ���͵�images, ��ҪͼƬ����ͬ����ȣ�
	//����2��int  ͼƬ����Ŀ
	//����3��ͨ������  �����飬�������ͨ�������������磺int channels[] = { 0, 1 };��
	//����4: mask,Ҫͳ��ͼ��ĳ���ֲ������ֱ��ͼֻ��Ҫ����һ����ģͼ�� ������Ϊ8λ��������image[i]��ͬ����С�ĳߴ硣��Ҫͳ�ƵĲ������óɰ�ɫ�����ಿ��Ϊ��ɫ���͹�����һ����ģͼ��Ȼ��������ģͼ�񴫸������Ϳ����ˡ�
	//����5�������ֱ��ͼ��һ����ά����
	//����6��int ֱ��ͼ��ά�ȣ�������������
	//����7��const int*   ���ÿ��ά��ֱ��ͼ�ߴ������(��������ֱ����
	//����8��const float**ÿһά��ֵ��ȡֵ��Χ����  ranges[] = {  { 0, 180 }, { 0, 256 } };
	//����9��bool���͵�uniform��ָʾֱ��ͼ�Ƿ���ȵı�ʶ����Ĭ��true
	//����10���ۼƱ�ʶ����false��ʾֱ��ͼ�����ý׶ϻᱻ����

	calcHist(&hsvImage, 1, channels, Mat(), dstHist, 2, histSize, ranges, true, false);

//------------------------------------------------------------------------
	
	//��4��Ϊ����ֱ��ͼ׼������
	double maxValue = 0;//���ֵ

	//����1������ĵ�ͨ�����У�һ����ά����
	//����2��double* ���͵�minVal ������Сֵ��ָ�룬���践����ΪNull
	//����3��double* ���͵�maxVal �������ֵ��ָ�룬���践����ΪNull
	//����4: Point* ���͵�minLoc ������Сλ�õ�ָ�루��ά����£������践����ΪNull
	//����5��Point* ���͵�maxLoc �������λ�õ�ָ�루��ά����£������践����ΪNull
	//����6��InputArray ���͵�mask������ѡ�������еĿ�ѡ��Ĥ
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);//����������������ȫ�����ֵ����maxValue��

	int scale = 10;//sacleΪһ��bin,����(0,10]Ϊһ��bin
	Mat histImg = Mat::zeros(saturationBinNum * scale, hueBinNum * 10, CV_8UC3);


//------------------------------------------------------------------------

	//��5��˫��ѭ��������ֱ��ͼ����
	for (int hue = 0; hue < hueBinNum; hue++)
		for (int saturation = 0; saturation < saturationBinNum; saturation++)
		{
			float binValue = dstHist.at<float>(hue, saturation);//ֱ��ͼ����ֵ
			int intensity = cvRound(binValue / maxValue * 255);//ǿ�� //255Ϊ���ֵ��Ӧ��������ֵ

			//��ʽ���л���
			rectangle(histImg, Point(hue * scale, saturation * scale),
				Point((hue + 1) * scale - 1, (saturation + 1) * scale - 1),
				Scalar::all(intensity), FILLED);
		}

//------------------------------------------------------------------------

	//��6����ʾЧ��ͼ
	imshow("�ز�ͼ", srcImage);
	imshow("H-S ֱ��ͼ", histImg);

	waitKey();

 

    return 0;
}