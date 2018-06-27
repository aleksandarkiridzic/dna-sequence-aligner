#include "str.h"
#include "exceptions.h"

#include <cstring>

using namespace std;

Str::Str(const char* src, unsigned len): len(len) {
    char *dest = new char[len + 1];
    memcpy(dest, src, len + 1);
    chars = dest;
}

Str::~Str() {
    delete[] chars;
}

const char& Str::operator[](int i) const {
    if (i < 0 || i > len) {
        throw IndexOutOfBoundsException(i, len);
    }
    else {
        return chars[i];
    }
}

ostream& operator<<(ostream& os, const Str& str) {
    for (unsigned i = 0; i <= str.len; i++) {
        os << str.chars[i];
    }
    return os;
}
