#include "opencv2/opencv.hpp"
#include<iostream>
using namespace std;
using namespace cv;



int main()
{

Mat img,res,kernel;
int data[3][3]={{-1,0,-1},{-2,6,2},{-1,0,-1}};
kernel=Mat(3,3,CV_32SC1,&data);
flip(kernel,kernel,-1);
cout<<kernel;
img=imread("/home/noufal/Projects/DIP/S.jpg");
//cvtColor(img,img,CV_RGB2GRAY);
filter2D(img,res,-1,kernel);

namedWindow("display",CV_WINDOW_NORMAL);
imshow("display",res);
imwrite("result.jpg",res);

waitKey(0);
return 0;


}
