#include <opencv2/opencv.hpp>  //头文件
#include <opencv2/core/core.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cstdio>
using namespace cv;  //包含cv命名空间
using namespace std;
/*
void main()
{
	Mat out;
	Mat n = imread("road.jpg", 0);
	imshow("灰度图", n);
	GaussianBlur(n, out, Size(23, 23), 0, 0);
	Mat g;
	uchar table[255];
	for (size_t i = 0; i < 255; ++i){
		if (i < 150)
			table[i] = 0;
		else
			table[i] = 200;
	}
	Mat lookuptable(1, 256, CV_8U);
	uchar* p = lookuptable.data;
	for (size_t i = 0; i < 255; ++i)
		p[i] = table[i];
	for (size_t i = 0; i < 255; i++)
		LUT(out, lookuptable, g);
	imshow("WINDOW_NAME", g);
	uchar* data = g.ptr<uchar>(133);
	cout << "hello" << data[376] << endl << sizeof(data[376]) << endl;
	//printf("%d", data[376]);
	//通过测试
	int rowNumber = n.rows;
	int colNumber = n.cols;
	printf("%d\n", n.rows);
	printf("%d\n", n.cols);
	int left=0;
	int right=0;
	for (size_t i = 0; i < rowNumber; i++)
	{
		uchar* valu = g.ptr<uchar>(i);
		for (size_t j = 0; j < colNumber; j++)
		{
			//printf("%d", valu[j]);
			if ((i>(rowNumber / 2)) && (valu[j]>2))
				right++;
			if ((i < (rowNumber / 2)) && (valu[j] > 2))
				left++;
		}

	}
	cout << "right=" << right << "   " << "left=" << left << endl;
	//cout << n ;
	//uchar* y = g.data;
	//for (size_t r = 0; r < rowNumber*colNumber; r++)
	//{
	//	cout << *y++;
	//}
	waitKey(0);
}
*/
int main()
{
	int leDif = 0;
	int riDif = 0;
	VideoCapture capture2(0);
	//VideoCapture capture(0);
	while (1)
	{
		Mat out;
		Mat frame2 , frame1;  //定义一个Mat变量，用于存储每一帧的图像
		capture2 >> frame1;  //读取当前帧
		cvtColor(frame1, frame2, COLOR_BGR2GRAY);
		//frame1.copyTo(frame2);
		GaussianBlur(frame2, out, Size(23, 23), 0, 0);
		Mat g;
		uchar table[255];
		for (size_t i = 0; i < 255; ++i){
			if (i < 150)
				table[i] = 0;
			else
				table[i] = 200;
		}
		Mat lookuptable(1, 256, CV_8U);
		uchar* p = lookuptable.data;
		for (size_t i = 0; i < 255; ++i)
			p[i] = table[i];
		for (size_t i = 0; i < 255; i++)
			LUT(out, lookuptable, g);
		int rowNumber = g.rows;
		int colNumber =g.cols;
		int left = 0;
		int right = 0;
		for (size_t i = 0; i < rowNumber; i++)
		{
			uchar* valu = g.ptr<uchar>(i);
			for (size_t j = 0; j < colNumber; j++)
			{
				if ((j > (colNumber / 2)) && (valu[j]>2))
					right++;
				if ((j < (colNumber / 2)) && (valu[j] > 2))
					left++;
			}
		}
		cout << "right=" << int(right/1000) << "   " << "left=" << int(left/1000) << endl;
		//PID
		if (right>left)
		{
			riDif = (right - left)/1000;
			cout << "右差值是" << riDif << endl;
		}
		else
		{
			leDif = (left - right)/1000;
			cout << "左差值是" << leDif << endl;
		}
		imshow("", g);
		waitKey(30);
	}
	return 0;
}
