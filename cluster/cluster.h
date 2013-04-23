#ifndef CLUSTER_H
#define CLUSTER_H
#include "png/png.h"
#include<vector>
using std::vector;

unsigned char getValue1(const mPng::Image& img, unsigned int x, unsigned int y, unsigned z=0 )
{
  return img.data[4*x*img.width + 4*y + z];
}


void createTranstionArray( const vector<float>& v,float threshold,vector<int>& idxArr )
{ 
   idxArr.clear();
   for(int i=0 ;i<v.size()-1 ;i++)
        if((v[i] <threshold)^(v[i+1]<threshold))
            idxArr.push_back(i+1);              
}



void crop( mPng::Image& image, mPng::Image& cropped)
{
    int sh,eh,sw,ew;
    int i,j,p,q;int k,l,res;
    int f1,f2;
    int counth=0,countw=0;
    
   
	
	
	for(i=0;i<image.height;i++)
	{
       for(j=0;j<image.width;j++)
          {
             k=(int)getValue1(image,i,j);
             if(k!=255) 
               {
                if(counth==0) { sh=i; }
                counth++;
                eh=i;
                break;
               }                                                   
           }
     }
	for(j=0;j<image.width;j++)
	{
        for(i=0;i<image.height;i++)
           {
              l=(int)getValue1(image,i,j);
                if(l!=255)  
                  {
                    if(countw==0) {sw=j;}
                    countw++; 
                    ew=j;
                    break;
                  }                           
            }
     }
     cropped.width=(ew-sw)+1;
     cropped.height=(eh-sh)+1;
     cropped.data = new unsigned char[4*cropped.width*cropped.height];
                                   
                                                         

    	  
                                        
     for(i=sh;i<=eh;i++)
     {
                       for(j=sw;j<=ew;j++)
                       {
                            f1=i-sh;f2=j-sw;
                            cropped.data[ 4*f1*cropped.width + 4*f2 + 0 ]=image.data[4*i*image.width + 4*j + 0];
                            cropped.data[ 4*f1*cropped.width + 4*f2 + 1 ]=image.data[4*i*image.width + 4*j + 1];
                            cropped.data[ 4*f1*cropped.width + 4*f2 + 2 ]=image.data[4*i*image.width + 4*j + 2];
                            cropped.data[ 4*f1*cropped.width + 4*f2 + 3 ]=image.data[4*i*image.width + 4*j + 3];    
                       }
                       
     }
     
}

float getThreshold( const vector<float>& v )
{
      float avg=0;int i=0;
      for( i=0;i<v.size();i++)    avg += v[i];
      avg/=v.size();
      
      float avg1=0,avg2=0,cnt1=0,cnt2=0,oldavg=0;
      while(true)
      {
          avg1 = avg2 = cnt1 = cnt2 = 0;
          for(i=0;i<v.size();i++)
          {
                 if(v[i]>avg) 
                    { ++cnt1; avg1+=v[i];}
                 else
                    { ++cnt2; avg2+=v[i];}
          }
            
          avg1 /= cnt1;
          avg2 /= cnt2;
          avg = (avg1 + avg2) / 2;
          if ( oldavg == avg )  return avg;
          oldavg = avg;
      }
}
#endif
