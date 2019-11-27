
//===============================================================
//FileName:
//          warpTriangle.cpp
//Date:
//          2019/11/24
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


//warpAffine允许您将仿射变换应用于图像，但不能对图像内部的三角形区域应用仿射变换。
//为了克服此限制，我们在源三角形周围找到一个边界框，并从源图像中裁剪出矩形区域。
//通过用白色填充输出三角形内的像素来创建三角形mask。
//将mask与输出图像相乘时，会将三角形外部的所有像素变为黑色，同时保留三角形内部的所有像素的颜色。


int main12( int argc, char** argv)
{

    //读入图像，转换为float类型
    Mat imgIn = imread("C:/Users/sualab/Desktop/robot.jpg");
	imgIn.convertTo(imgIn, CV_32FC3, 1 / 255.0); //0`255 ==> 0`1  1对应255.0

//------------------------------------------------------------------------
	// 输出图像(白色图像）
	Mat imgOut = Mat::ones(imgIn.size(), imgIn.type());
	imgOut = Scalar(1.0, 1.0, 1.0);

//------------------------------------------------------------------------
	// 输入三角形的三个点
	vector <Point2f> triIn;
	triIn.push_back(Point2f(360, 200));
	triIn.push_back(Point2d(60, 250));
	triIn.push_back(Point2f(450, 400));

//------------------------------------------------------------------------
	// 输出三角形的三个点
	vector <Point2f> triOut;
	triOut.push_back(Point2f(400, 200));
	triOut.push_back(Point2f(160, 270));
	triOut.push_back(Point2f(400, 400));

//------------------------------------------------------------------------
	
	//计算边界框  （对图像的一小部分进行仿射变换）
	//在源三角形周围找到一个边界框，并从源图像中裁剪出矩形区域
	Rect r1 = boundingRect(triIn);
	Rect r2 = boundingRect(triOut);

//------------------------------------------------------------------------

	//裁剪图像并更改坐标
	// 我们根据上一步中计算出的边界框来裁剪输入图像。
	//三角形的坐标也需要修改，以反映它们在新裁剪图像中的位置。这是通过从三角形的x和y坐标中减去边界框左上角的x和y坐标来完成的。
	vector<Point2f> triInCropped, triOutCropped;
	vector<Point> triOutCroppedInt;

	for (int i = 0; i < 3; i++)
	{
		triInCropped.push_back(Point2f(triIn[i].x - r1.x, triIn[i].y - r1.y));
		triOutCropped.push_back(Point2f(triOut[i].x - r2.x, triOut[i].y - r2.y));

		// 最后的fillConvexPoly 需要int型，不是float型
		triOutCroppedInt.push_back(Point((int)(triOut[i].x - r2.x), (int)(triOut[i].y - r2.y)));
	}


	Mat imgInCropped;
	imgIn(r1).copyTo(imgInCropped);

//------------------------------------------------------------------------
	//估计仿射变换：我们刚刚获得了裁剪后的输入和输出图像中输入和输出三角形的坐标。
	//用这两个三角形，我们可以找到仿射变换，可以使用以下代码在裁剪后的图像中将输入三角形转换为输出三角形。
	
	Mat warpMat = getAffineTransform(triInCropped, triOutCropped);

//------------------------------------------------------------------------
	//边界框内的扭曲像素将上一步中找到的仿射变换应用于裁剪后的输入图像，以获得裁剪后的输出图像。
	//在OpenCV中，您可以使用warpAffine将仿射变换应用于图像。

	
	Mat imgOutCropped = Mat::zeros(r2.height, r2.width, imgInCropped.type());
	warpAffine(imgInCropped, imgOutCropped, warpMat, imgOutCropped.size(), INTER_LINEAR, BORDER_REFLECT_101);

//------------------------------------------------------------------------
	//遮罩三角形外部的像素
	//在上一步中，我们获得了输出矩形图像。但是，我们对矩形区域内的三角形感兴趣。
	//因此，我们使用fillConvexPoly创建了一个mask，
	//该mask用于涂黑三角形之外的所有像素。
	//最后，可以使用输出边界矩形的左上角将此新裁剪的图像放置在输出图像中的正确位置。

	// Get mask by filling triangle
	Mat mask = Mat::zeros(r2.height, r2.width, CV_32FC3);
	fillConvexPoly(mask, triOutCroppedInt, Scalar(1.0, 1.0, 1.0),16, 0);//把三个点围成的区域用黑色填充

	
	multiply(imgOutCropped, mask, imgOutCropped);
	multiply(imgOut(r2), Scalar(1.0, 1.0, 1.0) - mask, imgOut(r2)); //Scalar(1.0, 1.0, 1.0) - mask 相当于把图像颜色反转
	imgOut(r2) = imgOut(r2) + imgOutCropped;





   
    waitKey(0);
    


    return 0;
}