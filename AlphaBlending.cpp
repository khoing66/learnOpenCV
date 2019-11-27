
//===============================================================
//FileName:
//          AlphaBlending.cpp
//Date:
//          2019/11/24
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;



// Alpha blending using multiply and add functions
Mat& blend(Mat& alpha, Mat& foreground, Mat& background, Mat& outImage)
{
	Mat fore, back;
	multiply(alpha, foreground, fore);
	multiply(Scalar::all(1.0) - alpha, background, back);
	add(fore, back, outImage);

	return outImage;
}

//------------------------------------------------------------------------



// ֱ��ʹ��ָ�����Alpha���
Mat& alphaBlendDirectAccess(Mat& alpha, Mat& foreground, Mat& background, Mat& outImage)
{

	int numberOfPixels = foreground.rows * foreground.cols * foreground.channels();


	//ָ��Ĭ��ָ�����ͼ��ĵ�һ������
	float* fptr = reinterpret_cast<float*>(foreground.data);
	float* bptr = reinterpret_cast<float*>(background.data);
	float* aptr = reinterpret_cast<float*>(alpha.data);
	float* outImagePtr = reinterpret_cast<float*>(outImage.data);

	int i, j;
	for (j = 0; j < numberOfPixels; ++j, outImagePtr++, fptr++, aptr++, bptr++)
	{
		*outImagePtr = (*fptr) * (*aptr) + (*bptr) * (1 - *aptr);
	}

	return outImage;
}

//------------------------------------------------------------------------




int main13( int argc, char** argv)
{
	//����ǰ��ͼ
	Mat foreGroundImage = imread("C:/Users/sualab/Desktop/foreGroundAssetLarge.png", IMREAD_UNCHANGED);
	Mat bgra[4];
	split(foreGroundImage, bgra);//��ǰ��ͼ���Ϊ4��ͨ��
	Mat b = bgra[0];
	Mat g = bgra[1];
	Mat r = bgra[2];
	Mat a = bgra[3];

	
//------------------------------------------------------------------------
	
	// Save the foregroung RGB content into a single Mat
	vector<Mat> foregroundChannels;
	foregroundChannels.push_back(bgra[0]);
	foregroundChannels.push_back(bgra[1]);
	foregroundChannels.push_back(bgra[2]);
	Mat foreground = Mat::zeros(foreGroundImage.size(), CV_8UC3);
	merge(foregroundChannels, foreground);//��3��ͨ����ͼ��merge��û��͸����ͨ��


//------------------------------------------------------------------------

	// Save the alpha information into a single Mat
	vector<Mat> alphaChannels;
	alphaChannels.push_back(bgra[3]);
	alphaChannels.push_back(bgra[3]);
	alphaChannels.push_back(bgra[3]);
	Mat alpha = Mat::zeros(foreGroundImage.size(), CV_8UC3);
	merge(alphaChannels, alpha);

//------------------------------------------------------------------------
	// Read background image
	Mat background = imread("C:/Users/sualab/Desktop/backGroundLarge.jpg");

//------------------------------------------------------------------------

	// Convert Mat to float data type
	foreground.convertTo(foreground, CV_32FC3, 1.0 / 255);
	background.convertTo(background, CV_32FC3, 1.0 / 255);
	alpha.convertTo(alpha, CV_32FC3, 1.0 / 255); // keeps the alpha values betwen 0 and 1


//------------------------------------------------------------------------

	// �����Ĵ�����ƽ������
	int numOfIterations = 1; //1000;


	// Alpha��� ʹ�ó˷��ͼӷ�
	Mat outImage = Mat::zeros(foreground.size(), foreground.type());
	
	double t = (double)getTickCount();
	for (int i = 0; i < numOfIterations; i++) {
		outImage = blend(alpha, foreground, background, outImage);
	}
	
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Time for alpha blending using multiply & add function : " << t * 1000 / numOfIterations << " milliseconds" << endl;


//------------------------------------------------------------------------

	// Alpha blending using direct Mat access with for loop
	outImage = Mat::zeros(foreground.size(), foreground.type());
	
	//��ʼʱ��
	t = (double)getTickCount();

	for (int i = 0; i < numOfIterations; i++) {
		outImage = alphaBlendDirectAccess(alpha, foreground, background, outImage);
	}

	//����ʱ��
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Time for alpha blending using alphaBlendDirectAccess : " << t * 1000 / numOfIterations << " milliseconds" << endl;



//------------------------------------------------------------------------

	imshow("alpha blended image", outImage);
	waitKey(0);


//�������ʹ��Сͼ ͼ��ĳ˷��ͼӷ��ٶȿ�Щ
	//����ͼƬ�� ʹ��ָ����������ٶȻ���



    return 0;
}