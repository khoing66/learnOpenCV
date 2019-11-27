//
////===============================================================
////FileName:
////          drawLandmarks.h
////Date:
////          2019/11/24
////Author:
////          khoing(https://blog.csdn.net/qq_45391763)
////===============================================================
//
//
//#ifndef _renderFace_H_
//#define _renderFace_H_
//#define COLOR Scalar(255, 200,0)
//
//#include "opencv2/opencv.hpp"
//
//
////------------------------------------------------------------------------
//
//using namespace std;
//using namespace cv;
//
//
////------------------------------------------------------------------------
//
////���ƶ���������������Ŀ�ʼ�ͽ����ĵ�
//
//void drawPolyline(Mat& im, const vector<Point2f>& landmarks, const int start, const int end, bool isClosed = false) {
//
//	vector <Point> points; //�����п�ʼ�ĵ㵽�����㶼����һ��
//	for (int i = start; i <= end; i++) {
//		points.push_back(Point(landmarks[i].x, landmarks[i].y));
//	}
//
//	polylines(im, points, isClosed, COLOR, 2, 16);
//}
//
//
//
//
////------------------------------------------------------------------------
//
//void drawLandmarks(Mat& im, vector<Point2f>& landmarks)
//{
//	// Draw face for the 68-point model.
//	if (landmarks.size() == 68)
//	{
//		drawPolyline(im, landmarks, 0, 16);           // Jaw line
//		drawPolyline(im, landmarks, 17, 21);          // Left eyebrow
//		drawPolyline(im, landmarks, 22, 26);          // Right eyebrow
//		drawPolyline(im, landmarks, 27, 30);          // Nose bridge
//		drawPolyline(im, landmarks, 30, 35, true);    // Lower nose
//		drawPolyline(im, landmarks, 36, 41, true);    // Left eye
//		drawPolyline(im, landmarks, 42, 47, true);    // Right Eye
//		drawPolyline(im, landmarks, 48, 59, true);    // Outer lip
//		drawPolyline(im, landmarks, 60, 67, true);    // Inner lip
//	}
//	else
//	{ 
//		//�����������68
//		//���ǲ�֪�����ĸ��������Щ�沿������
//		//����,����ÿ��landamrk����һ���㡣
//		for (int i = 0; i < landmarks.size(); i++)
//		{
//			circle(im, landmarks[i], 3, COLOR, FILLED);
//		}
//	}
//
//}
//
//	
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//#endif

