
//===============================================================
//FileName:
//          CenterOfBlob.cpp
//Date:
//          2019/11/25
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//using namespace std;
//
//int main( int argc, char** argv)
//{
//
//    
//   Mat im_src = imread("C:/Users/sualab/Desktop/circle.png");
//	Mat gray, thr;
//
////------------------------------------------------------------------------
//
//	cvtColor(im_src, gray, COLOR_BGR2GRAY);
//
////------------------------------------------------------------------------
//
//	threshold(gray, thr, 100, 255, THRESH_BINARY);
//
//
////------------------------------------------------------------------------
//
//	//array:�������飬�����ǹ�դͼ��(��ͨ����8-bit�򸡵��Ͷ�ά����),������һ����ά����(1 X N��N X 1),��ά��������ΪPoint��Point2f
//	//binaryImage:Ĭ��ֵ��false�����Ϊtrue�������з�������ض��ᰴֵ1�Դ���Ҳ����˵�൱�ڶ�ͼ������˶�ֵ��������ֵΪ1���˲�������ͼ����Ч��
//	Moments m = moments(thr, true); 
//
//	Point p(m.m10 / m.m00, m.m01 / m.m00); //�õ����ĵ�
//
//	//��������
//	cout << Mat(p) << endl; //Mat
//	
//
//	// show the image with a point mark at the centroid
//	circle(im_src, p, 5, Scalar(128, 0, 0), -1);
//	//imshow("Image with center", im_src);
//	imwrite("C:/Users/sualab/Desktop/circleMark.png", im_src);
//
//    waitKey(0);
//    
//    return 0;
//}



#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void find_moments(Mat gray) {

	Mat canny_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

//------------------------------------------------------------------------

	Canny(gray, canny_output, 50, 150);//�õ����Ƕ�ֵͼ��

//------------------------------------------------------------------------

	// Find contours
	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	

//------------------------------------------------------------------------
	// Get the moments
	vector<Moments> mu(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}


//------------------------------------------------------------------------

	///  Get the centroid of figures.
	vector<Point2f> mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}


//------------------------------------------------------------------------
	 /// Draw contours

	Mat drawing(canny_output.size(), CV_8UC3, Scalar(255, 255, 255));

	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(167, 151, 0);
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 7, 0);
	}

//------------------------------------------------------------------------


	/// Show the resultant image
	namedWindow("Contours", WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
	imwrite("C:/Users/sualab/Desktop/multiple-blobMark.png", drawing);
	waitKey(0);
}




int main20( int argc, char** argv)
{

    
	Mat im_src = imread("C:/Users/sualab/Desktop/multiple-blob.png");
	Mat gray, thr;

//------------------------------------------------------------------------

	cvtColor(im_src, gray, COLOR_BGR2GRAY);

//------------------------------------------------------------------------

	namedWindow("Source", WINDOW_AUTOSIZE);
	imshow("Source", im_src);

	// call function to find_moments
	find_moments(gray);
	
    waitKey(0);
    


    return 0;
}