
//===============================================================
//FileName:
//          homegraphy.cpp
//Date:
//          2019/11/23
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;


//��ԭͼ�е�Χס�����򸲸ǵ�Ŀ��ͼ�ϡ������ͼ�Ͻ���չʾ
int main7()
{

	//ԭͼ
	Mat im_src = imread("C:/Users/sualab/Desktop/book2.jpg");
	
	//ԭͼ������ĸ���
	vector<Point2f> pts_src;
	pts_src.push_back(Point2f(141, 131));
	pts_src.push_back(Point2f(480, 159));
	pts_src.push_back(Point2f(493, 630));
	pts_src.push_back(Point2f(64, 601));

//------------------------------------------------------------------------

	//Ŀ��ͼ
	Mat im_dst = imread("C:/Users/sualab/Desktop/book1.jpg");

	//Ŀ��ͼ�е��ĸ���
	vector<Point2f> pts_dst;
	pts_dst.push_back(Point2f(318, 256));
	pts_dst.push_back(Point2f(534, 372));
	pts_dst.push_back(Point2f(316, 670));
	pts_dst.push_back(Point2f(73, 473));


//------------------------------------------------------------------------

	//���� ��Ӧ����(homegraphy)
	Mat h = findHomography(pts_src, pts_dst);

//------------------------------------------------------------------------

	//���ͼ
	Mat im_out;
	warpPerspective(im_src, im_out, h, im_dst.size());



//------------------------------------------------------------------------
	imwrite("C:/Users/sualab/Desktop/im_out.jpg",im_out);

	waitKey(0);
	
	




	return 0;
}

