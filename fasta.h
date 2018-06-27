#ifndef FASTA_H_INCLUDED
#define FASTA_H_INCLUDED

#include "str.h"

// utility class for working with fasta files
class Fasta {
public:
    static Str read(const char* filePath);
};

#endif // FASTA_H_INCLUDED
