#ifndef STR_H_INCLUDED
#define STR_H_INCLUDED

#include <iostream>

//using namespace ;

// basic string structure holding characters and its length
class Str {
private:
    const char* chars = nullptr;
    const unsigned len = 0;
public:
    Str(const char* src, unsigned len);
    ~Str();
    const unsigned length() const { return len; }
    const char& operator[](int i) const;

    friend std::ostream& operator<<(std::ostream& os, const Str& str);
    friend class StrUtil;
};

#endif // STR_H_INCLUDED
