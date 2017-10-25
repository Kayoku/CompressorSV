#include <iostream>
#include <fstream>

int main (int argc, char *argv[])
{
 /*
  * Ignorer 1 lignes
  * Prendre la ligne suivante, et l'écrire dans un fichier
  * Ignorer 2 lignes
  * boucler
  */

 std::string line;

 for (int i = 0 ; i < 10000 ; i++)
  for (int j = 0 ; j < 4 ; j++)
   std::getline(std::cin, line);

 for (int i = 0 ; i < 100 ; i++)
 {
  std::getline(std::cin, line);
  std::getline(std::cin, line);
 
  std::ofstream file("../../sequences/seq"+std::to_string(i)+".txt");
  if (file.good())
  {
   file << line;

   std::cout << "New file !\n";
   std::getline(std::cin, line);
   std::getline(std::cin, line);
  }
  else
   std::cout << "No new file !\n"; 
 }

 return 0;
}
