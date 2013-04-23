// g++ rotation.cpp -o rotation -lpng
#include "png/png.h"
#include <math.h>
#define PI 3.14159265

#include <iostream>
using std::cout;

unsigned char getValue(const mPng::Image& img, unsigned int x, unsigned int y, unsigned z )
{
  return img.data[4*x*img.width + 4*y + z];
}

void setValue(const mPng::Image& img, unsigned int x, unsigned int y, unsigned int z, unsigned char c)
{
  img.data[4*x*img.width + 4*y + z ] = c;
}


int main()
{
	int i,j,si,sj;
  int ci,cj,csi,csj;

  mPng::Image image;
	mPng::read("normal.png", image);

  int w = image.width;
  int h = image.height;
  csi = h/2; csj = w/2;

  float theta = -30;
  float s = sin(theta*M_PI/180.0);
  float c = cos(theta*M_PI/180.0);
	cout<< w <<" "<< h <<"\n";;
    
 
  mPng::Image copy;
  copy.width = ceil(fabs(h*s)+w*c); 
  copy.height = ceil(fabs(w*s)+h*c);
  ci = copy.height/2; cj = copy.width/2;
  copy.data = 
      new unsigned char[copy.width*copy.height*4];

  for( i = 0; i < copy.height; ++i )
  {
    for( j = 0; j < copy.width; ++j )
    {
        si = csi +  c*(i-ci) - s*(j-cj);
        sj = csj +  s*(i-ci) + c*(j-cj);

        if( si >=0 && si < h && sj >= 0 && sj < w )
        {
          copy.data[ 4*i*copy.width + 4*j + 0 ] 
            = image.data[4*si*w + 4*sj + 0]; 
          copy.data[ 4*i*copy.width + 4*j + 1 ] 
            = image.data[4*si*w + 4*sj + 1]; 
          copy.data[ 4*i*copy.width + 4*j + 2 ] 
            = image.data[4*si*w + 4*sj + 2]; 
          copy.data[ 4*i*copy.width + 4*j + 3 ] 
            = image.data[4*si*w + 4*sj + 3]; 
        }
        else
        {
          copy.data[ 4*i*copy.width + 4*j + 0 ] 
            = 200; 
          copy.data[ 4*i*copy.width + 4*j + 1 ] 
            = 255; 
          copy.data[ 4*i*copy.width + 4*j + 2 ] 
            = 255; 
          copy.data[ 4*i*copy.width + 4*j + 3 ] 
            = 255; 
        }

    }
  }
	
	
	mPng::write("rotated.png",copy);
	
	return 0;
}


/****
	int width=image.width;
	int height=image.height;
	
	double param=180.0;
    double sinval =sin (param*PI/180);
    double cosval = cos(param*PI/180);
    double x0 = 0.5 * (width  - 1);     // point to rotate about
    double y0 = 0.5 * (height - 1);     // center of image
    cout<<x0<<y0;
    mPng::Image copy;
    copy.width = width; copy.height = height;
    copy.data = new unsigned char[width*height*4];
    int x,y;
      for ( x = 0; x < height; x++) {
            for ( y = 0; y < width; y++) {
                double a = x - x0;
                double b = y - y0;
                int xx = (int) (+a * cosval - b * sinval + x0);
                int yy = (int) (+a * sinval + b * cosval + y0);

                // plot pixel (x, y) the same color as (xx, yy) if it's in bounds
                if (xx >= 0 && xx < height && yy >= 0 && yy < width) {
               
        setValue(copy, x,y, 0, getValue(image, xx,yy,0));
	    setValue(copy, x,y, 1, getValue(image, xx,yy,1));
	    setValue(copy, x,y, 2, getValue(image, xx,yy,2));
	    setValue(copy, x,y, 3, 255);
               }
            }
        }

*****/
