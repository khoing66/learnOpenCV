

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


	/*	读取图像。
		将它们转换为灰度。
		选择您要估计的运动模型。
		分配空间（warp_matrix）以存储运动模型。
		定义终止标准，该终止标准告诉算法何时停止。
		使用findTransformECC估计扭曲矩阵。
		将扭曲矩阵应用于其中一个图像，使其与另一个图像对齐。*/


	//训练图和测试图，进行迭代找到合适的扭曲矩阵。
	//用生成扭曲矩阵去修复训练图




	Mat src_gray, dst_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);
	cvtColor(dst, dst_gray, CV_BGR2GRAY);

	//定义运动模型
	const int warp_mode = MOTION_EUCLIDEAN;

	//Set a 2x3 or 3x3 warp matrix(扭曲矩阵） depending on the motion model.
	Mat warp_matrix;

	//初始化矩阵以进行识别

	if (warp_mode == MOTION_HOMOGRAPHY)
		warp_matrix = Mat::eye(3, 3, CV_32F);
	else
		warp_matrix = Mat::eye(2, 3, CV_32F);

	//指定迭代的次数
	int number_of_iterations = 5000;


	//指定增量阈值 
	//两个迭代之间的相关系数
	double termination_eps = 1e-10;


	//定义终止条件
	TermCriteria criteria(TermCriteria::COUNT + TermCriteria::EPS, number_of_iterations, termination_eps);


	//运行ECC算法。结果存储在warp_matrix中。

	findTransformECC(
		src_gray,
		dst_gray,
		warp_matrix,
		warp_mode,
		criteria
	);

	// 保存扭曲矩阵
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


