#include <iostream>
#include <cstddef>
#include <fstream>

#include "Compressor.h"
#include "Basic_Compressor.h"
#include "LZ77_Compressor.h"
#include "Huffman_Compressor.h"

/*
A : 00
C : 01
G : 10
T : 11
*/

int main (int argc, char *argv[])
{
 // Erreur si pas le bon nombre d'arguments
 if (argc != 4)
 {
  std::cerr << "./compressor <compress/uncompress> <basic/lz77-1/lz77-2/huffman> <nom_fichier>" << std::endl;
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

 // Création du fichier d'entrée
 std::string input_string = argv[3];
 std::ifstream input_file(input_string, std::ifstream::binary); 
 if (!input_file.good())
 {
  std::cerr << "File doesn't exist." << std::endl;
  return -1;
 }

 // Création du fichier de sortie
 std::string algo = argv[2]; 
 std::ofstream compress_file(std::string((compress) ? "" : "un")+"compress_file."+algo, std::ofstream::binary);
 if (!compress_file.good())
 {
  std::cerr << "Can't create file." << std::endl;
  return -1;
 }

 // Choix de l'algo
 Compressor* compressor;
 if (algo == "basic")
  compressor = new Basic_Compressor(input_file, compress_file); 
 else if (algo == "lz77-1")
  compressor = new LZ77_Compressor(1, 3, 3, input_file, compress_file);
 else if (algo == "lz77-2")
  compressor = new LZ77_Compressor(2, 9, 5, input_file, compress_file);
 else if (algo == "huffman")
  compressor = new Huffman_Compressor(input_file, compress_file);
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
