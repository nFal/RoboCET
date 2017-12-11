#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;




int main()
{
Mat gradx,img,grady,res;
img=imread("/home/noufal/Projects/DIP/G.jpg");
img.convertTo(img,CV_32FC3,1/255.0);

Sobel(img,gradx,-1,1,0);
Sobel(img,grady,-1,0,1);
res=abs(gradx)+abs(grady);
namedWindow("display",CV_WINDOW_NORMAL);
imshow("display",res);
imwrite("result.jpg",res);
waitKey(0);
return 0;

}
