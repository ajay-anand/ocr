#include <vector>
using std::vector;
#include <iostream>
using std::cout;

/*
v is vector of fitness value vector for each template-character. Each character's fitness value vector has size equal to wordWidth. charWidth is average char width.
*/
void getPeaks( const vector < vector <float> >& v , const vector <int>& templateWidth, const int& wordWidth, const int& charWidth, vector <int>& index, vector <int>& position );
/*
int main()
{
  const int M = 3;//number of characters
  const int N = 12;//wordWidth
  const int charWidth = 2;
  
  double fitness[M][N] = { {4,3,2,1,0,0,0,0,0,0,0,0},
                           {0,0,0,1,0,1,2,3,4,3,2,1},
                           {0,1,2,3,4,3,2,1,0,0,0,0} };
  int templateWidthData[M] = {4,4,4};
  vector < vector < double > > vec;
  vector <int> templateWidth;
  int i,j;
  for( i = 0; i < M; ++i )
  {
    vector <double> v;
    for( j = 0; j < N; ++j ) v.push_back( fitness[i][j] );
    vec.push_back(v);
  } 
  for( i = 0; i < M; ++i ) templateWidth.push_back( templateWidthData[i] );
  
  vector <int> index, position;
  getPeaks( vec, templateWidth, N, 2, index, position);
  for( i = 0; i < index.size(); ++i ) cout << index[i] << " at " << position[i] << "\n";
  return 0;
}
*/