#include <iostream>
#include <cstddef>
#include <fstream>

#include "Compressor.h"
#include "Basic_Compressor.h"

/*
A : 00
C : 01
G : 10
T : 11
*/

int main (int argc, char *argv[])
{
 // Erreur si pas le bon nombre d'arguments
 if (argc != 3)
 {
  std::cerr << "./compressor <compress/uncompress> <basic>" << std::endl;
  return -1;
 }

 // Récupère si compression ou décompression
 bool compress;
 if (std::string(argv[1]) == "compress")
  compress = true;
 else if (std::string(argv[1]) == "uncompress")
  compress = false;
 else
 {
  std::cerr << "compress or uncompress are the only choice possible." << std::endl;
  return -1;
 }

 // Création du fichier de sortie
 std::string algo = argv[2]; 
 std::ofstream compress_file(std::string((compress) ? "" : "un")+"compress_file."+algo);
 if (!compress_file.good())
 {
  std::cerr << "Can't create file." << std::endl;
  return -1;
 }

 // Choix de l'algo
 Compressor* compressor;
 if (algo == "basic")
  compressor = new Basic_Compressor(std::cin, compress_file); 
 else
 {
  std::cerr << "Algo doesn't exist." << std::endl;
  return -1;
 }

 // Process
 if (compress)
  compressor->compress();
 else
  compressor->uncompress();

 delete compressor; 
 return 0;
}
