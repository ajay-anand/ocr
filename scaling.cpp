// g++ scaling.cpp -o scaling -lpng
#include<iostream>
using std::cout;
#include "png/png.h"
#include <math.h>

typedef unsigned char * UCP;

class Pixel
{
      public:
      float r, g, b;
      Pixel(){}
      Pixel(float _r, float _g, float _b):r(_r), g(_g), b(_b) {}
      Pixel(unsigned char * c):r(c[0]),g(c[1]),b(c[2]) {}
      Pixel operator+ (const Pixel& p) const
      {
            return Pixel( r + p.r , g + p.g, b + p.b );
      }
      
      Pixel operator* (const float f) const
      {
            return Pixel( f*r, f*g, f*b );
      }

      void copyTo( unsigned char * c ) 
      { 
           if( r < 0 ) c[0] = 0; else if( r > 255 ) c[0] = 255; else c[0] = r;
           if( g < 0 ) c[1] = 0; else if( g > 255 ) c[1] = 255; else c[1] = g;
           if( b < 0 ) c[2] = 0; else if( b > 255 ) c[2] = 255; else c[2] = b;
      }

      void addTo( unsigned char * c ) 
      { 
           float _r = c[0]+r, _g = c[1] + g, _b = c[2] + b;
           if( _r < 0 ) c[0] = 0; else if( _r > 255 ) c[0] = 255; else c[0] = _r;
           if( _g < 0 ) c[1] = 0; else if( _g > 255 ) c[1] = 255; else c[1] = _g;
           if( _b < 0 ) c[2] = 0; else if( _b > 255 ) c[2] = 255; else c[2] = _b;
      }
};

Pixel operator* (const float f, const Pixel& p )
{
      return Pixel( f*p.r, f*p.g, f*p.b );
}

void fun(const float l, const float u, int& a, float& f, float& g, int& m)
{
     int i,j;
     
     a = i = floor(l);
    if( i == l ) --i;
    j=ceil(u);
    if( j == u ) ++j;

    
    if(j-i<=1)
    {
      f=u-l;
      g=0;
      m=0;
    }
    else
    {
      f=1-l+i;
      g=1-j+u;
      m=j-2-i;
    }
     //cout<<"f2: "<<f2<<"\t"<<"g2: "<<g2<<"\t"<<"m2: "<<m2<<"\n\n"; 
 }
unsigned char getValue(const mPng::Image& img, unsigned int x, unsigned int y, unsigned z)
{
  return img.data[4*x*img.width + 4*y + z];
}

unsigned char * getValue(const mPng::Image& img, unsigned int x, unsigned int y)
{
  return img.data + (4*x*img.width + 4*y);
}

void setValue(const mPng::Image& img, unsigned int x, unsigned int y, unsigned int z, unsigned char c)
{
  img.data[4*x*img.width + 4*y + z ] = c;
}

int main()
{
    float fx=12,fy=12;
    
    
    mPng::Image image1;
	mPng::read("5.png", image1);
	
	mPng::Image image2;
	image2.width=ceil(image1.width*fx);
	image2.height=ceil(image1.height*fy);
	image2.data=new unsigned char[image2.width*image2.height*4];
	
	int i,j;
	
	for( i = 0; i < image2.height; ++i ) 
    for( j = 0; j < image2.width; ++j )
	{
        /* setValue(image2, i, j, 0 , 255 );
         setValue(image2, i, j, 1 , 255 );
         setValue(image2, i, j, 2 , 255 );*/
         setValue(image2, i, j, 3 , 255 );
         
     }
    
    for(i=0;i<image1.height;i++)
	{
        for(j=0;j<image1.width;j++)
        {
           int val;                    
           float l1, u1, l2, u2;
           float f1, g1, f2, g2;
           int m1, m2,a1,a2;
           
           l1 = fx*i;
           u1 = fx*(i+1);
           
           fun( l1, u1,a1, f1, g1, m1 );
           
           
           l2 = fy*j;
           u2 = fy*(j+1);   
           
           fun(l2, u2,a2,f2,g2,m2); 
        
           (f1*f2*(Pixel)getValue(image1,i,j)).addTo( getValue( image2, a1, a2 ) );
           (f1*g2*(Pixel)getValue(image1,i,j)).addTo( getValue( image2, a1, a2+m2 ) );
           (g1*f2*(Pixel)getValue(image1,i,j)).addTo( getValue( image2, a1+m1, a2 ) );
           (g1*g2*(Pixel)getValue(image1,i,j)).addTo( getValue( image2, a1+m1, a2+m2 ) );
           
           int k, m;
           
           for(k = 0; k < m2; ++k )
           {
                 for( m = 0; m < m1; ++m )
                 {
                      ((Pixel)getValue(image1,i,j)).copyTo( getValue( image2, a1+m+1, a2+k+1 ) );
                  }
                  
           }
           
        }
        
    }                       
	
	

	mPng::write("output.png", image2);
    
}
