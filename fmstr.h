#ifndef FMSTR_H_INCLUDED
#define FMSTR_H_INCLUDED

#include "general.h"
#include "str.h"
#include "suffixarray.h"

immutable_class FMStr : Str {
private:
    const bool isPacked;            // is run-length encoded or in raw format
    const SuffixArray& sufArr;
    const Checkpoint& Checkpoint;

    friend class Checkpoint;
};

#endif // FMSTR_H_INCLUDED
