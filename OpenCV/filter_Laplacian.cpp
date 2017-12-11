#include "opencv2/opencv.hpp"
#include<iostream>
using namespace std;
using namespace cv;



int main()
{

Mat lap,img,res;
img=imread("/home/noufal/Projects/DIP/E.jpg");

Laplacian(img,lap,-1);
res=lap;


namedWindow("display",CV_WINDOW_NORMAL);
imshow("display",res);
imwrite("result.jpg",res);
waitKey(0);
return 0;


}
