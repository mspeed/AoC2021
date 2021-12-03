#include<iostream>
#include<fstream>
#include<vector>

using std::cout; using std::endl; using std::cerr;
using std::fstream;
using std::vector; using std::next;

template<typename T, uint8_t TapCount>
vector<T>& SMA(vector<T>& Output, vector<T> const& Input)
{
  for(typename vector<T>::const_iterator  it = Input.begin();
                                          next(it, TapCount-1) != Input.end();
                                          ++it)
  {
    T Accu = 0;
    for(int i = 0; i < TapCount; i++)
    {
      Accu += *next(it, i);
    }
    Output.push_back(Accu);
  }
  return Output;
}

template<typename T>
uint32_t CountIncreases(vector<T> const& Values)
{
  uint32_t Count = 0;
  for(typename vector<T>::const_iterator  it = Values.begin();
                                          next(it) != Values.end();
                                          ++it)
  {
    if(*it < *next(it)){ Count++; }
  }
  return Count;
}

template<typename T>
vector<T>& ParseDepths(fstream& In, vector<T>& Depths)
{
  T Depth;
  while(In >> Depth) { Depths.push_back(Depth); }
  return Depths;
}

int main(int argc, char * argv[])
{
  if(argc != 2){ cout << "Usage: " << argv[0] << " <filename>" << endl; }

  fstream fs(argv[1]);
  if(!fs.is_open()){ cerr << "Failed to read file." << endl; return -1; }

  using depth_type = uint32_t;
  vector<depth_type> Depths;
  vector<depth_type> FilteredDepths;

  cout << "Increase count: " << CountIncreases(SMA<depth_type, 3>(FilteredDepths, ParseDepths(fs, Depths))) << endl;

  return 0;
}
