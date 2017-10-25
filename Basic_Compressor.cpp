#include "Basic_Compressor.h"

////////////////////////////////////////////////////////////////////////////
void Basic_Compressor::compress()
////////////////////////////////////////////////////////////////////////////
{
 std::string line;
 uint8_t buffer = 0x00;
 short cpt = 0;

 while (std::getline(std::cin, line))
 {
  out << (uint16_t)line.size();
  for (char c : line)
  {
   if (cpt == 4)
   {
    cpt = 0;
    out << buffer;
    buffer = 0x00;
   }

   // A C G T ?
   if (c == 'C')
    buffer = buffer | 0x01;
   else if (c == 'G')
    buffer = buffer | 0x02;
   else if (c == 'T')
    buffer = buffer | 0x03;
   buffer = buffer << 2;
   cpt++;
  }

  if (cpt == 1 || cpt == 2 || cpt == 3)
   out << buffer;
  cpt = 0;
  buffer = 0x00;
 }
}

////////////////////////////////////////////////////////////////////////////
void Basic_Compressor::uncompress()
////////////////////////////////////////////////////////////////////////////
{

}
