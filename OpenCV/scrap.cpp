#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
Mat a(3,3,CV_8UC1,Scalar(3));
Mat b;
a.convertTo(b,CV_32FC1);
Mat c,d;
sqrt(b,c);
c.convertTo(d,CV_8UC1);
cout<<d;

return 0;






}

