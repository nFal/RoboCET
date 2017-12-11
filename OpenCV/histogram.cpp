#include "opencv2/opencv.hpp"
#include<iostream>
using namespace std;
using namespace cv;



int main()
{

Mat img,res;

img=imread("/home/noufal/Projects/DIP/V.jpg");

cvtColor(img,img,CV_RGB2GRAY);
equalizeHist(img,res);

namedWindow("original",CV_WINDOW_NORMAL);
namedWindow("processed",CV_WINDOW_NORMAL);

imshow("original",img);
imshow("processed",res);
imwrite("original.jpg",img);
imwrite("result.jpg",res);

waitKey(0);
return 0;


}


