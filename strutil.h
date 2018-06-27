#ifndef STRUTIL_H_INCLUDED
#define STRUTIL_H_INCLUDED

#include "str.h"

#include <iostream>

constexpr unsigned CHARSIZE_BITS = 8;
constexpr unsigned TOTAL_CHARS = 1 << (sizeof(char) * CHARSIZE_BITS);

// utility class for more advanced string functions
class StrUtil {
public:
    // sample few first and last chars of a string
    static void sample(Str& str, unsigned n, std::ostream& os);
    // textual histogram
    static void histogram(Str& str, std::ostream& os);
    // create suffix array - O(n * log^2(n))
    static int constructSuffixArray(Str& str, unsigned*& sufArr);

private:
    struct Suffix {
        static unsigned genInd;
        unsigned index = genInd++;  // index of suffix's first char
        unsigned rankHigh = 0;      // high priority part of rank
        unsigned rankLow = 0;       // low priority part of rank
        bool operator<(const Suffix& s) const;
        bool operator==(const Suffix& s) const;
    };
};

#endif // STRUTIL_H_INCLUDED
