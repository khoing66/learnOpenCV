

#include <iostream>
#include <opencv2/opencv.hpp>




int main6()
{

	using namespace cv;
	using namespace std;
	Mat src = imread("C:/Users/sualab/Desktop/1.png");
	Mat dst = imread("C:/Users/sualab/Desktop/2.png");
	
	if (src.empty() || dst.empty()) {
		cout << "not" << endl;
		return 0;
	}


	/*	��ȡͼ��
		������ת��Ϊ�Ҷȡ�
		ѡ����Ҫ���Ƶ��˶�ģ�͡�
		����ռ䣨warp_matrix���Դ洢�˶�ģ�͡�
		������ֹ��׼������ֹ��׼�����㷨��ʱֹͣ��
		ʹ��findTransformECC����Ť������
		��Ť������Ӧ��������һ��ͼ��ʹ������һ��ͼ����롣*/


	//ѵ��ͼ�Ͳ���ͼ�����е����ҵ����ʵ�Ť������
	//������Ť������ȥ�޸�ѵ��ͼ




	Mat src_gray, dst_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);
	cvtColor(dst, dst_gray, CV_BGR2GRAY);

	//�����˶�ģ��
	const int warp_mode = MOTION_EUCLIDEAN;

	//Set a 2x3 or 3x3 warp matrix(Ť������ depending on the motion model.
	Mat warp_matrix;

	//��ʼ�������Խ���ʶ��

	if (warp_mode == MOTION_HOMOGRAPHY)
		warp_matrix = Mat::eye(3, 3, CV_32F);
	else
		warp_matrix = Mat::eye(2, 3, CV_32F);

	//ָ�������Ĵ���
	int number_of_iterations = 5000;


	//ָ��������ֵ 
	//��������֮������ϵ��
	double termination_eps = 1e-10;


	//������ֹ����
	TermCriteria criteria(TermCriteria::COUNT + TermCriteria::EPS, number_of_iterations, termination_eps);


	//����ECC�㷨������洢��warp_matrix�С�

	findTransformECC(
		src_gray,
		dst_gray,
		warp_matrix,
		warp_mode,
		criteria
	);

	// ����Ť������
	Mat im2_aligned;

	if (warp_mode != MOTION_HOMOGRAPHY)
		// Use warpAffine for Translation, Euclidean and Affine
		warpAffine(dst, im2_aligned, warp_matrix, src.size(), INTER_LINEAR + WARP_INVERSE_MAP);
	else
		// Use warpPerspective for Homography
		warpPerspective(dst, im2_aligned, warp_matrix, src.size(), INTER_LINEAR + WARP_INVERSE_MAP);

	// Show final result
	imshow("Image 1", src);
	imshow("Image 2", dst);
	imshow("Image 2 Aligned", im2_aligned);
	waitKey(0);






	return 0;



}


