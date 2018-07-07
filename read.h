#ifndef READ_H_INCLUDED
#define READ_H_INCLUDED

#include "str.h"
#include "strUtil.h"
#include "general.h"

#include <vector>

immutable_class Read {
private:
    const Str ident;
    const Str seq;
    Str revComp;
    const Str qual;
public:
    Read(const Str& ident, const Str& seq, const Str& qual);
private:
    static const char* inverse;         // points to inverse character of every allowed character, for non-allowed 0
public:
    static void setAlphabet(std::vector<char> alphabet);

    friend class ReadMatch;

    void info() {
        StrUtil::sample(ident, 3, std::cout);
        StrUtil::sample(seq, 3, std::cout);
        StrUtil::sample(revComp, 3, std::cout);
        StrUtil::sample(qual, 3, std::cout);
    }
};

#endif // READ_H_INCLUDED
