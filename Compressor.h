#ifndef COMPRESSOR_DEFINE
#define COMPRESSOR_DEFINE

#include <iostream>

class Compressor
{
 protected:
  std::istream &in;
  std::ostream &out;

 public:
  Compressor(std::istream& in, std::ostream& out):
   in(in),
   out(out)
  {}

  virtual ~Compressor() {}
  virtual void compress() = 0;
  virtual void uncompress() = 0;
};

#endif
