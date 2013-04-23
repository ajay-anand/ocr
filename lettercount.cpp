//g++  lettercount.cpp -o lettercount -lpng
#include "cluster/cluster.h"
#include "png/png.h"
#include<math.h>
#include<iostream>
#include <fstream>
#include<vector>
using namespace std;



int main()
{
    mPng::Image image;
    mPng::read("Word=17.png",image);
    mPng::Image cropped;
    crop( image, cropped );
    mPng::write("output.png", cropped);
    
    return 0;
        
}
