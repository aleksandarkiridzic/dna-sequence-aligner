#ifndef STR_H_INCLUDED
#define STR_H_INCLUDED

#include "general.h"
#include <iostream>
#include <cstring>

// basic string structure holding characters and its length
immutable_class Str {
protected:
    const char* chars = nullptr;
    unsigned len = 0;
public:
    Str() {}
    Str(const char* src, unsigned len);
    Str(std::string str): Str(str.c_str(), str.length()) {}
    Str(unsigned len, const char* ptr): chars(ptr), len(len) {}     // shallow copy
    ~Str() { /* destroy(); */ }                                     // must be destroyed explicitly
    const unsigned length() const { return len; }
    const bool isEmpty() const { return !chars; }
    const char& operator[](int i) const;
    Str subStr(unsigned from, unsigned siz) const;
    Str subStrCatch(unsigned from, unsigned siz) const;
    const char lastCharVisible() const;
    static Str empty;
protected:
    virtual void destroy();

    friend std::ostream& operator<<(std::ostream& os, const Str& str);
    friend class StrUtil;
    friend class StrFact;
    friend class SuffixArray;
    friend class Checkpoint;
};

#endif // STR_H_INCLUDED
