#ifndef STR_H_INCLUDED
#define STR_H_INCLUDED

class Str {
private:
    const char* chars = nullptr;
    const unsigned len = 0;
public:
    Str(const char* src, unsigned len);
    const unsigned length() const { return len; }
    const char& operator[](int i) const;

    friend class StrUtil;
};

#endif // STR_H_INCLUDED
