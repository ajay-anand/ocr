/* 2>/dev/null
g++ om.cpp -o om -lpng peaks.a
exit
*/
#include "cluster/cluster.h"
#include "png/png.h"
#include "peaks.h"
#include<math.h>
#include<iostream>
#include <fstream>
#include<vector>
using namespace std;
#include<fstream>
using std::ofstream;
#include <stdlib.h>


const string alphabet[]={
      "\xe0\xac\x85",
      "\xe0\xac\x86",
      "\xe0\xac\x87",
      "\xe0\xac\x88",
      "\xe0\xac\x89",
      "\xe0\xac\x8a",
      "\xe0\xac\x8b",
      "\xe0\xac\x8f",
      "\xe0\xac\x90",
      "\xe0\xac\x93",
      "\x0a\xe0\xac\x94",
      "\xe0\xac\x95",
      "\xe0\xac\x96",
      "\x0a\xe0\xac\x97",
      "\xe0\xac\x98",
      "\xe0\xac\x99",
      "\xe0\xac\x9a",
      "\xe0\xac\x9b",
      "\xe0\xac\x9c",
      "\xe0\xac\x9d",
      "\xe0\xac\x9e",
      "\xe0\xac\x9f",
      "\xe0\xac\xa0",
      "\xe0\xac\xa1",
      "\xe0\xac\xa2",
      "\xe0\xac\xa3",
      "\xe0\xac\xa4",
      "\xe0\xac\xa5",
      "\xe0\xac\xa6",
      "\x0a\xe0\xac\xa7",
      "\xe0\xac\xa8",
      "\xe0\xac\xaa",
      "\xe0\xac\xab",
      "\xe0\xac\xac",
      "\xe0\xac\xad",
      "\xe0\xac\xae",
      "\xe0\xac\xaf",
      "",
      "\xe0\xac\xb0",
      "\x0a\xe0\xac\xb3",
      "\xe0\xac\xb2",
      "\xe0\xac\xb6",
      "\xe0\xac\xb7",
      "\xe0\xac\xb8", 
      "\xe0\xac\xb9",
      "\xe0\xac\xbe",
      "\xe0\xac\xbf",
      "\xe0\xad\x80",
      "\xe0\xad\x81",
      "\xe0\xad\x82",
      "\x0a\xe0\xad\x83",
      "\xe0\xad\x87",
      "\xe0\xad\x88",
      "\xe0\xad\x8b",
      "\xe0\xad\x8c"};
 

void findwords(string s,int lc);
void findletter (string c);

vector<float> v;
vector<float> v1;


void match( mPng::Image& wordImage, mPng::Image& templ,  vector < vector <float> >& fitness )
{
  int r,c,j,ki,kt,i;
  //int w = inw < tw? inw : tw;
  int sum=0;
  int th=templ.height;
  int tw=templ.width;
  vector <float> fv;
  for(i = 0; i < wordImage.width-templ.width; ++i )
  {
    sum = 0;
    for(r=0; r<th; r++)
    for(c=0; c<tw; c++)
    {
      kt=(int)getValue1(templ,r,c);
      ki=(int)getValue1(wordImage,r,c+i);
      sum=sum+(kt-127)*(ki-127);
    }

  fv.push_back(sum/(th*tw*128.0*128.0));

  }
  for( i = 0; i < templ.width; ++i )
  {
    sum = 0;
    for( r=0; r < th; r++ )
    for( c=0; c < templ.width-i; ++c )
    {
      kt=(int)getValue1(templ,r,c);
      ki=(int)getValue1(wordImage,r,c+i+wordImage.width-templ.width);
      sum=sum+(kt-127)*(ki-127);
    }
  fv.push_back(sum/(th*tw*128.0*128.0));
  }
    fitness.push_back(fv);
    
    cout << "1\n";

}



