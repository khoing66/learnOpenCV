
//===============================================================
//FileName:
//          cameraFps (fps).cpp
//Date:
//          2019/11/23
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================


#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main10( int argc, char** argv)
{

    
	// 打开默认的相机
	VideoCapture video(0);

//------------------------------------------------------------------------
	
	//查找连接的摄像头/网络摄像头的帧速率不能直接得到。
	//get（CAP_PROP_FPS）或get（CV_CAP_PROP_FPS）给出每秒的帧数,这对于视频文件是适用的，
	//但对于网络摄像头则不适用。对于网络摄像头和许多其他连接的相机，您必须手动计算每秒的帧数。
	//您可以从视频中读取一定数量的帧，并查看计算每秒帧数所花费的时间。
	double fps = video.get(CAP_PROP_FPS);
	cout << "Frames per second using video.get(CV_CAP_PROP_FPS) : " << fps << endl;

//------------------------------------------------------------------------

	// 设置帧数为120
	int num_frames = 120;

	// Start and end times
	time_t start, end;

	// 存取图像帧的变量Mat
	Mat frame;

	cout << "Capturing " << num_frames << " frames" << endl;

//------------------------------------------------------------------------

	// Start time
	time(&start);

	// Grab a few frames
	for (int i = 0; i < num_frames; i++)
	{
		video >> frame;
	}

	// End Time
	time(&end);

//------------------------------------------------------------------------

	// 时间转换
	double seconds = difftime(end, start);
	cout << "Time taken : " << seconds << " seconds" << endl;

//------------------------------------------------------------------------
	 
	//帧数 除以 显示帧数的时间   得到相机每秒显示多少帧
	fps = num_frames / seconds;
	cout << "Estimated frames per second : " << fps << endl;


	// 关闭相机
	video.release();


    waitKey(0);
    






    return 0;
}