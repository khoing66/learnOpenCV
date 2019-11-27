
//===============================================================
//FileName:
//          ParallelPixelAccess.cpp
//Date:
//          2019/11/24
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


//------------------------------------------------------------------------

// Define a pixel
typedef Point3_<uint8_t> Pixel;

//------------------------------------------------------------------------


// tic is called to start timer
//��¼��ʼʱ��
void tic(double& t)
{
	t = (double)getTickCount();
}

//------------------------------------------------------------------------


// toc is called to end timer
//��¼����ʱ��
double toc(double& t)
{
	return ((double)getTickCount() - t) / getTickFrequency();
}

//------------------------------------------------------------------------


void complicatedThreshold(Pixel& pixel)
{
	if (pow(double(pixel.x) / 10, 2.5) > 100)
	{
		pixel.x = 255;
		pixel.y = 255;
		pixel.z = 255;
	}
	else
	{
		pixel.x = 0;
		pixel.y = 0;
		pixel.z = 0;
	}
}

//------------------------------------------------------------------------

// Parallel execution with function object.
struct Operator
{
	void operator ()(Pixel& pixel, const int* position) const
	{
		// Perform a simple threshold operation
		complicatedThreshold(pixel);
	}
};



//------------------------------------------------------------------------

int main16( int argc, char** argv)
{

    
    Mat image = imread("C:/Users/sualab/Desktop/butterfly.jpg");


//------------------------------------------------------------------------

	//Scale image 30
	resize(image, image, Size(), 30, 30);
	
//------------------------------------------------------------------------

	// Print image size
	cout << "Image size " << image.size() << endl;

//------------------------------------------------------------------------

	// Number of trials
	int numTrials = 5; //����ȫ�����صĴ���


//------------------------------------------------------------------------
	// Make two copies
	Mat image1 = image.clone();
	Mat image2 = image.clone();
	Mat image3 = image.clone();


//------------------------------------------------------------------------

	//����1��ʹ��at������ԭʼ���ط���
	//Mat�����һ�ֳ�Ϊ�ı�ݷ��������ڷ���ͼ����λ�ã��У��У������ء����´���ʹ��at��������ÿ������
	//��Ϊ��Ч�ʵ��µģ���Ϊÿ�����ǵ���at����ʱ����������ڴ������ص�λ�á����漰�˷�����


	// Start timer
	double t;
	tic(t);

	for (int n = 0; n < numTrials; n++)
	{
		// Naive pixel access
		//������������

		// Loop over all rows
		for (int r = 0; r < image.rows; r++)
		{
			// Loop over all columns
			for (int c = 0; c < image.cols; c++)
			{
				// Obtain pixel at (r, c)
				Pixel pixel = image.at<Pixel>(r, c);
				// Apply complicatedTreshold
				complicatedThreshold(pixel);
				// Put result back
				image.at<Pixel>(r, c) = pixel;
			}

		}
	}

	cout << "Naive way: " << toc(t) << endl;

//------------------------------------------------------------------------
	//����2��ʹ��ָ�������������ط���
	//��OpenCV�У�һ���е��������ض��洢��һ���������ڴ���С����ʹ��create���� Mat����
	//���������ض��洢��һ���������ڴ���С�
	//�����������ڴӴ��̶�ȡͼ�񣬲���imreadʹ��create������������ǿ���ʹ�ò���Ҫ�˷��ļ�ָ���㷨�򵥵ر����������ء�


	// Start timer
	tic(t);

	// image1 is guaranteed to be continous, but
	// if you are curious uncomment the line below
	// cout << "Image 1 is continous : " << image1.isContinuous() << endl;

	for (int n = 0; n < numTrials; n++)
	{
		// Get pointer to first pixel
		Pixel* pixel = image1.ptr<Pixel>(0, 0);

		// Mat objects created using the create method are stored
		// in one continous memory block.
		const Pixel* endPixel = pixel + image1.cols * image1.rows;

		// Loop over all pixels
		for (; pixel != endPixel; pixel++)
		{
			complicatedThreshold(*pixel);
		}


	}
	cout << "Pointer Arithmetic " << toc(t) << endl;
	tic(t);

//------------------------------------------------------------------------
	//����3��ʹ��forEach
	//Mat���forEach�������ú�����������÷���
	//void cv::Mat::forEach(const Functor & operation)
	//��������÷�����򵥷�����ͨ��������ʾ��ʾ�������Ƕ���һ����forEachһ��ʹ�õĺ����������������

	tic(t);

	for (int n = 0; n < numTrials; n++)
	{
		image2.forEach<Pixel>(Operator());
	}
	cout << "forEach : " << toc(t) << endl;

//------------------------------------------------------------------------


#if __cplusplus >= 201103L || (__cplusplus < 200000 && __cplusplus > 199711L)
	tic(t);

	for (int n = 0; n < numTrials; n++)
	{
		// Parallel execution using C++11 lambda.
		image3.forEach<Pixel>
			(
				[](Pixel& pixel, const int* position) -> void
				{
					complicatedThreshold(pixel);
				}
		);
	}
	cout << "forEach C++11 : " << toc(t) << endl;

#endif

    
	/*	��������					ʱ�䣨���룩

		at						6656
		ָ��						6575
		forEach					1221
		forEach��C++ 11 Lambda��	1272*/



    return 0;
}

