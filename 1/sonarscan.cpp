#include<iostream>
#include<string>
#include<fstream>

using std::string;
using std::cout; using std::endl;
using std::fstream;

fstream& ParseDepths(fstream& In, int32_t& Count)
{
  int32_t Depth;
  int32_t PreviousDepth = -1;
  while(In >> Depth)
  {
    if(Depth > PreviousDepth) { Count++; }
    PreviousDepth = Depth;
  }
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
