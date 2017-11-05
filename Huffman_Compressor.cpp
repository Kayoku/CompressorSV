#include "Huffman_Compressor.h"
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#include <iterator>

 
typedef std::vector<bool> HuffCode;
typedef std::map<int, HuffCode> HuffCodeMap;
void GenerateCodes(const Node* node, const HuffCode& prefix, HuffCodeMap& outCodes)
{
    if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
    {
        outCodes[lf->character] = prefix;
    }
    else if (const ParentNode* in = dynamic_cast<const ParentNode*>(node))
    {
        HuffCode leftPrefix = prefix;
        leftPrefix.push_back(false);
        GenerateCodes(in->left, leftPrefix, outCodes);
 
        HuffCode rightPrefix = prefix;
        rightPrefix.push_back(true);
        GenerateCodes(in->right, rightPrefix, outCodes);
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
 std::priority_queue<Node*, std::vector<Node*>, NodeCompare> queue; 

 for (int i = 0 ; i < (int)sorted_frequencies.size() ; i++)
  if (sorted_frequencies[i].second > 0)
   queue.push(new LeafNode(sorted_frequencies[i].second,
                           sorted_frequencies[i].first));

 while (queue.size() > 1)
 {
  Node* child_right = queue.top();
  queue.pop();

  Node* child_left = queue.top();
  queue.pop();

  Node* parent = new ParentNode(child_right, child_left);
  queue.push(parent);
 }

 std::cout << queue.top()->depth << std::endl;
 HuffCodeMap codes;
 GenerateCodes(queue.top(), HuffCode(), codes);
 queue.pop();

 for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it)
 {
  std::cout << it->first << " ";
  std::copy(it->second.begin(), it->second.end(),
            std::ostream_iterator<bool>(std::cout));
  std::cout << std::endl;
 }

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

 out << buffer_out;
}

////////////////////////////////////////////////////////////////////////////
void Huffman_Compressor::uncompress()
////////////////////////////////////////////////////////////////////////////
{

}
