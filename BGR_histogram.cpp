
//===============================================================
//FileName:
//          BGR_histogram.cpp
//Date:
//          2019/11/27
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main28(int argc, char** argv)
{

	//��1�������ز�ͼ����ʾ
	Mat srcImage = imread("C:/Users/sualab/Desktop/red.png");
	imshow("�ز�ͼ", srcImage);

	vector<Mat> imgs;
	split(srcImage, imgs);
	Mat b = imgs[0];
	Mat g = imgs[1];
	Mat r = imgs[2];

//------------------------------------------------------------------------

		//��2������׼��
	int bins = 256;
	int hist_size[] = { bins };
	float range[] = { 0, 256 };
	const float* ranges[] = { range };
	MatND redHist, greenHist, blueHist;
	int channels_b[] = { 0 };

//------------------------------------------------------------------------


	//��3������ֱ��ͼ�ļ��㣨��ɫ�������֣�
	calcHist(&srcImage, 1, channels_b, Mat(), //��ʹ����Ĥ
		blueHist, 1, hist_size, ranges,
		true, false);

//------------------------------------------------------------------------

	//��4������ֱ��ͼ�ļ��㣨��ɫ�������֣�
	int channels_g[] = { 1 };
	calcHist(&srcImage, 1, channels_g, Mat(), // do not use mask
		greenHist, 1, hist_size, ranges,
		true, // the histogram is uniform
		false);

//------------------------------------------------------------------------

	//��5������ֱ��ͼ�ļ��㣨��ɫ�������֣�
	int channels_r[] = { 2 };
	calcHist(&srcImage, 1, channels_r, Mat(), // do not use mask
		redHist, 1, hist_size, ranges,
		true, // the histogram is uniform
		false);

//------------------------------------------------------------------------
	////Ҳ����ֱ�ӵõ���ά�����ֱ��ͼ���о���
	//int channels[3];
	//channels[0] = 0;
	//channels[1] = 1;
	//channels[2] = 2;

	//Mat hist;
	//calcHist(&srcImage, 1, channels, Mat(), hist, 3, hist_size, ranges);

//------------------------------------------------------------------------
//����ֱ��ͼ


//------------------------------------------------------------------------

	//����׼��
	double maxValue_red, maxValue_green, maxValue_blue;
	minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
	minMaxLoc(greenHist, 0, &maxValue_green, 0, 0);
	minMaxLoc(redHist, 0, &maxValue_red, 0, 0);

	int scale = 1;
	int histHeight = 256;
	Mat histImage = Mat::zeros(histHeight, bins * 3, CV_8UC3);

//------------------------------------------------------------------------

	//��ʽ��ʼ����
	for (int i = 0; i < bins; i++)
	{	
		//------------------------------------------------------------------------
		
		//����׼��
		float binValue_blue = blueHist.at<float>(i);
		float binValue_green = greenHist.at<float>(i);
		float binValue_red = redHist.at<float>(i);

		int intensity_blue = cvRound((binValue_blue / maxValue_blue) * histHeight);  //Ҫ���Ƶĸ߶�
		int intensity_green = cvRound((binValue_green / maxValue_green) * histHeight );  //Ҫ���Ƶĸ߶�
		int intensity_red = cvRound((binValue_red / maxValue_red) * histHeight);  //Ҫ���Ƶĸ߶�
		
		//------------------------------------------------------------------------
		
		//������ɫ������ֱ��ͼ
		rectangle(histImage, Point(i * scale, histHeight - 1),
			Point((i + 1) * scale - 1, histHeight - intensity_blue),
			Scalar(255, 0, 0));
		
		//------------------------------------------------------------------------
		
		//������ɫ������ֱ��ͼ
		rectangle(histImage, Point((i + bins) * scale, histHeight - 1),
			Point((i + bins + 1) * scale - 1, histHeight - intensity_green),
			Scalar(0, 255, 0));
		
		//------------------------------------------------------------------------
		
		//���ƺ�ɫ������ֱ��ͼ
		rectangle(histImage, Point((i + bins * 2) * scale, histHeight - 1),
			Point((i + bins * 2 + 1) * scale - 1, histHeight - intensity_red),
			Scalar(0, 0, 255));

	}
	
	//------------------------------------------------------------------------
	
	//�ڴ�������ʾ�����ƺõ�ֱ��ͼ
	imshow("ͼ���BGRֱ��ͼ", histImage);
	waitKey(0);


    return 0;
}