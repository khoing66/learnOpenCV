
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

    
	// ��Ĭ�ϵ����
	VideoCapture video(0);

//------------------------------------------------------------------------
	
	//�������ӵ�����ͷ/��������ͷ��֡���ʲ���ֱ�ӵõ���
	//get��CAP_PROP_FPS����get��CV_CAP_PROP_FPS������ÿ���֡��,�������Ƶ�ļ������õģ�
	//��������������ͷ�����á�������������ͷ������������ӵ�������������ֶ�����ÿ���֡����
	//�����Դ���Ƶ�ж�ȡһ��������֡�����鿴����ÿ��֡�������ѵ�ʱ�䡣
	double fps = video.get(CAP_PROP_FPS);
	cout << "Frames per second using video.get(CV_CAP_PROP_FPS) : " << fps << endl;

//------------------------------------------------------------------------

	// ����֡��Ϊ120
	int num_frames = 120;

	// Start and end times
	time_t start, end;

	// ��ȡͼ��֡�ı���Mat
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

	// ʱ��ת��
	double seconds = difftime(end, start);
	cout << "Time taken : " << seconds << " seconds" << endl;

//------------------------------------------------------------------------
	 
	//֡�� ���� ��ʾ֡����ʱ��   �õ����ÿ����ʾ����֡
	fps = num_frames / seconds;
	cout << "Estimated frames per second : " << fps << endl;


	// �ر����
	video.release();


    waitKey(0);
    






    return 0;
}