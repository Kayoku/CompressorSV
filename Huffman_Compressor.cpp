#include "Huffman_Compressor.h"
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#include <iterator>

////////////////////////////////////////////////////////////////////////////
void generate_bools 
////////////////////////////////////////////////////////////////////////////
(
 const Node* node,
 const std::vector<bool>& prefix,
 std::map<int, std::vector<bool>>& out_codes
)
{
 if (const Leaf_Node* lf = dynamic_cast<const Leaf_Node*>(node))
  out_codes[lf->character] = prefix;
 else if (const Parent_Node* in = dynamic_cast<const Parent_Node*>(node))
 {
  std::vector<bool> left_prefix = prefix;
  left_prefix.push_back(false);
  generate_bools(in->left, left_prefix, out_codes);

  std::vector<bool> right_prefix = prefix;
  right_prefix.push_back(true);
  generate_bools(in->right, right_prefix, out_codes);
 }
}

////////////////////////////////////////////////////////////////////////////
void Huffman_Compressor::compress()
////////////////////////////////////////////////////////////////////////////
{
 std::string line;
 char buffer;
 std::map<int, unsigned long> frequencies;
 std::vector<std::pair<int, unsigned long>> sorted_frequencies;

 // Calcul des fréquences de chaque chaines
 for (int i = 0 ; i < 256 ; i++)
  frequencies[i] = 0;

 while(in.read(&buffer, sizeof(buffer)))
  frequencies[(uint8_t)buffer]++;

 for (int i = 0 ; i < (int)frequencies.size() ; i++)
  sorted_frequencies.push_back(std::pair<int, unsigned long>(i, frequencies[i]));

 std::sort(sorted_frequencies.begin(),
           sorted_frequencies.end(),
           [&] (const std::pair<int, unsigned long> &first,
                const std::pair<int, unsigned long> &second)
           { return first.second < second.second; }); 

 for (int i = 0 ; i < (int)sorted_frequencies.size() ; i++)
  std::cout << i << " " << sorted_frequencies[i].first << " "
                        << sorted_frequencies[i].second << std::endl;

 in.clear();
 in.seekg(0);

 // Création de l'arbre
 std::priority_queue<Node*, std::vector<Node*>, Node_Compare> queue; 

 for (int i = 0 ; i < (int)sorted_frequencies.size() ; i++)
  if (sorted_frequencies[i].second > 0)
   queue.push(new Leaf_Node(sorted_frequencies[i].second,
                           sorted_frequencies[i].first));

 while (queue.size() > 1)
 {
  Node* child_right = queue.top();
  queue.pop();

  Node* child_left = queue.top();
  queue.pop();

  Node* parent = new Parent_Node(child_right, child_left);
  queue.push(parent);
 }

 std::map<int, std::vector<bool>> codes;
 generate_bools(queue.top(), std::vector<bool>(), codes);
 queue.pop();

 // Ecriture de l'arbre
 

 // utilisation de l'arbre
 std::vector<bool> inter_bool;
 short cpt = 0;
 uint8_t buffer_out = 0x00;

 while(in.read(&buffer, sizeof(buffer)))
 {
  inter_bool = codes[(uint8_t)buffer];
  std::reverse(inter_bool.begin(), inter_bool.end());

  while (!inter_bool.empty())
  {
   buffer_out <<= 1;
   buffer_out |= inter_bool.back();
   inter_bool.pop_back();
   cpt++;

   if (cpt == 7)
   { 
    cpt = 0;
    out << buffer_out; 
    buffer_out = 0x00;
   } 
  }
 }

 if (cpt > 0)
  out << buffer_out;
}

////////////////////////////////////////////////////////////////////////////
void Huffman_Compressor::uncompress()
////////////////////////////////////////////////////////////////////////////
{

}
