#ifndef LZ77_COMPRESSOR_DEFINE
#define LZ77_COMPRESSOR_DEFINE

#include "Compressor.h"
#include <math.h>

class LZ77_Compressor : public Compressor
{
 private:
  int size_search_buffer;
  int nb_bit_search_buffer;
  int size_look_ahead_buffer;
  int nb_bit_look_ahead_buffer;
  int nb_bytes;
 
 public:
  LZ77_Compressor(int nb_bytes,
                  int nb_bit_search_buffer,
                  int nb_bit_look_ahead_buffer,
                  std::ifstream &in,
                  std::ofstream &out):
   Compressor(in,out),
   nb_bit_search_buffer(nb_bit_search_buffer),
   nb_bit_look_ahead_buffer(nb_bit_look_ahead_buffer),
   nb_bytes(nb_bytes)
  {
   size_search_buffer = pow(2, nb_bit_search_buffer);
   size_look_ahead_buffer = pow(2, nb_bit_look_ahead_buffer);

   // 1 octet
   if (nb_bytes == 1)
   {
    if (size_look_ahead_buffer * size_search_buffer != 64)
    {
     std::cerr << "Bad combination for buffer size." << std::endl;
     exit(-1);
    }
   }
   // 2 octets
   else if (nb_bytes == 2)
   {
    if (size_look_ahead_buffer * size_search_buffer != 16384)
    {
     std::cerr << "Bad combination for buffer size." << std::endl;
     exit(-1);
    }
   }
   // Erreur
   else
   {
    std::cerr << "Can't create a LZ77 compressor for more than 2 bytes." << std::endl;
    exit(-1);
   }

   size_search_buffer--;
   size_look_ahead_buffer--;
  }

  void compress() override;
  void uncompress() override;
};

#endif
