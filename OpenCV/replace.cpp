#include "opencv2/opencv.hpp"
#include<iostream>

using namespace cv;
using namespace std;

int main()
{

//uchar *p;
Mat img=imread("/home/noufal/Desktop/tj.jpg");//path to img..img must be 640*480 (webcams resolution

int l1=0,l2=0,l3=115,u1=77,u2=193,u3=255;
VideoCapture cap(0);
cout<<cap.get(CV_CAP_PROP_FRAME_WIDTH);
cout<<" "<<cap.get(CV_CAP_PROP_FRAME_HEIGHT);
namedWindow("before",CV_WINDOW_NORMAL);
namedWindow("after",CV_WINDOW_NORMAL);
namedWindow("Trackbars",CV_WINDOW_NORMAL);
namedWindow("final",CV_WINDOW_NORMAL);
createTrackbar("1L","Trackbars",&l1,255);
createTrackbar("2L","Trackbars",&l2,255);
createTrackbar("3L","Trackbars",&l3,255);
createTrackbar("1U","Trackbars",&u1,255);
createTrackbar("2U","Trackbars",&u2,255);
createTrackbar("3U","Trackbars",&u3,255);
Mat frame,frame2(480,640,CV_8UC3);//640*480 is my webcam resolution
Mat gry;
uchar *pgry,*pimg,*pframe2;
pimg=img.data;
for(;;)
{

cap>>frame;
frame.copyTo(frame2);
pframe2=frame2.data;

imshow("before",frame);
cvtColor(frame,frame,CV_BGR2HSV);
inRange(frame,Scalar(l1,l2,l3),Scalar(u1,u2,u3),gry);
pgry=gry.data;

for(unsigned long int i=0,k=0;i<307200;i++,k+=3)
{
if(*(pgry+i)==255)
{
*(pframe2+k)=*(pimg+k);//pixel replacement code for r g and b channels
*(pframe2+k+1)=*(pimg+k+1);
*(pframe2+k+2)=*(pimg+k+2);




}


}
//GaussianBlur(frame2, frame2, Size(7,7), 1.5, 1.5);
imshow("after",gry);
imshow("final",frame2);

if(waitKey(30)>=0)break;
}
/*
cout<<img.rows;
cout<<"\n"<<img.cols;
cout<<"\n"<<img.elemSize1();
p=img.data;
unsigned long int k=img.rows * img.cols*img.channels();
//GaussianBlur(img, img, Size(7,7), 1.5, 1.5);
if(img.isContinuous())
{

for(unsigned long int i=0;i<k;i=i+3)
{



    if(*(p+i+2)>= *(p+i+1) && *(p+i+2)>=*(p+i))
    {
        *(p+i+2)=0;
        *(p+i+1)=0;
        *(p+i)=0;

    }





}


}



namedWindow("new",CV_WINDOW_NORMAL);
imshow("new",img);
waitKey(0);
*/









return 0;
}
