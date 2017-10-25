#include "Basic_Compressor.h"
#include "acgt_biblio.h"

////////////////////////////////////////////////////////////////////////////
void Basic_Compressor::compress()
////////////////////////////////////////////////////////////////////////////
{
 std::string line;
 uint8_t buffer;
 short cpt;

 while (std::getline(std::cin, line))
 {
  cpt = 0;
  buffer = 0x00;

  out << (uint16_t)line.size();

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
 uint16_t size = 0;

 while (std::cin >> size)
 {
  // Calcul nb de byte à lire
  int nb_buffer_char = ((int)size)/4;
  if (((int)size)%4 > 0)
   nb_buffer_char++;

  // On lit chaque octet, pour le dernier, on enlève les nucléotides
  // qui n'existe pas
  std::string new_byte = "";
  for (int i = 0 ; i < nb_buffer_char ; i++)
  {
   std::cin >> buffer;
   new_byte += read_byte_acgt((uint8_t)buffer); 
  }

  if (((int)size)%4 > 0)
   for (int i = 0 ; i < ((int)size)%4 ; i++)
    new_byte.pop_back();

  out << new_byte;
  out << '\n';
 }
}
