
#include <iostream>
#include <opencv2/opencv.hpp>


int main5() {

	using namespace cv;
	//using namespace std;
	Mat src = imread("C:/Users/sualab/Desktop/blob_detection.jpgo");

	//�ߵ���ͼ����һ�鹲������أ����Ǿ���һЩ��ͬ�����ԣ�����Ҷ�ֵ����
	//��ɫ���������ǰߵ㣬�ߵ����Ŀ����ʶ�𲢱����Щ����


	

	//���blob
	std::vector<KeyPoint> keypoints;
		//KeyPoint һ��Ϊ����������������ݽṹ����ʾ����������
		

		//KeyPoint תpoint2f
			//KeyPoint::convert(keypoints, point2f, 1, 1, 0, -1);

		//point2f תKeyPoint
			//KeyPoint::convert(point2f, keypoint, 1, 1, 0, -1);


	//ʹ��Ĭ�ϲ������ü����
	//SimpleBlobDetector detector;

	// Setup SimpleBlobDetector parameters.
	SimpleBlobDetector::Params params;

	//��ֵ����
	// Change thresholds
		//ͨ����minThreshold��ʼ����ֵ��Դͼ�������ֵ������Դͼ��ת��Ϊ���������ͼ��  ��
		//��Щ��ֵ��thresholdStep������  ֱ��  maxThreshold��
		//��ˣ���һ����ֵΪ  minThreshold�� 
		//�ڶ�����ֵΪ  minThreshold + thresholdStep���������� ֵΪ  minThreshold + 2 x thresholdStep���������ơ�
	params.minThreshold = 10;
	params.maxThreshold = 200;//��ʾ10���º�200���ϵĲ�������

	//���������С����
	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 100; //��ʾ���˳���������100�����ص�blob

	//Բ��
	// Filter by Circularity
	params.filterByCircularity = true;
	params.minCircularity = 0.1; //Բ��Բ��Ϊ1�������ε�Բ��Ϊ0.785,��������Բ��С��0.1��

	//͹��
	// Filter by Convexity
	params.filterByConvexity = true;
	params.minConvexity = 0.87;//�ߵ�����/͹�������   ���С��1�Ļ�����ʾ�ǰ���,����1��ʾԲ�Σ�����1��͹�͡�

	
	// Filter by Inertia   ���Ժ�����״���쳤�̶�
	params.filterByInertia = true;
	params.minInertiaRatio = 0.01;//����һ��Բ����ֵ��1��������Բ����0��1֮�䣬����������0


	// Set up detector with params
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

	detector->detect(src, keypoints);

	//�ú�ɫȦס����blob
	Mat src_with_keyPoints;
	//����1��ԭͼ��
	//����2���ؼ���
	//����3�����ͼ��
	//����4�������ؼ������ɫ��
	//����5��DrawMatchesFlags::DRAW_RICH_KEYPOINTS ʹԲȦ�Ĵ�С��blob�Ĵ�С���Ӧ
	drawKeypoints(src,keypoints, src_with_keyPoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imwrite("C:/Users/sualab/Desktop/blobed_detection.jpg", src_with_keyPoints);



	return 0;

}