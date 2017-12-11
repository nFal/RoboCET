#include <math.h>
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

float angle(Point2f A, Point2f B,Point2f C) {

    Point2f BC(C.x-B.x,C.y-B.y),BA(A.x-B.x,A.y-B.y);
    float bc=norm(BC),ba=norm(BA);
    float D=BC.ddot(BA);
    float ang=57.297*acos((double)(D)/(bc*ba));
    return ang;
}

int main(int, char**)
{
//    VideoCapture cap(0); // open the default camera
  //  if(!cap.isOpened())  // check if we succeeded
    //    return -1;
    cout<<angle(Point2f(100,0),Point2f(0,0),Point2f(0,100));

    //namedWindow("processed",1);
    //namedWindow("Original",1);

   /* for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame f  rom camera


        if(waitKey(30) >= 0) break;
    }*/
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}


