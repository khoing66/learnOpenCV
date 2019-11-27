
//===============================================================
//FileName:
//          clacBackProject.cpp
//Date:
//          2019/11/27
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat g_srcImage; Mat g_hsvImage; Mat g_hueImage;
int g_bins = 30;//ֱ��ͼ���,Խ��������Խ�ࡣ���Ƕ����bin
//------------------------------------------------------------------------

void on_BinChange(int, void*)
{
	//��1������׼��
	MatND hist;
	int histSize = MAX(g_bins, 2);//�ֳɶ��ٸ�bin

	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };

	//��2������ֱ��ͼ����һ��
	calcHist(&g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	//��3�����㷴��ͶӰ
	MatND backproj;

	//����1����������飬���еľ����������ͬ�ĳߴ����ȣ�ͼƬ��
	//����2����һ����������ľ�����������ͼ��ĸ���
	//����3����Ҫͳ�Ƶ�ͨ������ int* 
	//����4�������ֱ��ͼ
	//����5������ķ���ͶӰͼ,Ϊ��ͨ��������ԭͼ����ͬ�Ĵ�С�ͳߴ�
	//����6��ÿһά�����ȡֵ��Χ
	//����7��double scale �������ͶӰ��ѡ���������ӣ�Ĭ��ֵ1
	//����8��ֱ��ͼ�Ƿ���ȵı�ʶ������Ĭ��ֵtrue
	calcBackProject(&g_hueImage, 1, 0, hist, backproj, &ranges, 1, true);

	//------------------------------------------------------------------------

		//��4����ʾ����ͶӰ
	imshow("����ͶӰͼ", backproj);

	//------------------------------------------------------------------------

		//��5������ֱ��ͼ�Ĳ���׼��
	int w = 400; int h = 400;
	int bin_w = cvRound((double)w / histSize);
	Mat histImg = Mat::zeros(w, h, CV_8UC3);

	//------------------------------------------------------------------------

		//��6������ֱ��ͼ
	for (int i = 0; i < g_bins; i++)
	{
		rectangle(histImg, Point(i * bin_w, h), Point((i + 1) * bin_w, h - cvRound(hist.at<float>(i) * h / 255.0)), Scalar(100, 123, 255), -1);
	}

	//------------------------------------------------------------------------

		//��7����ʾֱ��ͼ����
	imshow("ֱ��ͼ", histImg);
}

//------------------------------------------------------------------------

int main31( int argc, char** argv)
{

	//��1����ȡԴͼ�񣬲�ת���� HSV �ռ�
	g_srcImage = imread("C:/Users/sualab/Desktop/cow.jpg", 1);
	if (!g_srcImage.data) { printf("��ȡͼƬ������ȷ��Ŀ¼���Ƿ���imread����ָ��ͼƬ����~�� \n"); return false; }
	cvtColor(g_srcImage, g_hsvImage, COLOR_BGR2HSV);
 
 //------------------------------------------------------------------------
	g_hueImage.create(g_hsvImage.size(), g_hsvImage.depth());
	int ch[] = { 0, 0 };
	//0ͨ�� -- ��  -- 0ͨ��

	//����ͼ��ͨ��
	//����1����������飬���еľ����������ͬ�ĳߴ����ȣ�ͼƬ��
	//����2����һ����������ľ�����������ͼ��ĸ���
	//����3����������飬���еľ����������ͬ�ĳߴ����ȣ�ͼƬ��
	//����4����������������ľ����������ͼ��ĸ���
	mixChannels(&g_hsvImage, 1, &g_hueImage, 1, ch, 1);

/*
//Ӧ��ʵ��(���´�����ʾmixChannels��ʹ�ã�
//------------------------------------------------------------------------
	//��һ��4ͨ����RGBAͼ��ת��Ϊ3ͨ��BGR��һ��������Alphaͨ��
	Mat rgba(100, 100, CV_8UC4, Scalar(1, 2, 3, 4));
	Mat bgr(rgba.rows, rgba.cols, CV_8UC3);
	Mat alpha(rgba.rows, rgba.cols, CV_8UC1);


	Mat out[] = { bgr , alpha };
	//��rgba[0] -->bgr[2] , rgba[1] --> bgr[1]
	//��rgba[2] -->bgr[0] , rgba[3] --> alpha[0]

	int from_to[] = { 0,2, 1,1, 2,0, 3,3 };
	mixChannels(&rgba, 1, out, 2, from_to, 4);
*/
//------------------------------------------------------------------------

	//��3������ Trackbar ������bin����Ŀ
	namedWindow("test", WINDOW_AUTOSIZE);
	createTrackbar("ɫ����� ", "test", &g_bins, 180, on_BinChange);
	on_BinChange(0, 0);//����һ�γ�ʼ��

	//��4����ʾЧ��ͼ
	imshow("test", g_srcImage);

    waitKey(0);
    


    return 0;
}

