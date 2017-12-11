#include "opencv2/opencv.hpp"
#include<iostream>
using namespace std;
using namespace cv;



int main()
{

Mat img,res,st_el;

img=imread("/home/noufal/Projects/DIP/N.jpg");

st_el=getStructuringElement(MORPH_RECT,Size(3,3));
morphologyEx(img,res,MORPH_CLOSE,st_el);



namedWindow("original",CV_WINDOW_NORMAL);
namedWindow("processed",CV_WINDOW_NORMAL);

imshow("original",img);
imshow("processed",res);
imwrite("result.jpg",res);

waitKey(0);
return 0;


}



