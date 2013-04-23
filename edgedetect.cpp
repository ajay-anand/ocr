// g++ edgedetect.cpp -o edgedetect -lpng
#include "png/png.h"
#include <math.h>

#include <iostream>
using std::cout;

unsigned char getValue(const mPng::Image& img, unsigned int x, unsigned int y, unsigned z = 0)
{
  return img.data[4*x*img.width + 4*y + z];
}

void setValue(const mPng::Image& img, unsigned int x, unsigned int y, unsigned int z, unsigned char c)
{
  img.data[4*x*img.width + 4*y + z ] = c;
}

int main()
{
	mPng::Image image;
	
	mPng::read("full.png", image);

	long pos = (unsigned long)image.width*(unsigned long)image.height*4-4;
	unsigned char dummy;
	while( pos >= 0 )
	{
		dummy = ((int)image.data[pos]+(int)image.data[pos+1]+(int)image.data[pos+2])/3;
		image.data[pos+0] = dummy;
		image.data[pos+1] = dummy;
		image.data[pos+2] = dummy;
		image.data[pos+3] = 255;
		pos -= 4;
	}

	int i,j;
	unsigned char current, next;
	
	mPng::Image copy;
	copy.data = new unsigned char[image.width*image.height*4];
	copy.width = image.width;
	copy.height = image.height;
	
	
	for( i = 1; (i < image.height-1); ++i )
	{
	  for( j = 1; j < image.width-1; ++j )
	  {
	    //current = getValue(image, i,j);
	    //next = getValue( image, i, j + 1);
	    
      //if( current < next ) current = 0;
	    //else current = 255;
	    
	    float dummy = (int)(4.0*getValue(image, i,j) - (float)getValue(image, i-1, j-1 ) - (float)getValue(image, i-1, j+1 ) - (float)getValue(image, i+1, j-1 ) - (float)getValue(image, i+1, j+1 ));
	    
	    if( dummy < 0 ) dummy = 0; else if( dummy > 255 ) dummy = 255;
	    
	    int dummy1 = 255*pow(dummy/255.0,0.25);//How we will know this value?
	    
	    setValue(copy, i,j, 0, dummy1);
	    setValue(copy, i,j, 1, dummy1);
	    setValue(copy, i,j, 2, dummy1);
	    setValue(copy, i,j, 3, 255);
	  }
	}
	
	mPng::write("edge.png", copy);

	return 0;
}
