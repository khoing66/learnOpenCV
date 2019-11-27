
#include <iostream>
#include <opencv2/opencv.hpp>


int main5() {

	using namespace cv;
	//using namespace std;
	Mat src = imread("C:/Users/sualab/Desktop/blob_detection.jpgo");

	//斑点是图像中一组共享的像素，它们具有一些共同的属性（例如灰度值）。
	//深色连接区域是斑点，斑点检测的目的是识别并标记这些区域。


	

	//检测blob
	std::vector<KeyPoint> keypoints;
		//KeyPoint 一个为特征点检测而生的数据结构，表示用于特征点
		

		//KeyPoint 转point2f
			//KeyPoint::convert(keypoints, point2f, 1, 1, 0, -1);

		//point2f 转KeyPoint
			//KeyPoint::convert(point2f, keypoint, 1, 1, 0, -1);


	//使用默认参数设置检测器
	//SimpleBlobDetector detector;

	// Setup SimpleBlobDetector parameters.
	SimpleBlobDetector::Params params;

	//阈值控制
	// Change thresholds
		//通过以minThreshold开始的阈值对源图像进行阈值处理，将源图像转换为多个二进制图像  。
		//这些阈值以thresholdStep递增，  直到  maxThreshold。
		//因此，第一个阈值为  minThreshold， 
		//第二个阈值为  minThreshold + thresholdStep，第三个阈 值为  minThreshold + 2 x thresholdStep，依此类推。
	params.minThreshold = 10;
	params.maxThreshold = 200;//表示10以下和200以上的不做处理

	//像素面积大小控制
	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 100; //表示将滤除所有少于100个像素的blob

	//圆度
	// Filter by Circularity
	params.filterByCircularity = true;
	params.minCircularity = 0.1; //圆的圆度为1，正方形的圆度为0.785,过滤所有圆度小于0.1的

	//凸性
	// Filter by Convexity
	params.filterByConvexity = true;
	params.minConvexity = 0.87;//斑点的面积/凸包的面积   如果小于1的话，表示是凹型,等于1表示圆形，大于1是凸型。

	
	// Filter by Inertia   可以衡量形状的伸长程度
	params.filterByInertia = true;
	params.minInertiaRatio = 0.01;//对于一个圆，该值是1，对于椭圆它是0和1之间，而对于线是0


	// Set up detector with params
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

	detector->detect(src, keypoints);

	//用红色圈住检测的blob
	Mat src_with_keyPoints;
	//参数1：原图像
	//参数2：关键点
	//参数3：输出图像
	//参数4：画出关键点的颜色，
	//参数5：DrawMatchesFlags::DRAW_RICH_KEYPOINTS 使圆圈的大小和blob的大小相对应
	drawKeypoints(src,keypoints, src_with_keyPoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imwrite("C:/Users/sualab/Desktop/blobed_detection.jpg", src_with_keyPoints);



	return 0;

}