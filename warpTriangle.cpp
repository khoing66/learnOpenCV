
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


//warpAffine������������任Ӧ����ͼ�񣬵����ܶ�ͼ���ڲ�������������Ӧ�÷���任��
//Ϊ�˿˷������ƣ�������Դ��������Χ�ҵ�һ���߽�򣬲���Դͼ���вü�����������
//ͨ���ð�ɫ�������������ڵ�����������������mask��
//��mask�����ͼ�����ʱ���Ὣ�������ⲿ���������ر�Ϊ��ɫ��ͬʱ�����������ڲ����������ص���ɫ��


int main12( int argc, char** argv)
{

    //����ͼ��ת��Ϊfloat����
    Mat imgIn = imread("C:/Users/sualab/Desktop/robot.jpg");
	imgIn.convertTo(imgIn, CV_32FC3, 1 / 255.0); //0`255 ==> 0`1  1��Ӧ255.0

//------------------------------------------------------------------------
	// ���ͼ��(��ɫͼ��
	Mat imgOut = Mat::ones(imgIn.size(), imgIn.type());
	imgOut = Scalar(1.0, 1.0, 1.0);

//------------------------------------------------------------------------
	// ���������ε�������
	vector <Point2f> triIn;
	triIn.push_back(Point2f(360, 200));
	triIn.push_back(Point2d(60, 250));
	triIn.push_back(Point2f(450, 400));

//------------------------------------------------------------------------
	// ��������ε�������
	vector <Point2f> triOut;
	triOut.push_back(Point2f(400, 200));
	triOut.push_back(Point2f(160, 270));
	triOut.push_back(Point2f(400, 400));

//------------------------------------------------------------------------
	
	//����߽��  ����ͼ���һС���ֽ��з���任��
	//��Դ��������Χ�ҵ�һ���߽�򣬲���Դͼ���вü�����������
	Rect r1 = boundingRect(triIn);
	Rect r2 = boundingRect(triOut);

//------------------------------------------------------------------------

	//�ü�ͼ�񲢸�������
	// ���Ǹ�����һ���м�����ı߽�����ü�����ͼ��
	//�����ε�����Ҳ��Ҫ�޸ģ��Է�ӳ�������²ü�ͼ���е�λ�á�����ͨ���������ε�x��y�����м�ȥ�߽�����Ͻǵ�x��y��������ɵġ�
	vector<Point2f> triInCropped, triOutCropped;
	vector<Point> triOutCroppedInt;

	for (int i = 0; i < 3; i++)
	{
		triInCropped.push_back(Point2f(triIn[i].x - r1.x, triIn[i].y - r1.y));
		triOutCropped.push_back(Point2f(triOut[i].x - r2.x, triOut[i].y - r2.y));

		// ����fillConvexPoly ��Ҫint�ͣ�����float��
		triOutCroppedInt.push_back(Point((int)(triOut[i].x - r2.x), (int)(triOut[i].y - r2.y)));
	}


	Mat imgInCropped;
	imgIn(r1).copyTo(imgInCropped);

//------------------------------------------------------------------------
	//���Ʒ���任�����Ǹոջ���˲ü������������ͼ�����������������ε����ꡣ
	//�������������Σ����ǿ����ҵ�����任������ʹ�����´����ڲü����ͼ���н�����������ת��Ϊ��������Ρ�
	
	Mat warpMat = getAffineTransform(triInCropped, triOutCropped);

//------------------------------------------------------------------------
	//�߽���ڵ�Ť�����ؽ���һ�����ҵ��ķ���任Ӧ���ڲü��������ͼ���Ի�òü�������ͼ��
	//��OpenCV�У�������ʹ��warpAffine������任Ӧ����ͼ��

	
	Mat imgOutCropped = Mat::zeros(r2.height, r2.width, imgInCropped.type());
	warpAffine(imgInCropped, imgOutCropped, warpMat, imgOutCropped.size(), INTER_LINEAR, BORDER_REFLECT_101);

//------------------------------------------------------------------------
	//�����������ⲿ������
	//����һ���У����ǻ�����������ͼ�񡣵��ǣ����ǶԾ��������ڵ������θ���Ȥ��
	//��ˣ�����ʹ��fillConvexPoly������һ��mask��
	//��mask����Ϳ��������֮����������ء�
	//��󣬿���ʹ������߽���ε����Ͻǽ����²ü���ͼ����������ͼ���е���ȷλ�á�

	// Get mask by filling triangle
	Mat mask = Mat::zeros(r2.height, r2.width, CV_32FC3);
	fillConvexPoly(mask, triOutCroppedInt, Scalar(1.0, 1.0, 1.0),16, 0);//��������Χ�ɵ������ú�ɫ���

	
	multiply(imgOutCropped, mask, imgOutCropped);
	multiply(imgOut(r2), Scalar(1.0, 1.0, 1.0) - mask, imgOut(r2)); //Scalar(1.0, 1.0, 1.0) - mask �൱�ڰ�ͼ����ɫ��ת
	imgOut(r2) = imgOut(r2) + imgOutCropped;





   
    waitKey(0);
    


    return 0;
}