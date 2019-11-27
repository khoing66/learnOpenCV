
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

//�ع��ں�
//�ع��ں�ͨ�����ڶ����ع�ͼ�������б�������ѡ���������������ͼ��


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

	//����ĵ�ͼ����Ҫ���룬��Ϊ��ʹ��΢������ζ�Ҳ�ή������ͼ�������
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

	//���㷨������ͼ��ת��Ϊ��ֵ��ֵλͼ��MTB����ͨ����ֵ1���������ֵ���ȸ��������أ�
	//��ֵ����0������Ϊ0������ͼ���MTB��MTB ����ı��ع�ʱ�䡣��ˣ���������ָ���ع�ʱ�伴�ɶ�׼MTB��
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