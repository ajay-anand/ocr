//g++ rowcountdee.cpp -o rowcountdee -lpng
#include "cluster/cluster.h"
#include "png/png.h"
#include<math.h>
#include<iostream>
#include <fstream>
#include<vector>
using namespace std;

unsigned char getValue(const mPng::Image& img, unsigned int x, unsigned int y, unsigned z = 0)
{
  return img.data[4*x*img.width + 4*y + z];
}

int line=0; vector<float> v;
void countpixel(int arr[],int size)
{
     int i=0;
     int flag=0,countblackpixel=0;
     for(i=0;i<size;i++)
     {
          if(arr[i]<250)
          {
                                         
              countblackpixel++;   
             // break;  
          }
                        
     }
     v.push_back(countblackpixel);
                                 
 }

int main()
{
    int i,j;int line=0,tr=0;vector<int> idxArr;
    
    mPng::Image image;
    mPng::read("cap1.png",image);
    
    
    int width=image.width;
    int height=image.height;
    int arr[image.width];
    
    
    for(i=0;i<image.height;i++)
    {
        for(j=0;j<image.width;j++)
          {
             int k=(int)getValue(image,i,j);
             arr[j]=k;
          }
      
      countpixel(arr,image.width);      
    }
    
    
    
    
     // cout<<"Vector"<<"\n";
      //for(int i=0;i<v.size();i++)
     // cout<<v[i]<<"\n";
      
      //float threshold=getThreshold(v);
     // cout<< "Threshold="<<threshold<<"\n";
     
     
     
       //createTranstionArray(v,threshold,idxArr);
      // cout<<"IndexValues"<<"\n";
       //for(int i=0;i<idxArr.size();i++) cout<<idxArr[i]<<"\n";
       
       //float avgCharWidth = 0;
       //for(int i =0; i < idxArr.size(); i+=2 ) avgCharWidth += (idxArr[i+1]-idxArr[i]);
       //avgCharWidth /= (idxArr.size()/2);
       
      createTranstionArray(v, 2, idxArr );
      
      for(i=0;i<idxArr.size();i++)
      cout<<idxArr[i]<<"\n";



/*

      bool flag = true;
       for(int i=0;i<idxArr.size()-1;++i)
       {
         int j;
         if( flag ) for( j = idxArr[i]+1; j <= idxArr[i+1]; ++j )
         {
              cout << -v[j] << "\n";
         }
          else for( j = idxArr[i]; j < idxArr[i+1]; ++j ) cout << 100 << "\n";
          flag = !flag;
       }                                                                                               ajay*/
       
       
       
       
 
return 0;
        
}
