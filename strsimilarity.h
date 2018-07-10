#ifndef STRSIMILARITY_H_INCLUDED
#define STRSIMILARITY_H_INCLUDED

#include "general.h"
#include "str.h"

#include <vector>

immutable_struct StrSimMatch {
    const unsigned pos;
    const int score;
    const Str cigar;
    StrSimMatch(unsigned pos, int score, const Str& cigar): pos(pos), score(score), cigar(cigar) {}
    inline bool isEmpty() const { return cigar.isEmpty(); }

    friend std::ostream& operator<<(std::ostream& os, const StrSimMatch& ssm);
};

immutable_struct StrSimilarity {
private:
    int** table;              // scoring matrix
    unsigned* ch2ind;         // ch2col[c] = ind of table row/column corresponding to c
    unsigned activeChars;     // dim(ch2ind) = dim(table) = activeChars + 2 (one for gap, one or all other characters)
public:
    StrSimilarity(std::vector<char> alphabet, int** table);
    StrSimilarity(int** table, unsigned* ch2ind, unsigned activeChars):
        table(table), ch2ind(ch2ind), activeChars(activeChars) {}
    ~StrSimilarity() { destroy(); }
    StrSimMatch occurence(const Str& pattern, const Str& str, unsigned basePos = 0) const;
    void destroy();
private:
    inline int get(char ch1, char ch2) const { return table[ch2ind[(byte)ch1]][ch2ind[(byte)ch2]]; }
    inline int gap(char ch) const { return table[ch2ind[(byte)ch]][activeChars]; }
public:
    static StrSimilarity defaulStrSim();
};

#endif // STRSIMILARITY_H_INCLUDED
