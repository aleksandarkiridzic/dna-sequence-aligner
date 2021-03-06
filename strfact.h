#ifndef STRFACT_H_INCLUDED
#define STRFACT_H_INCLUDED

#include "str.h"
#include "fmstr.h"

#include <iostream>

// utility class for advanced string creation
class StrFact {
public:
    // create suffix array - O(n * log^2(n))
    static int constructSuffixArray(const Str& str, unsigned*& sufArr);
    // create Burrows�Wheeler transform of a string given its suffix array
    // if not given, suffix array is created and returned through reference parameter
    static Str bwt(Str& str, unsigned*& sufArr, bool keepOriginal = true);
    // create fully fm-indexed string
    static FMStr constructFMStr(Str& str, unsigned sufArrStep = 1, unsigned checkpointStep = 1);
    // run-length encoding
    static Str rlEncode(Str& str, bool keepOriginal = true);
    // inverse
    static Str inverse(Str& str, bool keepOriginal = true);
private:
    struct Suffix {
        static unsigned genInd;
        unsigned index = genInd++;  // index of suffix's first char
        unsigned rankHigh = 0;      // high priority part of rank
        unsigned rankLow = 0;       // low priority part of rank
        bool operator<(const Suffix& s) const;
        bool operator==(const Suffix& s) const;
        inline static void resetInd() { genInd = 0; }
    };
};

#endif // STRFACT_H_INCLUDED
