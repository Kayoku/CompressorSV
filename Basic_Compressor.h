#ifndef BASIC_COMPRESSOR_DEFINE
#define BASIC_COMPRESSOR_DEFINE

#include "Compressor.h"

class Basic_Compressor: public Compressor
{
 private:

 public:
  Basic_Compressor(std::istream &in, std::ostream &out):
   Compressor(in, out)
   {}

  void compress() override;
  void uncompress() override;
};

#endif
