
//===============================================================
//FileName:
//          videoRead.cpp
//Date:
//          2019/11/24
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================


#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main15( int argc, char** argv)
{

	// Create a VideoCapture object and open the input file
	// If the input is the web camera, pass 0 instead of the video file name
	VideoCapture cap("C:/Users/sualab/Desktop/chaplin.mp4");
	//VideoCapture cap("F:/a.mp4");
	    
	// Check if camera opened successfully
	if (!cap.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return -1;
	}

//------------------------------------------------------------------------
	//循环显示视频的每一帧
	while (1){
		Mat Frame;

		cap >> Frame;

		if (Frame.empty())
		{
			break;
		}

		imshow("FRAME", Frame);

		// Press  ESC on keyboard to exit
		char c = (char)waitKey(25); //每25毫秒就继续执行 等于每过25毫秒显示下一帧
		if (c == 27)
			break;
	}

	cap.release();

	// Closes all the frames
	destroyAllWindows();




    return 0;
}