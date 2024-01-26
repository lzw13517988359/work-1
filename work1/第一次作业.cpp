#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
using namespace std;
using namespace cv;Mat imgGray, imgBlur, imgCanny, imgDil, imgHSV, mask, imgBinary;
int hmin=0,smin=110,vmin=153;
int hmax=19,smax=240,vmax=255;
int main(){
string path="../resources/kunkunplayball.mp4";
VideoCapture cap(path);
Mat img;
namedWindow("Trackbars",(640,200));
createTrackbar("Hue Min","Trackbars",nullptr,179);
setTrackbarPos("Hue Min", "Trackbars", hmin);
createTrackbar("Hue Max","Trackbars",nullptr,179);
setTrackbarPos("Hue Max", "Trackbars", hmax);
createTrackbar("Sat Min","Trackbars",nullptr,255);
setTrackbarPos("Sat Min", "Trackbars", smin);
createTrackbar("Sat Max","Trackbars",nullptr,255);
setTrackbarPos("Sat Max", "Trackbars", smax);
createTrackbar("Val Min","Trackbars",nullptr,255);
setTrackbarPos("Val Min", "Trackbars", vmin);
createTrackbar("Hal Max","Trackbars",nullptr,255);
setTrackbarPos("Hal Max", "Trackbars", vmax); */
while (true) {
	cap.read(img);
	cvtColor(img,imgHSV,COLOR_BGR2HSV);
	 Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    inRange(imgHSV, lower, upper, mask);

    Canny(mask, imgBinary, 100, 200);

    Mat kernel = (getStructuringElement(MORPH_RECT, Size(3, 3)));
    dilate(imgBinary, imgDil, kernel);

    vector<vector<Point>>contours;
    findContours(imgDil, contours, RETR_LIST, CHAIN_APPROX_NONE);
    vector<Point>centers;
    vector<float>radius;
    for (int i = 0; i < contours.size(); i++) {
        Point2f c;
        float r;
        minEnclosingCircle(contours[i], c, r);
        centers.push_back(c);
        radius.push_back(r);
        for (int j = 0; j < contours[i].size(); j++) {
            circle(img, contours[i][j], 1, Scalar(255, 0, 0), FILLED);
        }
    }
    for (int i = 0; i < centers.size(); i++) {
        circle(img, centers[i], cvRound(radius[i]), Scalar(255, 0, 0), LINE_4);
    }
    imshow("Image Mask", mask);
    imshow("Image Dilation", imgDil);
    imshow("Image", img);
    waitKey(20);
}

return 0;
} 
