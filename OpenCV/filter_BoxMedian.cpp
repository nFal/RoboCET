#include "opencv2/opencv.hpp"
#include<iostream>
using namespace std;
using namespace cv;



int main()
{

Mat img,res;

img=imread("/home/noufal/Projects/DIP/N.bmp");

medianBlur(img,res,3);
//boxFilter(img,res,-1,Size(5,5));


namedWindow("display",CV_WINDOW_NORMAL);
imshow("display",res);
imwrite("result.jpg",res);

waitKey(0);
return 0;


}

