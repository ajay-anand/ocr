//g++ threshold.cpp -o threshold -lpng
#include "cluster/cluster.h"
#include "png/png.h"
#include<iostream>
#include<vector>

using namespace std;

unsigned char getValue(const mPng::Image& img, unsigned int x, unsigned int y, unsigned z = 0)
{
  return img.data[4*x*img.width + 4*y + z];
}


int main()
{
     
    int i=0,j=0,totalsum=0;
    vector <float> v;
    
    mPng::Image image;
    mPng::read("cap.png",image);
    
   for(i=0;i<image.height;i++)
      for(j=0;j<image.width;j++)
             v.push_back(getValue(image,i,j));
               
    float newth = getThreshold(v);
    
  mPng::Image copy;
  copy.width = image.width; 
  copy.height = image.height;
  copy.data =  new unsigned char[copy.width*copy.height*4];
    
for( i = 0; i < image.height; ++i )
for( j = 0; j < image.width ; ++j )
{
     int k=(int)getValue(image,i,j);
     if(k<newth)
     {
     copy.data[i*image.width*4+j*4+0]=0;
     copy.data[i*image.width*4+j*4+1]=0;
     copy.data[i*image.width*4+j*4+2]=0;
     copy.data[i*image.width*4+j*4+3]=255;
     }
     else
     {
     copy.data[i*image.width*4+j*4+0]=255;
     copy.data[i*image.width*4+j*4+1]=255;
     copy.data[i*image.width*4+j*4+2]=255;
     copy.data[i*image.width*4+j*4+3]=255;
     }
      
}
	mPng::write("outrowimage1.png",copy);
    
    return 0;
}
