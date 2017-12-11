#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;


int main()
{
VideoCapture cap(0);
Mat frame,fr;
int id;
vector<vector<Point> > contours;
namedWindow("original",CV_WINDOW_NORMAL);
double area;
for(;;)
{
    cap>>frame;

    Mat ne(frame.size(),frame.type());
    ne=Scalar(255,255,255);
    Canny(frame,fr,50,100);
    findContours(fr,contours,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
    area=contourArea(contours[0]);
    id=0;
    for(int i=1;i<contours.size();i++)
    {
        if(contourArea(contours[i])>area)
        {        id=i;
                area=contourArea(contours[i]);
        }
    }
    approxPolyDP(contours[id],contours[id],5,true);
    Rect rect=boundingRect(contours[id]);
    rectangle(frame,rect,Scalar(255,0,0));
    imshow("original",frame);
    waitKey(20);





}



return 0;
}

