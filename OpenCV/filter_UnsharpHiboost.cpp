#include "opencv2/opencv.hpp"

using namespace cv;

int main()
{
const int k=-1;
Mat blur,img,sub,res;
img=imread("/home/noufal/Projects/DIP/f.jpg");

boxFilter(img,blur,-1,Size(5,5));
sub=img-blur;
res=img+k*sub;



namedWindow("display",CV_WINDOW_NORMAL);
imshow("display",res);
imwrite("result.jpg",res);
waitKey(0);
return 0;


}
