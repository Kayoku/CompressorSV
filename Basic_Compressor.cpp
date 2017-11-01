#include "Basic_Compressor.h"
#include "acgt_biblio.h"

////////////////////////////////////////////////////////////////////////////
void Basic_Compressor::compress()
////////////////////////////////////////////////////////////////////////////
{
 std::string line;
 uint8_t buffer;
 short cpt;

 while (std::getline(in, line))
 {
  cpt = 0;
  buffer = 0x00;

  uint16_t size = line.size();
  
  out << (uint8_t)(size & 0x00FF) << (uint8_t)(size >> 8);

  for (char c : line)
  {
   buffer = add_nucleotide(buffer, c);
   cpt++;

   if (cpt == 4)
   {
    cpt = 0;
    out << buffer;
    buffer = 0x00;
   }
  }

  if (cpt > 0)
   out << buffer;
 }
}

////////////////////////////////////////////////////////////////////////////
void Basic_Compressor::uncompress()
////////////////////////////////////////////////////////////////////////////
{
 std::string line;
 char buffer;
 char size_buffer[2];
 uint16_t size = 0;
 int rest = 0;

 while (in.read(&size_buffer[0],sizeof(size_buffer)))
 {
  // Conversion size_buffer -> size uint16
  size = (size_buffer[1] << 8) + (uint8_t)size_buffer[0];

  // Calcul nb de byte à lire
  int nb_buffer_char = ((int)size)/4;
  rest = (int)size%4;
  if (rest > 0)
   nb_buffer_char++;

  // On lit chaque octet
  std::string new_byte = "";
  for (int i = 0 ; i < nb_buffer_char ; i++)
  {
   in.read(&buffer, sizeof(buffer));
   if (i == nb_buffer_char-1 && rest > 0)
    new_byte += read_byte_acgt(buffer, rest);
   else
    new_byte += read_byte_acgt(buffer); 
  }

  out << new_byte;
  out << '\n';
 }
}
