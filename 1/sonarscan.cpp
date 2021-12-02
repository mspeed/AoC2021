#include<iostream>
#include<string>
#include<fstream>

using std::string;
using std::cout; using std::endl;
using std::fstream;

int32_t ThreeTapSMA(int32_t const& Input)
{
  static int32_t x1 = 0;
  static int32_t x2 = 0;

  int32_t const Output = Input + x1 + x2;

  x2 = x1; x1 = Input;
  //return (x1 && x2 ) ? Output : -1;
  return Output;
}

fstream& ParseDepths(fstream& In, int32_t& Count)
{
  int32_t Depth;
  int32_t PreviousDepth = -1;
  int32_t PreFill = -2;
  while(In >> Depth)
  {
    Depth = ThreeTapSMA(Depth);
    if(PreFill < 0){ PreFill++; continue; }
    if(Depth > PreviousDepth) { Count++; }
    PreviousDepth = Depth;
  }
  return In;
}

int main(int argc, char * argv[])
{
  if(argc != 2){ cout << "Usage: " << argv[0] << " <filename>" << endl; }

  string const InputFilename(argv[1]);

  int32_t IncreaseCount = -1;

  fstream fs(InputFilename);

  ParseDepths(fs, IncreaseCount);

  cout << "Increase count: " << IncreaseCount << endl;

}
