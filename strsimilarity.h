#ifndef STRSIMILARITY_H_INCLUDED
#define STRSIMILARITY_H_INCLUDED

#include "general.h"
#include "str.h"

#include <vector>

immutable_struct StrSimMatch {
    const int pos;
    const int score;
    const Str cigar;
    StrSimMatch(int pos, int score, const Str& cigar): pos(pos), score(score), cigar(cigar) {}

    friend std::ostream& operator<<(std::ostream& os, const StrSimMatch& ssm);
};

immutable_struct StrSimilarity {
private:
    const int** table;              // scoring matrix
    const unsigned* ch2ind;         // ch2col[c] = ind of table row/column corresponding to c
    const unsigned activeChars;     // dim(ch2ind) = dim(table) = activeChars + 2 (one for gap, one or all other characters)
public:
    StrSimilarity(std::vector<char> alphabet, const int** table);
    StrSimMatch occurence(const Str& pattern, const Str& str);
private:
    inline int get(char ch1, char ch2) const { return table[ch2ind[(byte)ch1]][ch2ind[(byte)ch2]]; }
    inline int gap(char ch) const { return table[ch2ind[(byte)ch]][activeChars]; }
};

#endif // STRSIMILARITY_H_INCLUDED
