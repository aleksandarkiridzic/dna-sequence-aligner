#ifndef STR_H_INCLUDED
#define STR_H_INCLUDED

#include <iostream>

constexpr unsigned CHARSIZE_BITS = 8;
constexpr unsigned TOTAL_CHARS = 1 << (sizeof(char) * CHARSIZE_BITS);

// basic string structure holding characters and its length
class Str {
private:
    const char* chars = nullptr;
    const unsigned len = 0;
public:
    Str(const char* src, unsigned len);
    ~Str() { destroy(); }
    const unsigned length() const { return chars ? len : 0; }
    const char& operator[](int i) const;
    Str subStr(unsigned from, unsigned siz) const;
    const char lastCharVisible() const;

    void destroy();

    friend std::ostream& operator<<(std::ostream& os, const Str& str);
    friend class StrUtil;
    friend class StrFact;
};

#endif // STR_H_INCLUDED
