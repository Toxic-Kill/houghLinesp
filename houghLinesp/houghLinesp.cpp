#include <iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat cannyMat;
	cv::Mat gryMat= cv::imread("D:\\Files\\metal-part-distorted-03.png",0);
	cv::Mat srcMat = cv::imread("D:\\Files\\metal-part-distorted-03.png");//读取图像
	//检测图像是否读取成功
	if (srcMat.empty())
	{
		cout << "Can not open the image." << endl;
		return -1;
	}
	//用Canny算子进行边缘检测
	cv::Canny(gryMat, cannyMat, 100, 250, 3);
	//进行霍夫变换
	cv::Mat lineMat;
	cv::HoughLinesP(cannyMat, lineMat, 1, CV_PI / 180, 50, 50, 30);
	//绘制直线
	for (int i = 0; i < lineMat.rows; i++)
	{
		cv::Point pt1, pt2;
		pt1.x = lineMat.at<Vec4i>(i, 0)[0];
		pt1.y = lineMat.at<Vec4i>(i, 0)[1];
		pt2.x = lineMat.at<Vec4i>(i, 0)[2];
		pt2.y = lineMat.at<Vec4i>(i, 0)[3];
		line(srcMat, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);
	}
	//显示结果
	cv::imshow("dst", srcMat);
	cv::imshow("canny", cannyMat);
	waitKey(0);
}

