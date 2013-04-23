//g++  wordcount.cpp -o wordcount -lpng
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
          if(arr[i]<255)
          {
                                         
              countblackpixel++;   
             
          }
                        
     }
     v.push_back(countblackpixel);
                                 
 }

int main()
{
    int i,j;int line=0,tr=0;vector<int> idxArr;
    
    mPng::Image image;
    mPng::read("Line=1.png",image);
    
    
    int width=image.width;
    int height=image.height;
    int arr[image.height];
    
    
    
  for(j=0;j<image.width;j++)
    {
        for(i=0;i<image.height;i++)
          {
             int k=(int)getValue(image,i,j);
             arr[i]=k;
          }
      
      countpixel(arr,image.height);      
    }
    //for(i=0;i<v.size();i++)
    //cout<<v[i]<<"\n";
     
       
    createTranstionArray(v, 1, idxArr );
    cout<<"Before"<<idxArr.size();
    
    float avgCharWidth = 0;
       for(int i =0; i < idxArr.size(); i+=2 ) avgCharWidth += (idxArr[i+1]-idxArr[i]);
       avgCharWidth /= (idxArr.size()/2);
       
       cout<<"Char width"<< avgCharWidth;
    
    
    for(i=0;i<idxArr.size()-1;i++)
    {
                                int temp=idxArr[i+1]-idxArr[i];
                                if( temp <= (avgCharWidth/3))
        //if(idxArr[i+1]-idxArr[i] == 1 || idxArr[i+1]-idxArr[i] == 2 || idxArr[i+1]-idxArr[i] == 3 )
        
        {
                                // cout<<idxArr[i]<<"\n";
                                idxArr.erase(idxArr.begin()+(i+1));
                                  idxArr.erase(idxArr.begin()+(i));
                                  i=i-2;
                                  
                                  
        }
       
    }
    cout<<"After"<<idxArr.size()<<"\n";  
      for(i=0;i<idxArr.size();i++)
      cout<<idxArr[i]<<"\n";
     int word=0;
     
      for(int i=0;i<idxArr.size();i=i+2)
      {
  mPng::Image copy;
  copy.width = idxArr[i+1]-idxArr[i]; 
  copy.height = image.height;
  copy.data = 
    new unsigned char[copy.width*copy.height*4];
    
              for(int l=0;l<image.height;l++)
              for(int m=idxArr[i];m<=idxArr[i+1];m++)
              {
        copy.data[ 4*l*copy.width + 4*(m-idxArr[i]) + 0 ] 
                                                = image.data[4*l*image.width + 4*m + 0]; 
        copy.data[ 4*l*copy.width + 4*(m-idxArr[i]) + 1 ] 
                                                = image.data[4*l*image.width + 4*m + 1]; 
        copy.data[ 4*l*copy.width + 4*(m-idxArr[i])  + 2 ] 
                                                = image.data[4*l*image.width + 4*m + 2]; 
        copy.data[ 4*l*copy.width + 4*(m-idxArr[i]) + 3 ] 
                                                = image.data[4*l*image.width + 4*m + 3];  
              }
              
              
    char c[32];
    word++;
    sprintf(c,"Word=%d.png",word);
    mPng::write(c,copy);
    
      }


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