void countpixel(int arr[],int size)  //this function is for line detection
{
     int i=0;
     int flag=0,countblackpixel=0;
     for(i=0;i<size;i++)
     {
          if(arr[i]<250)
          {
                                         
              countblackpixel++;   
             
          }
                        
     }
     v.push_back(countblackpixel);
                                 
}
void countpixel1(int arr[],int size)
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
     v1.push_back(countblackpixel);                      
    cout << "2\n";

 }


 
 int main()
 {
   vector<int> idxArr;int lc=0;char c[50];
     
    mPng::Image image;
    mPng::read("ocrfinal.png",image);
    
    int width=image.width;
    int height=image.height;
    int arr[image.width];
    
    for(int i=0;i<image.height;i++)
    {
        for(int j=0;j<image.width;j++)
          {
             int k=(int)getValue1(image,i,j);
             arr[j]=k;
          }
      
      countpixel(arr,image.width);      
    }
    
    createTranstionArray(v, 2, idxArr );

  for(int i=0;i<idxArr.size();i=i+2)
  {
    mPng::Image copy;
    copy.width = image.width; 
    copy.height = idxArr[i+1]-idxArr[i]+1;
    copy.data = 
              new unsigned char[copy.width*copy.height*4];
     for(int l=idxArr[i];l<=idxArr[i+1];l++)
     for(int m=0;m<image.width;m++)
     {
        copy.data[ 4*(l-idxArr[i])*copy.width + 4*m + 0 ] 
                 = image.data[4*l*image.width + 4*m + 0]; 
        copy.data[ 4*(l-idxArr[i])*copy.width + 4*m + 1 ] 
                = image.data[4*l*image.width + 4*m + 1]; 
        copy.data[ 4*(l-idxArr[i])*copy.width + 4*m + 2 ] 
                 = image.data[4*l*image.width + 4*m + 2]; 
        copy.data[ 4*(l-idxArr[i])*copy.width + 4*m + 3 ] 
                = image.data[4*l*image.width + 4*m + 3];  
     }
                     
    lc++;
    sprintf(c,"Line=%d.png",lc);
    mPng::write(c,copy);
   findwords(c,lc);
  
   }
    cout << "3\n";
    return 0;
 }
 
 void findwords(string s,int lc)
{
    vector<int> idxArr1; int word=0; char c1[50];
    mPng::Image image;
    mPng::read(s,image);
    
    int width=image.width;
    int height=image.height;
    int arr[image.height];
    
    for(int j=0;j<image.width;j++)
    {
        for(int i=0;i<image.height;i++)
          {
             int k=(int)getValue1(image,i,j);
             arr[i]=k;
          }
      
      countpixel1(arr,image.height);      
    }
    createTranstionArray(v1, 1, idxArr1 );
    
    float avgCharWidth = 0;
    for(int i =0; i < idxArr1.size(); i+=2 ) avgCharWidth += (idxArr1[i+1]-idxArr1[i]);
    avgCharWidth /= (idxArr1.size()/2);
    
    cout<<"Before:"<<idxArr1.size();
    for(int i=0;i<idxArr1.size()-1;i++)
    {
         int temp=idxArr1[i+1]-idxArr1[i];
         if( temp <= (avgCharWidth/3))
        
        {
           idxArr1.erase(idxArr1.begin()+(i+1));
           idxArr1.erase(idxArr1.begin()+(i));
           i=i-2;                     
        } 
    }
    cout<<"After:"<<idxArr1.size()<<"\n";
         cout << s << "\n";
 for(int i=0;i<idxArr1.size();i=i+2)
  {
      mPng::Image copy1;
      copy1.width = idxArr1[i+1]-idxArr1[i]; 
      copy1.height = image.height;
      copy1.data = 
                   new unsigned char[copy1.width*copy1.height*4];
                   cout << copy1.width << " " << copy1.height << "\n";
      for(int l=0;l<image.height;l++)
      for(int m=idxArr1[i];m<idxArr1[i+1];m++)
      {
        copy1.data[ 4*l*copy1.width + 4*(m-idxArr1[i]) + 0 ] 
                                                = image.data[4*l*image.width + 4*m + 0]; 
        copy1.data[ 4*l*copy1.width + 4*(m-idxArr1[i]) + 1 ] 
                                                = image.data[4*l*image.width + 4*m + 1]; 
        copy1.data[ 4*l*copy1.width + 4*(m-idxArr1[i])  + 2 ] 
                                                = image.data[4*l*image.width + 4*m + 2]; 
        copy1.data[ 4*l*copy1.width + 4*(m-idxArr1[i]) + 3 ] 
                                                = image.data[4*l*image.width + 4*m + 3];  
      }
              
              
   
    word++;
    printf("Line=%dWord=%d.png",lc,word);
    sprintf(c1,"Line=%dWord=%d.png",lc,word);
    mPng::write(c1,copy1);
    findletter(c1);
    
  }
  v1.clear();idxArr1.clear();
ofstream ofile;
ofile.open("output.txt",  fstream::app);
ofile << "\r\n";
ofile.close();    
    cout << "4\n";

}



void findletter (string c)
{
     
     mPng::Image ink;
     mPng::read(c, ink);
     mPng::Image cropped;
     crop( ink, cropped );
     mPng::write("in.png", cropped);

 
     int inh=cropped.height;
     int inw=cropped.width;
     char d[100];
if(inw<=inh)
{
sprintf(d," gimp -i -b '(scale-to-max \"in.png\" \"output128.png\"  128)' -b '(gimp-quit 0)'");
system(d);
}
else
{
char c[200];
float temp=ceil(inw*128)/inh;
int a=(int)ceil(temp);
sprintf(c, "gimp -i -b '(scale-to-max \"in.png\" \"output128.png\" %d  )' -b '(gimp-quit 0)'" ,a);
system(c);
}
mPng::Image out128;
mPng::read("output128.png", out128);
vector < vector <float> > v;


vector <int> templateWidth;
int charWidth = 0;



for( int z=1 ; z<=45 ; z++ )
{
        mPng::Image t;
        cout<<z<<"\n";
char ca[60];
sprintf(ca,"1  (%d).png",z);
mPng::read(ca, t);

match(out128,t,v);
templateWidth.push_back(t.width);
charWidth += t.width;

}

charWidth /= 45;

//cout<<"CharWidth="<<charWidth<<"out128Width="<<out128.width<<"templateWidth Size="<<templateWidth.size()<<"v size="<<v.size();
vector <int> index;
vector <int> position;

//getPeaks( v , templateWidth, out128.width, charWidth, index, position );
//cout<<"\n"<<"index size="<<index.size()<<"position size="<<position.size();
int i;
ofstream ofile;
ofile.open("output.txt",  fstream::app);
for( i = 0; i < index.size(); ++i )
{
    cout << index[i]+1 << " at " << position[i] << "\n";
    ofile << alphabet[ index[i] ];
}
ofile << " ";
ofile.close();
    cout << "5\n";

 }


