#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include<iostream>

using namespace std;
using namespace cv;

int main()
{

Mat stelem,img,imgblur,processd,gray;
int thresh=40;
VideoCapture cap(0);
namedWindow("Original",CV_WINDOW_NORMAL);
namedWindow("Corners",CV_WINDOW_NORMAL);
//namedWindow("Eroded",CV_WINDOW_NORMAL);
stelem=getStructuringElement(MORPH_RECT,Size(3,3));
//createTrackbar("thresh","Eroded",&thresh,255);

for(;;)
{

vector<Point2d> corners;
cap>>img;

imshow("Original",img);

cvtColor(img,gray,CV_BGR2GRAY);
goodFeaturesToTrack(gray,corners,10,0.01,10);
processd=img.clone();
cout<<corners.size() <<" ";
waitKey(10);
for(int i=0;i<corners.size();i++)
    circle(processd,corners[i],4,CV_RGB(0,255,0),-1);
imshow("Corners",processd);
waitKey(30);




}




return 0;
}
