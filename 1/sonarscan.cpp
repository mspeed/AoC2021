#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using std::string;
using std::cout; using std::endl;
using std::fstream;
using std::vector; using std::next;

int32_t ThreeTapSMA(int32_t const& Input)
{
  static int32_t x1 = 0;
  static int32_t x2 = 0;

  int32_t const Output = Input + x1 + x2;

  x2 = x1; x1 = Input;
  //return (x1 && x2 ) ? Output : -1;
  return Output;
}

template<typename T>
uint32_t CountIncreases(vector<T> const& Values)
{
  uint32_t Count = 0;
  cout << "Size: " << Values.size() << endl;
  for(typename vector<T>::const_iterator  it = Values.begin();
                                  (it != Values.end()) && (next(it) != Values.end());
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

  string const InputFilename(argv[1]);

  //int32_t IncreaseCount = -1;

  fstream fs(InputFilename);

  vector<uint32_t> Depths;

  //ParseDepths(fs, Depths);

  cout << "Increase count: " << CountIncreases(ParseDepths(fs, Depths)) << endl;

}
