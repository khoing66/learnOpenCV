
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main14( int argc, char** argv)
{

    
    Mat im_src1 = imread("C:/Users/sualab/Desktop/foreGroundAssetLarge.png");
	Mat im_src2 = imread("C:/Users/sualab/Desktop/backGroundLarge.jpg");


	Mat out_src;
	addWeighted(im_src1, 0.5, im_src2, 0.5, 0, out_src);


    //Create a window
    namedWindow("Image", 1);

    //show the image
    imshow("Image", out_src);
    waitKey(0);
    


    return 0;
}