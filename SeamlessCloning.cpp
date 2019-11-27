


#include <iostream>
#include <opencv2/opencv.hpp>




int main4()
{

	using namespace cv;
	using namespace std;
	Mat src = imread("C:/Users/sualab/Desktop/airplane.jpg");
	Mat dst = imread("C:/Users/sualab/Desktop/sky.jpg");
	if (src.empty()||dst.empty()) {
		cout << "not" << endl;
		return 0;
	}

	
	//Create a rough mask around the airplane.
	
	Mat src_mask = Mat::zeros(src.rows, src.cols,src.type());//该类型返回3通道的图像
	//Mat src_mask = Mat::zeros(src.rows, src.cols,src.depth());//该类型返回1通道的图像
	//depth 图像元素的位深度，表示每一通道的值
		/*位深度                                                            取值范围

		IPL_DEPTH_8U - 无符号8位整型                                     0--255

		IPL_DEPTH_8S - 有符号8位整型 - 128--127

		IPL_DEPTH_16U - 无符号16位整型                                   0--65535

		IPL_DEPTH_16S - 有符号16位整型 - 32768--32767

		IPL_DEPTH_32S - 有符号32位整型                                    0--65535

		IPL_DEPTH_32F - 单精度浮点数                                     0.0--1.0

		IPL_DEPTH_64F - 双精度浮点数                                      0.0--1.0*/

	
	// Define the mask as a closed polygon
	Point poly[1][7];
	poly[0][0] = Point(4, 80);
	poly[0][1] = Point(30, 54);
	poly[0][2] = Point(151, 63);
	poly[0][3] = Point(254, 37);
	poly[0][4] = Point(298, 90);
	poly[0][5] = Point(272, 134);
	poly[0][6] = Point(43, 122);


	const Point* polygons[1] = { poly[0] };
	int num_points[] = { 7 };

	// Create mask by filling the polygon

	//参数1：多边形将画到此图像上
	//参数2：多边形的顶点集  *polypoints 存储各顶点坐标的数组，每两个一组表示一个顶点的 X 和 Y 坐标
	//参数3：绘制的多边形顶点数目为npt 为数组格式
	//参数4：区域的颜色
	fillPoly(src_mask,polygons, num_points, 1, Scalar(255, 255, 255));

	// 源图像中心在目标图像中的位置
	Point center(800, 100);

	// Seamlessly clone src into dst and put the results in output
	Mat output;
	/*src	将被复制到目标图像的源图像。在我们的示例中是飞机。
	dst		源映像将克隆到的目标映像。在我们的示例中，它是天空图像。
	面具		要克隆的对象周围的粗糙蒙版。这应该是源图像的大小。单通3通都可以
	中央 	源图像中心在目标图像中的位置。
	标志		当前工作的两个标志是NORMAL_CLONE和MIXED_CLONE。我提供了一个例子来说明差异。
	输出		输出 / 结果图像*/
	seamlessClone(src, dst, src_mask, center, output, NORMAL_CLONE);

	Mat output1; //用全白的mask //只对对象标白，表示只关注白色区域
	Mat src_mask1;
	src_mask1 = Mat(src.size(), src.type(), Scalar::all(255));
	seamlessClone(src, dst, src_mask, center, output1, NORMAL_CLONE);






	//NORMAL_CLONE和MIXED_CLONE差异
	Mat srcimg = imread("C:/Users/sualab/Desktop/iloveyouticket.jpg");
	Mat dstimg = imread("C:/Users/sualab/Desktop/wood-texture.jpg");
	if (srcimg.empty() || dstimg.empty()) {
		cout << "not" << endl;
		return 0;
	}
	//Mat src_mask2 = 255 * Mat::ones(srcimg.rows, srcimg.cols, srcimg.depth());
	//Mat src_mask2 = 255 * Mat::ones(srcimg.rows, srcimg.cols, srcimg.depth());
	Mat src_mask2 = Mat(srcimg.size(), srcimg.type(), Scalar::all(255));

	Point center2(dstimg.cols / 2, dstimg.rows / 2);
	Mat normal_clone;
	Mat mixed_clone;

	//过度平滑(可以通过精确的mask改善）
	seamlessClone(srcimg, dstimg, src_mask2, center2, normal_clone, NORMAL_CLONE);
	//纹理不再平滑
	seamlessClone(srcimg, dstimg, src_mask2, center2, mixed_clone, MIXED_CLONE);//这里选用单通道的mask，没有效果。





	waitKey(0);
	return 0;






}

