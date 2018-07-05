#ifndef FASTQ_H_INCLUDED
#define FASTQ_H_INCLUDED

#include "read.h"
#include "general.h"

#include <vector>

// utility class for working with fastq files
utility_class Fastq {
private:
    enum ReaderState { ID, SEQ, PLUS, QUAL };
public:
    static std::vector<Read> read(const char* filePath);

};

#endif // FASTQ_H_INCLUDED
