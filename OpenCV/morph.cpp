#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;


int main()
{
VideoCapture cap(0);
Mat frame;
Mat strel=getStructuringElement(MORPH_RECT,Size(5,5));
namedWindow("original",CV_WINDOW_NORMAL);
for(;;)
{
cap>>frame;
morphologyEx(frame,frame,MORPH_OPEN,strel);

imshow("original",frame);
waitKey(30);



}



return 0;
}
