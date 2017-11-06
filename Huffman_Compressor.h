#ifndef HUFFMAN_COMPRESSOR_DEFINE
#define HUFFMAN_COMPRESSOR_DEFINE  

#include "Compressor.h"

class Node
{
 public:
  const unsigned long value;
  int depth;

  Node(unsigned long value, int depth):
   value(value),
   depth(depth)
  {}
  virtual ~Node() {}
};

class Leaf_Node : public Node
{
 public:
  const uint8_t character;

  Leaf_Node(unsigned long value, uint8_t character): 
   Node(value, 0),
   character(character)
  {}
};

class Parent_Node : public Node
{
 public:
  Node const* left;
  Node const* right;

  Parent_Node(Node* n1, Node* n2):
   Node(n1->value + n2->value, (n1->depth > n2->depth)? n1->depth+1 : n2->depth+1), 
   left(n1),
   right(n2)
  {}

  ~Parent_Node()
  {
   delete left;
   delete right;
  }
};

struct Node_Compare
{
 bool operator()(const Node* first, const Node* second) const
  { return first->value > second->value; }
};

class Huffman_Compressor : public Compressor
{
 private:

 public:
  Huffman_Compressor(std::ifstream &in, std::ofstream &out):
   Compressor(in, out)
  {}

  void compress() override;
  void uncompress() override;
};

#endif
