#ifndef FASTA_H_INCLUDED
#define FASTA_H_INCLUDED

#include "str.h"
#include "general.h"

// utility class for working with fasta files
utility_class Fasta {
public:
    static Str read(const char* filePath);
};

#endif // FASTA_H_INCLUDED
