float w=250,h=350;
const int kThreashold = 220;
const int kMaxVal = 255;
const Size kGaussianRedSize = Size(5, 5);


int main(){VideoCapture video;
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
    for (size_t i = 0; i < contours.size(); i++)
    {
        double area = contourArea(contours[i]);
        if (area > 100) // 根据实际情况调整筛选条件
        {
            armorContours.push_back(contours[i]);
        }
    }

    // 绘制筛选后的轮廓
    Mat result = Mat::zeros(frame.size(), CV_8UC3);
    drawContours(result, armorContours, -1, Scalar(0, 255, 255), 2);

    // 显示结果
    imshow("Result", result);
