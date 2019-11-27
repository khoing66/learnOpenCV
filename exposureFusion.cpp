
//===============================================================
//FileName:
//          exposureFusion.cpp
//Date:
//          2019/11/25
//Author:
//          khoing(https://blog.csdn.net/qq_45391763)
//===============================================================

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//曝光融合
//曝光融合通过仅在多重曝光图像序列中保留“最佳”部分来计算所需图像。


//------------------------------------------------------------------------
void readImages(vector<Mat>& images)
{

	int numImages = 16;
	static const char* filenames[] =
	{
	  "C:/Users/sualab/Desktop/images/memorial0061.jpg",
	  "C:/Users/sualab/Desktop/images/memorial0062.jpg",
	  "C:/Users/sualab/Desktop/images/memorial0063.jpg",
	  "C:/Users/sualab/Desktop/images/memorial0064.jpg",
	  "C:/Users/sualab/Desktop/images/memorial0065.jpg",
	  "C:/Users/sualab/Desktop/images/memorial0066.jpg",
	  "C:/Users/sualab/Desktop/images/memorial0067.jpg",
	  "C:/Users/sualab/Desktop/images/memorial0068.jpg",
	  "C:/Users/sualab/Desktop/images/memorial0069.jpg",
	  "C:/Users/sualab/Desktop/images/memorial0070.jpg",
	  "C:/Users/sualab/Desktop/images/memorial0071.jpg",
	  "C:/Users/sualab/Desktop/images/memorial0072.jpg",
	  "C:/Users/sualab/Desktop/images/memorial0073.jpg",
	  "C:/Users/sualab/Desktop/images/memorial0074.jpg",
	  "C:/Users/sualab/Desktop/images/memorial0075.jpg",
	  "C:/Users/sualab/Desktop/images/memorial0076.jpg"
	};

	for (int i = 0; i < numImages; i++)
	{
		Mat im = imread(filenames[i]);
		images.push_back(im);
	}

}

//------------------------------------------------------------------------





int main19( int argc, char** argv)
{

	// Read images
	cout << "Reading images ... " << endl;
	vector<Mat> images;
//------------------------------------------------------------------------
	bool needsAlignment = true;

	//相机拍的图像，需要对齐，因为即使轻微的相机晃动也会降低最终图像的质量
	if (argc > 1)
	{
		// Read images from the command line
		for (int i = 1; i < argc; i++)
		{
			Mat im = imread(argv[i]);
			images.push_back(im);
		}

	}
	else
	{
		// Read example images
		readImages(images);
		needsAlignment = false;
	}

//------------------------------------------------------------------------

	//该算法将所有图像转换为中值阈值位图（MTB）。通过将值1分配给比中值亮度更亮的像素，
	//将值赋给0，否则为0来计算图像的MTB。MTB 不会改变曝光时间。因此，无需我们指定曝光时间即可对准MTB。
	if (needsAlignment)
	{
		cout << "Aligning images ... " << endl;
		Ptr<AlignMTB> alignMTB = createAlignMTB();
		alignMTB->process(images, images);
	}
	else
	{
		cout << "Skipping alignment ... " << endl;
	}

//------------------------------------------------------------------------
	 // Merge using Exposure Fusion
	cout << "Merging using Exposure Fusion ... " << endl;
	Mat exposureFusion;

	Ptr<MergeMertens> mergeMertens = createMergeMertens();
	mergeMertens->process(images, exposureFusion);


//------------------------------------------------------------------------

	// Save output image
	cout << "Saving output ... exposure-fusion.jpg" << endl;
	Mat outImg;
	exposureFusion.convertTo(outImg, CV_8UC3, 255);
	imwrite("C:/Users/sualab/Desktop/exposure-fusion.jpg", outImg);




    waitKey(0);
    


    return 0;
}