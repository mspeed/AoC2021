#include<fstream>
#include<iostream>
#include<string>
#include<utility>
#include<tuple>

using std::ifstream;
using std::cout; using std::endl; using std::cerr;
using std::string;
using std::pair; using std::tuple; using std::get; using std::make_tuple;

using Position = tuple<uint32_t, uint32_t, uint32_t>;
using Command = pair<string, uint32_t>;

enum ePosition
{
  HORI,
  VERT,
  AIM,
};

ifstream& ParseCommands(ifstream& fs, Position& pos)
{
  Command cmd;
  while(fs >> cmd.first >> cmd.second)
  {
          if(!cmd.first.compare(string("forward"))) { get<HORI>(pos)  += cmd.second; get<VERT>(pos) += cmd.second * get<AIM>(pos);  }
    else  if(!cmd.first.compare(string("up")))      { get<AIM>(pos)   -= cmd.second;                                                }
    else  if(!cmd.first.compare(string("down")))    { get<AIM>(pos)   += cmd.second;                                                }
  }
}

int main(int argc, char * argv[])
{
  if(2 != argc){ cout << "Usage: " << argv[0] << "<inputfile>" << endl; }
  ifstream fs(argv[1]);

  if(!fs.is_open()){ cerr << "Error opening file. " << endl; }

  Position pos = make_tuple(0, 0, 0);
  ParseCommands(fs, pos);

  cout << "Horiz * Vert = " << get<HORI>(pos) * get<VERT>(pos) << endl;

  return 0;
}
