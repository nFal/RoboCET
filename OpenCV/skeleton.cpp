#include "opencv2/opencv.hpp"
#include<iostream>
using namespace std;
using namespace cv;



int main()
{

Mat img,org,st_el,temp,eroded;

org=imread("/home/noufal/Projects/DIP/o.png");
cvtColor(org,img,CV_RGB2GRAY);

Mat skel(img.size(), CV_8UC1, Scalar(0));

threshold(img, img, 70, 255, THRESH_BINARY);
st_el = getStructuringElement(MORPH_CROSS, Size(3, 3));

bool done=false;
for(int i=0;i<10;i++)
{
    erode(img, eroded, st_el);
    dilate(eroded, temp, st_el); // temp = open(img)
    subtract(img, temp, temp);
    bitwise_or(skel, temp, skel);
    eroded.copyTo(img);
    done = (countNonZero(img) == 0);


}



namedWindow("original",CV_WINDOW_NORMAL);
namedWindow("processed",CV_WINDOW_NORMAL);

imshow("original",org);
imshow("processed",img);
imwrite("result.jpg",img);

waitKey(0);
return 0;


}













