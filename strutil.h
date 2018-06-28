#ifndef STRUTIL_H_INCLUDED
#define STRUTIL_H_INCLUDED

#include "str.h"

#include <iostream>

// utility class for more advanced string functions
class StrUtil {
public:
    // sample few first and last chars of a string
    static void sample(const Str& str, unsigned n, std::ostream& os);
    // count occurrences of all ascii characters
    static unsigned* count(const Str& str);
    // textual histogram
    static void histogram(const Str& str, std::ostream& os);
    // check of all chars are uppercase
    static bool areAllUpper(const Str& str);
    // print char or its ascii if not printable
    static std::ostream& printChar(std::ostream& os, char c);
};

#endif // STRUTIL_H_INCLUDED
