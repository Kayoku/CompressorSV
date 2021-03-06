#include "acgt_biblio.h"
#include <string>

////////////////////////////////////////////////////////////////////////////
std::string read_byte_acgt
////////////////////////////////////////////////////////////////////////////
(
 uint8_t byte,
 short nb_carac
)
{
 std::string s;

 for (int i = 4 - nb_carac ; i < 4 ; i++)
 {
  uint8_t buffer = (byte >> 2*(3-i)) & 0x03;
  if ((int)buffer == 0)
   s += 'A';
  else if ((int)buffer == 1)
   s += 'C';
  else if ((int)buffer == 2)
   s += 'G';
  else
   s += 'T';
 }

 return s;
}

////////////////////////////////////////////////////////////////////////////
uint8_t add_nucleotide
////////////////////////////////////////////////////////////////////////////
(
 uint8_t byte,
 char c
)
{
 byte = byte << 2;

 if (c == 'A')
  byte = byte | 0x0;
 else if (c == 'C')
  byte = byte | 0x1;
 else if (c == 'G')
  byte = byte | 0x2;
 else
  byte = byte | 0x3;

 return byte;
}

////////////////////////////////////////////////////////////////////////////
uint8_t char_to_nucleotide
////////////////////////////////////////////////////////////////////////////
(
 char c
)
{
 if (c == 'A')
  return 0x0;
 else if (c == 'C')
  return 0x1;
 else if (c == 'G')
  return 0x2;
 else
  return 0x3;
}

////////////////////////////////////////////////////////////////////////////
char nucleotide_to_char
////////////////////////////////////////////////////////////////////////////
(
 uint8_t byte
)
{
 if (byte == 0x0)
  return 'A';
 else if (byte == 0x1)
  return 'C';
 else if (byte == 0x2)
  return 'G';
 else
  return 'T';
}
