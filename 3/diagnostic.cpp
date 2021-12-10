#include<fstream>
#include<iostream>
#include<bitset>
#include<array>
#include<vector>

using std::cout; using std::endl; using std::cerr;
using std::ifstream;
using std::array; using std::bitset;
using std::vector;

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

uint16_t vector_to_bitcount(vector<bitset<numbits>> const& bitvec, array<uint16_t, numbits>& bitcount)
{
  for(vector<bitset<numbits>>::const_iterator it = bitvec.begin();
                                              it != bitvec.end();
                                              ++it)
                                              {
                                                  for(int i = 0; i < numbits; i++)
                                                  {
                                                    bitcount[i] += it->test(i);
                                                  }
                                              }
  return bitvec.size();
}

vector<bitset<numbits>>& parse_to_vector(ifstream& fs, vector<bitset<numbits>>& bitvec)
{
  bitset<numbits> bs;
  while(fs >> bs)
  {
    bitvec.push_back(bs);
  }
  return bitvec;
}

bitset<numbits> oxygen_generator_rating(vector<bitset<numbits>> bitmasks)
{
  uint8_t testposition = numbits - 1;
  while(bitmasks.size() > 1)
  {
    std::array<uint16_t, numbits> bitcount;
    uint16_t num_entries = vector_to_bitcount(bitmasks, bitcount);

    if(bitcount[testposition] > (num_entries>>1)) // Set.
    {



    }

  }

}

int main(int argc, char* argv[])
{
  if(2 != argc){ cout << "USAGE: " << argv[0] << " <filename>" << endl; return -1; }

 ifstream fs(argv[1]);
 if(!fs.is_open()){ cerr << "File error." << endl; return -1; }

 array<uint16_t, numbits> bcount {0}; /*< Count of each bit in the mask. */
 vector<bitset<numbits>> bitvec;      /*< The bitsets as read from the file. */

 bitset<numbits> g_rate = gamma_rate(bcount, vector_to_bitcount(parse_to_vector(fs, bitvec), bcount));
 bitset<numbits> e_rate = bitset<numbits>((1 << numbits)-1) ^ g_rate;

 cout << g_rate << endl << e_rate << endl;
 cout << "Power consumption: " << g_rate.to_ulong() * e_rate.to_ulong() << endl;




}
