#include "str.h"
#include "exceptions.h"

#include <cstring>
#include <cctype>

using namespace std;

Str::Str(const char* src, unsigned len): len(len) {
    char *dest = new char[len + 1];
    memcpy(dest, src, len + 1);
    chars = dest;
}

const char& Str::operator[](int i) const {
    if (i < 0 || i > len) {
        throw IndexOutOfBoundsException(i, len);
    }
    else {
        return chars[i];
    }
}

Str Str::subStr(unsigned from, unsigned siz) const {
    if (from > len) {
        throw IndexOutOfBoundsException(from, len);
    }
    if (from + siz > len) {
        throw IndexOutOfBoundsException(from + siz, len);
    }
    return Str(chars + from, siz);
}

const char Str::lastCharVisible() const {
    return isprint(chars[len]) ? chars[len] : '0';
}

void Str::destroy() {
    delete[] chars;
    chars = nullptr;
    len = 0;
}

ostream& operator<<(ostream& os, const Str& str) {
    for (unsigned i = 0; i < str.len; i++) {
        os << str.chars[i];
    }
    return os;
}
