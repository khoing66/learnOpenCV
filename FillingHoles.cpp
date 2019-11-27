
//===============================================================
//FileName:
//          FillingHoles.cpp
//Date:
//          2019/11/23
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


//����ͼ��
//��ֵ��ͼ���Ի�ö�����ͼ��(1-->2)
//�����أ�0��0���������(2--3)  (���أ�0,0�����ӵ����������з����������ȡ���������ܷ������Ӱ������ر����ڱ߽��ڣ�
//��ת����ͼ��3-->4)��������ɫ��ɰ�ɫ����ɫ��ɺ�ɫ����
//ʹ�á������㽫��ֵ��ͼ���뵹����䣨4��ͼ����ϣ��Ի�����յ�ǰ���ɰ棬

int main9( int argc, char** argv)
{

    //����ͼ��
	Mat im_in = imread("C:/Users/sualab/Desktop/nickel.jpg", IMREAD_GRAYSCALE);


//------------------------------------------------------------------------

	//��ֵ��
	//���ڻ����220 ��Ϊ0
	//С��220 ��Ϊ255
	Mat im_th;
	threshold(im_in, im_th, 220, 255, THRESH_BINARY_INV);

//------------------------------------------------------------------------
	//��0��0 ��ʼ��ˮ���
	Mat im_floodFill = im_th.clone();
	floodFill(im_floodFill, Point(0, 0), Scalar(255));


//------------------------------------------------------------------------

	//��תͼ��
	Mat im_floodfill_inv;
	bitwise_not(im_floodFill, im_floodfill_inv);

//------------------------------------------------------------------------

	//�� ����
	Mat im_out = (im_th | im_floodfill_inv);

//------------------------------------------------------------------------
	
// Display images
	imshow("Thresholded Image", im_th);
	imshow("Floodfilled Image", im_floodFill);
	imshow("Inverted Floodfilled Image", im_floodfill_inv);
	imshow("Foreground", im_out);
	waitKey(0);
    


    return 0;
}