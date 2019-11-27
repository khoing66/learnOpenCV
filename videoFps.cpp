
//===============================================================
//FileName:
//          videoFps.cpp
//Date:
//          2019/11/23
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================


//查找视频的FPS

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main11( int argc, char** argv)
{

    
	//打开视频文件
	VideoCapture video("H:/2020/11.1.mp4");
	if (!video.isOpened()) {
		cout << "Video Not Found!!!" << endl;
		return 0;
	}



	double fps = video.get(CAP_PROP_FPS);

	cout << "Frames per second using video.get(CV_CAP_PROP_FPS) : " << fps << endl;

	video.release();
	return 0;
}