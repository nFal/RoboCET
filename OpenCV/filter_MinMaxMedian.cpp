#include "opencv2/opencv.hpp"
#include<iostream>
using namespace std;
using namespace cv;



int main()
{

Mat img,res;

img=imread("/home/noufal/Projects/DIP/e");

medianBlur(img,res,3);

namedWindow("display",CV_WINDOW_NORMAL);
imshow("display",res);
imwrite("result.jpg",res);

waitKey(0);
return 0;


}

