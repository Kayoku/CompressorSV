#include <iostream>
#include <fstream>

int main ()
{
 /*
  * Ignorer 1 lignes
  * Prendre la ligne suivante, et l'écrire dans un fichier
  * Ignorer 2 lignes
  * boucler
  */

 std::string line;
 std::ofstream file("sequence-base.acgt");

 if (!file.good())
 {
  std::cerr << "Fichier non créé." << std::endl;
  return -1;
 }

 while (std::getline(std::cin, line))
 {
  std::getline(std::cin, line);
 
  file << line << '\n';

  std::getline(std::cin, line);
  std::getline(std::cin, line);
 }

 return 0;
}
