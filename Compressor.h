#ifndef COMPRESSOR_DEFINE
#define COMPRESSOR_DEFINE

#include <iostream>
#include <fstream>

class Compressor
{
 protected:
  std::ifstream &in;
  std::ofstream &out;

 public:
  Compressor(std::ifstream& in, std::ofstream& out):
   in(in),
   out(out)
  {}

  virtual ~Compressor() {}
  virtual void compress() = 0;
  virtual void uncompress() = 0;
};

#endif
