
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace cv;
using namespace std;

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>

int fun(string a)
{

Mat img = imread(a,0);
//cout<<"cols= "<<img.cols<<"row= "<<img.rows<<"\n";
int i,j,count=0;
for(i=0;i<img.cols;i++)
{
for(j=0;j<img.rows;j++)
{
int k=img.at<uchar>(j,i);
if(k==0)
{  
count++;
//cout<<"col="<<i<<"row="<<j<<"k= "<< k<<"\t\n";
}
}
} 
//cout<<"count="<<count<<"\n";
if(count>=70000)
cout<<" Heavy weight vehicle Toll Cost 70 Rs"<<endl;
else
cout<<" Light weight vehicle Toll Cost 40 Rs"<<endl;

  waitKey(0);
}
