#ifndef READ_H_INCLUDED
#define READ_H_INCLUDED

#include "str.h"
#include "strUtil.h"

#include <vector>

class Read {
private:
    const Str ident;
    const Str seq;
    Str complement;
    const Str qual;
public:
    Read(const Str& ident, const Str& seq, const Str& qual);
private:
    static const char* inverse;         // points to inverse character of every allowed character, for non-allowed 0
public:
    static void setAlphabet(std::vector<char> alphabet);

    void info() {
        StrUtil::sample(ident, 3, std::cout);
        StrUtil::sample(seq, 3, std::cout);
        StrUtil::sample(complement, 3, std::cout);
        StrUtil::sample(qual, 3, std::cout);
    }
};

#endif // READ_H_INCLUDED
