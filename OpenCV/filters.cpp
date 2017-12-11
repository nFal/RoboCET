#include "opencv2/opencv.hpp"

using namespace cv;

int main()
{
Mat res,img;
img=imread("/home/noufal/Projects/DIP/aa.png");
flip(img,res,5);
namedWindow("display",CV_WINDOW_NORMAL);
imshow("display",img);
waitKey(0);
return 0;






}
