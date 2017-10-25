#ifndef acgt_biblio_define
#define acgt_biblio_define

#include <iostream>

/*
A : 0x0
C : 0x1
G : 0x2
T : 0x3
*/

std::string read_byte_acgt(uint8_t byte, short nb_carac = 4);
uint8_t add_nucleotide(uint8_t byte, char c);

#endif
