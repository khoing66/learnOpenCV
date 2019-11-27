
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
//记录开始时间
void tic(double& t)
{
	t = (double)getTickCount();
}

//------------------------------------------------------------------------


// toc is called to end timer
//记录结束时间
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
	int numTrials = 5; //遍历全部像素的次数


//------------------------------------------------------------------------
	// Make two copies
	Mat image1 = image.clone();
	Mat image2 = image.clone();
	Mat image3 = image.clone();


//------------------------------------------------------------------------

	//方法1：使用at方法的原始像素访问
	//Mat类具有一种称为的便捷方法，用于访问图像中位置（行，列）的像素。以下代码使用at方法访问每个像素
	//认为是效率低下的，因为每次我们调用at方法时，都会计算内存中像素的位置。这涉及乘法运算


	// Start timer
	double t;
	tic(t);

	for (int n = 0; n < numTrials; n++)
	{
		// Naive pixel access
		//遍历所有像素

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
	//方法2：使用指针算术进行像素访问
	//在OpenCV中，一行中的所有像素都存储在一个连续的内存块中。如果使用create创建 Mat对象，
	//则所有像素都存储在一个连续的内存块中。
	//由于我们正在从磁盘读取图像，并且imread使用create方法，因此我们可以使用不需要乘法的简单指针算法简单地遍历所有像素。


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
	//方法3：使用forEach
	//Mat类的forEach方法采用函数运算符。用法是
	//void cv::Mat::forEach(const Functor & operation)
	//理解上述用法的最简单方法是通过下面显示的示例。我们定义一个与forEach一起使用的函数对象（运算符）。

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

    
	/*	方法类型					时间（毫秒）

		at						6656
		指针						6575
		forEach					1221
		forEach（C++ 11 Lambda）	1272*/



    return 0;
}

