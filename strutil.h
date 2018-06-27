#ifndef STRUTIL_H_INCLUDED
#define STRUTIL_H_INCLUDED

#include "str.h"

#include <iostream>

constexpr unsigned TOTAL_CHARS = 1 << (sizeof(char) * 8);

// utility class for more advanced string functions
class StrUtil {
public:
    static void sample(Str& str, unsigned n, std::ostream& os);
    static void histogram(Str& str, std::ostream& os);
};

#endif // STRUTIL_H_INCLUDED
