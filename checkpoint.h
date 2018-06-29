#ifndef CHECKPOINT_H_INCLUDED
#define CHECKPOINT_H_INCLUDED

#include "fmstr.h"
#include "range.h"

immutable_class Checkpoint {
private:
    const FMStr& fmstr;           // corresponding string
    const unsigned** table;     // table[r][c] = number of occurrences of c in prefix str(r * 2 ^ logStep)
    const int* ch2col;          // ch2col[c] = column of table corresponding to c
    const unsigned* limits;     // limits[c] =
    unsigned logStep;           // shift step when sparse, 0 when not
    unsigned sparseMask;        // mask for checking if the value is held; step = sparseMask + 1
    unsigned activeChars;       // number of distinct character in the string
public:
    Checkpoint(const FMStr& fmstr, unsigned step = 1);
    ~Checkpoint() { destroy(); };
    Range range(const Range& range, char ch) const; // range in F string of all occurrences of ch in the given range in L string
    Range rangeAll(char ch) const;                  // range in F string of all occurrences of ch
    inline unsigned length() const { return (fmstr.len >> logStep) + 1; }
    void destroy();
private:

};

#endif // CHECKPOINT_H_INCLUDED
