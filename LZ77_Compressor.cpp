#include "LZ77_Compressor.h"
#include "acgt_biblio.h"
#include <vector>
#include <sstream>
#include <bitset>

////////////////////////////////////////////////////////////////////////////
void LZ77_Compressor::compress()
////////////////////////////////////////////////////////////////////////////
{
 std::string line;
 int next_slide = 1;
 char buffer_char;
 std::string search_buffer;
 std::string look_ahead_buffer;
 int size_ss_line = 0;

 while (std::getline(in, line))
 {
  size_ss_line = 0;
  std::stringstream ss_line(line);

  // On écrit la taille de la ligne
  uint16_t line_size = line.size();
  out << (uint8_t)(line_size & 0x00FF) << (uint8_t)(line_size >> 8);

  do
  {
   // On remplit la queue look_ahead jusqu'à ce qu'elle est la bonne taille
   while ((int)look_ahead_buffer.size() < size_look_ahead_buffer &&
          ss_line >> buffer_char)
   {
    size_ss_line++;
    look_ahead_buffer += buffer_char;
   }
 
   // On cherche la plus grande chaine de look_ahead_buffer contenu dans
   // search_buffer en formant des chaines débutant toujours au début de
   // look_ahead_buffer
   std::string inter;
   int max_length = 0;
   inter += look_ahead_buffer[max_length]; 
   while (search_buffer.find(inter) != std::string::npos &&
          max_length+1 < (int)look_ahead_buffer.size())
   {
    max_length++;
    inter += look_ahead_buffer[max_length];
   }
  
   // Si max_length = 0, pas de corespondance
   // Si max_length > 0 : correspondance
   // -> inter.pop_back
   // -> find inter
   // -> distance : size - pos inter
   // -> longueur : size de inter
   uint16_t u_distance = 0x0000;
   uint16_t u_length = 0x0000;
   uint8_t u_letter = char_to_nucleotide((char)inter[inter.size()-1]);

   if (max_length == 0)
    next_slide = 1;
   else
   {
    auto inter_less1 = inter;
    inter_less1.pop_back();
    auto pos_string = search_buffer.find(inter_less1);
    int distance = (int)search_buffer.size() - pos_string;
    int length = (int)inter.size();
    u_distance = distance;
    u_length = length-1;
    next_slide = length;
   }

   // On écrit selon le nb d'octets
   if (nb_bytes == 1)
   {
    uint8_t to_write = 0x00;
    to_write |= u_distance;
    to_write <<= nb_bit_look_ahead_buffer;
    to_write |= u_length;
    to_write <<= 2;
    to_write |= u_letter;
    out << to_write;
   }
   else
   {
    uint16_t to_write = 0x0000;
    to_write |= u_distance;
    to_write <<= nb_bit_look_ahead_buffer;
    to_write |= u_length;
    to_write <<= 2;
    to_write |= u_letter;
    out << (uint8_t)(to_write & 0x00FF) << (uint8_t)(to_write >> 8);
   }
 
   // On décale dans le search_buffer avec le slide
   search_buffer.insert(search_buffer.end(),
                        look_ahead_buffer.begin(), 
                        look_ahead_buffer.begin()+next_slide);
 
   if ((int)search_buffer.size() > size_search_buffer)
   {
    int diff = (int)search_buffer.size() - size_search_buffer;
    search_buffer.erase(0, diff);
   }
 
   look_ahead_buffer.erase(0, next_slide);
 
  } while ((int)look_ahead_buffer.size() > 0 || (!ss_line.eof() && size_ss_line != (int)ss_line.str().size()));
 }
}


////////////////////////////////////////////////////////////////////////////
void LZ77_Compressor::uncompress()
////////////////////////////////////////////////////////////////////////////
{
 std::string line;
 char size_buffer[2];
 char buffer;
 char buffer2[2];
 uint16_t size = 0;
 int distance = 0;
 int length = 0;
 char letter = 0;
 std::string search_buffer;
 int kk = 0;

 while (in.read(&size_buffer[0], sizeof(size_buffer)))
 {
  kk++;
  line = "";

  // Conversion size_buffer -> size uint16
  size = (size_buffer[1] << 8) + (uint8_t)size_buffer[0];

  while (line.size() < size)
  {
   if (nb_bytes == 1)
   {
    in.read(&buffer, sizeof(buffer)); 
    uint8_t u_buffer = buffer;
    letter = nucleotide_to_char((u_buffer & 0x3));
    u_buffer >>= 2;
    length = (int)(u_buffer & ~(~0 << nb_bit_look_ahead_buffer));
    u_buffer >>= nb_bit_look_ahead_buffer;
    distance = (int)(u_buffer & ~(~0 << nb_bit_search_buffer));
   }
   else
   {
    in.read(&buffer2[0], sizeof(buffer2));
    uint16_t u_buffer = (buffer2[1] << 8);
    u_buffer |= (uint8_t)buffer2[0]; 
    letter = nucleotide_to_char((u_buffer & 0x3));
    u_buffer >>= 2;
    length = (int)(u_buffer & ~(~0 << nb_bit_look_ahead_buffer));
    u_buffer >>= nb_bit_look_ahead_buffer;
    distance = (int)(u_buffer & ~(~0 << nb_bit_search_buffer));
   }

   if (distance > 0)
   {
    int current_pos = search_buffer.size();
    for (int j = current_pos - distance ; j < (current_pos - distance) + length ; j++)
    {
     search_buffer += search_buffer[j];
     line += search_buffer[j];
    }
   }

   search_buffer += letter;
   line += letter;

   if ((int)search_buffer.size() > size_search_buffer)
   {
    int diff = (int)search_buffer.size() - size_search_buffer;
    search_buffer.erase(0, diff);
   }
  }
  out << line << '\n';
 }
}
