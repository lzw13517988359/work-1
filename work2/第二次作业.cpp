#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
using namespace std;
using namespace cv;
float w=250,h=350;
const int kThreashold = 220;
const int kMaxVal = 255;
const Size kGaussianRedSize = Size(5, 5);


int main() {
	VideoCapture video;
	video.open("../resources/ood_red.mp4");
	Mat frame,grayImg,gray,binary,Gaussian,binary1,canny,result1,imgWarp;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Rect boundRect;
	RotatedRect box;
	vector<Point2f> boxPts(4);

	for (;;) {

		Rect point_array[20];
		video >> frame;
		if (frame.empty()) {
			break;
		}


		cvtColor(frame, grayImg, COLOR_BGR2GRAY); // 转换为灰度图像
		GaussianBlur(grayImg, gray, Size(5, 5), 0, 0); // 高斯滤波

		Canny(gray, canny,150,450); // 边缘检测
		threshold(canny, binary, kThreashold, kMaxVal, 0);
		GaussianBlur(binary, Gaussian, kGaussianRedSize, 0);
		cv::Mat template1 = imread("../resources/Hb6lWxmn.jpeg", cv::IMREAD_GRAYSCALE);
// 加载其他数字模板...
		matchTemplate(gray,template1,result1,TM_CCOEFF_NORMED);
		double minVal1, maxVal1;
		Point minLoc1, maxLoc1;
		Mat minMaxLoc(result1, &minVal1, &maxVal1, &minLoc1, &maxVal1);
//由数字匹配所得点的坐标，再由点的坐标截取数字“4”所处位置，Point2d后面参数有误，无法得出。
// Point2d src[4]={{minVal1,maxVal1},{minVal1,maxVal1},{minLoc1,maxVal1},{minLoc1,maxVal1}};
// Point2d dst[4]={{0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h}};
// Mat matrix=getPerspectiveTransform(src,dst);
// warpPerspective(frame,imgWarp,matrix,Point(w,h));
//imshow("Imgwarp",imgWarp);
		auto start = std::chrono::high_resolution_clock::now();

		// 在这里进行图像处理





		std::vector<std::vector<Point>> armorContours;
		for (size_t i = 0; i < contours.size(); i++) {
			double area = contourArea(contours[i]);
			if (area > 100) { // 根据实际情况调整筛选条件
				armorContours.push_back(contours[i]);
			}
		}

		// 绘制筛选后的轮廓
		Mat result = Mat::zeros(frame.size(), CV_8UC3);
		drawContours(result, armorContours, -1, Scalar(0, 255, 255), 2);

		// 显示结果
		imshow("Result", result);

		findContours( Gaussian, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
		int index = 0;
		for (int i = 0; i < contours.size(); i++) {
			//box = minAreaRect(Mat(contours[i]));
			//box.points(boxPts.data());
			boundRect = boundingRect(Mat(contours[i]));
			//rectangle(frame, boundRect.tl(), boundRect.br(), (0, 255, 0), 2,8 ,0);
			try {
				if (double(boundRect.height / boundRect.width) >= 1.2 && boundRect.height > 10 && boundRect.height>5) {
					point_array[index] = boundRect;
					index++;
				}
			} catch (const char* msg) {
				cout << printf(msg) << endl;
				//continue;
			}
		}
		int point_near[2];
		int min = 10000;
		for (int i = 0; i < index-1; i++) {
			for (int j = i + 1; j < index; j++) {
				int value = abs(point_array[i].area() - point_array[j].area());
				if (value < min) {
					min = value;
					point_near[0] = i;
					point_near[1] = j;
				}
			}
		}
		try {
			Rect rectangle_1 = point_array[point_near[0]];
			Rect rectangle_2 = point_array[point_near[1]];
			if (rectangle_2.x == 0 || rectangle_1.x == 0) {
				throw "not enough points";
			}
			Point point1 = Point(rectangle_1.x + rectangle_1.width / 2, rectangle_1.y);
			Point point2 = Point(rectangle_1.x + rectangle_1.width / 2, rectangle_1.y + rectangle_1.height);
			Point point3 = Point(rectangle_2.x + rectangle_2.width / 2, rectangle_2.y);
			Point point4 = Point(rectangle_2.x + rectangle_2.width / 2, rectangle_2.y + rectangle_2.height);
			Point p[4] = { point1,point2,point4,point3 };
			cout << p[0]<<p[1]<<p[2]<<p[3] << endl;

			机器人232李水兰 2024/1/26 14:26:57
//continue;
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::string processingTime = "Processing Time: " + std::to_string(duration.count()) + " ms";

		cv::putText(frame, processingTime, cv::Point(25, 75), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);


		imshow("video", frame);

		if (waitKey(20) >= 0) {
			15
			break;
		}


		return 0;
	}
}


