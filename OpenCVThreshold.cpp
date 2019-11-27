
#include <iostream>
#include <opencv2/opencv.hpp>


int main3()
{

	using namespace cv;
	using namespace std;

	//1.��������ֵ������ = THRESH_BINARY��

	//��ֵ����

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

	//ֻҪͼ������ص����thresh���ͻᱻ��ΪmaxValue
	threshold(src, dst, thresh, maxValue, THRESH_BINARY);

	threshold(src, dst1, 127, maxValue, THRESH_BINARY);

	threshold(src, dst2, thresh, 128, THRESH_BINARY);
	

	//2.����������ֵ������ = THRESH_BINARY_INV��

	//���������ֵ�������������ֵ�����෴��
	//�����Ӧ��Դ���ش�����ֵ����Ŀ����������Ϊ�㣻���Դ����С����ֵ����Ŀ����������ΪmaxValue��

	//��ֵ����

	/*if (src(row, col) > thresh) {
		dst(row, col) = 0;
	}
	else {
		dst(row, col) = maxValue;
	}*/
	//ֻҪ����thresh�ľͻᱻ��Ϊ0,��֮��ΪmaxValue
	threshold(src, dst3, thresh, maxValue, THRESH_BINARY_INV);


	//3.�ض���ֵ������ = THRESH_TRUNC��

	//���Դ����ֵ������ֵ����Ŀ����������Ϊ��ֵ��thresh�� �����򣬽�������ΪԴ����ֵ��maxValue�����ԡ�
	//maxValue�����ԡ�
	//Truncate Threshold
	/*if (src(row, col) > thresh) {
		dst(row, col) = thresh;
	}
	else {
		dst(row, col) = src(row,col);
	}*/

	threshold(src, dst4, 127, maxValue, THRESH_TRUNC);


	//4.��ֵΪ�㣨���� = THRESH_TOZERO��

	//���Դ����ֵ������ֵ����Ŀ������ֵ����Ϊ��Ӧ��Դ����ֵ������������Ϊ�㡣maxValue������
	// Threshold to Zero
	/*if (src(row, col) > thresh) {
		dst(row, col) = src(row,col);
	}
	else {
		dst(row, col) = 0;
	}*/

	threshold(src, dst5, thresh, maxValue, THRESH_TOZERO);




	//5.������ֵΪ�㣨���� = THRESH_TOZERO_INV��

	//����ֵ������ֵ����Ŀ������ֵ����Ϊ�㡣���򣬽�������ΪԴ����ֵ��
	//maxValue������

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

