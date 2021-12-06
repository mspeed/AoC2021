#include<fstream>
#include<iostream>
#include<bitset>
#include<array>

using std::cout; using std::endl; using std::cerr;
using std::ifstream;
using std::array; using std::bitset;

#define numbits 12

uint16_t parse_binary(ifstream& fs, array<uint16_t, numbits>& bitcount)
{
  bitset<numbits> bs;
  uint16_t linecount = 0;
  while(fs >> bs)
  {
    for(int i = 0; i < numbits; i++)
    {
      bitcount[i] += bs[i];
    }
    linecount++;
  }
  return linecount;
}

bitset<numbits> gamma_rate(array<uint16_t, numbits> const& bitcount, uint16_t lines)
{
  bitset<numbits> bs;
  for(int i = 0; i < numbits; i++)
  {
    if(bitcount[i] > (lines >> 1)) bs.set(i);
  }
  return bs;
}

int main(int argc, char* argv[])
{
  if(2 != argc){ cout << "USAGE: " << argv[0] << " <filename>" << endl; return -1; }

 ifstream fs(argv[1]);
 if(!fs.is_open()){ cerr << "File error." << endl; return -1; }

 array<uint16_t, numbits> bcount {0};

 bitset<numbits> g_rate = gamma_rate(bcount, parse_binary(fs, bcount));
 bitset<numbits> e_rate ( (1 << numbits)-1 );

 e_rate ^= g_rate;

 cout << g_rate << endl << e_rate << endl;

 cout << "Power consumption: " << g_rate.to_ulong() * e_rate.to_ulong() << endl;

}
