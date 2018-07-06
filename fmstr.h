#ifndef FMSTR_H_INCLUDED
#define FMSTR_H_INCLUDED

#include "general.h"
#include "str.h"
#include "suffixarray.h"
#include "checkpoint.h"

#include <vector>
#include <iostream>

immutable_class FMStr : public Str {
private:
    bool isPacked = false;   // is run-length encoded or in raw format
    SuffixArray sufArr;            // corresponding suffix array
    Checkpoint checkpoint;         // corresponding checkpoint tables
public:
    // constructed in factory due to preprocessing, here only assigned
    FMStr(const Str& str, const SuffixArray& sufArr, const Checkpoint& checkpoint);
    ~FMStr();
    std::vector<unsigned> allPos(const Str& str) const;
    Str inverse() const;
    void pack();
    void unpack();

    void info(std::ostream& os) const;
private:
    unsigned originalPos(unsigned index) const;   // position of F(index) in the original index

    friend class Checkpoint;
};

#endif // FMSTR_H_INCLUDED
