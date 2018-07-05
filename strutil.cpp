#include "strutil.h"

#include <cctype>

using namespace std;

void StrUtil::sample(const Str& str, unsigned n, ostream& os) {
    if (n > (str.len >> 1)) {
        n = str.len / 2;
    }
    Str firstN = str.subStr(0, n);
    Str lastN = str.subStr(str.len - n, n);
    os << firstN << "..." << lastN << str.lastCharVisible() << endl;
}

unsigned* StrUtil::count(const Str& str) {
    unsigned *cnt = new unsigned[TOTAL_CHARS];
    for (unsigned i = 0; i < TOTAL_CHARS; i++) {
        cnt[i] = 0;
    }
    for (unsigned i = 0; i <= str.len; cnt[(byte)str.chars[i++]]++);

    return cnt;
}

void StrUtil::histogram(const Str& str, ostream& os) {
    unsigned *cnt = count(str);
    for (unsigned c = 0; c < TOTAL_CHARS; c++) {
        if (cnt[c] > 0) {
            printChar(os, c) << ": " << cnt[c] << endl;
        }
    }
    delete[] cnt;
}

bool StrUtil::areAllUpper(const Str& str) {
    for (unsigned i = 0; i < str.len; i++) {
        if (str.chars[i] && !isupper(str.chars[i])) {
            return false;
        }
    }
    return true;
}

bool StrUtil::areAllAllowed(const Str& str, char* allowed) {
    for (unsigned i = 0; i < str.len; i++) {
        if (!allowed[(byte)str.chars[i]]) {
            return false;
        }
    }
    return true;
}

std::ostream& StrUtil::printChar(std::ostream& os, char c) {
    if (isprint(c)) {
        os << c;
    }
    else {
        os << "\'" << (unsigned)c << "\'";
    }
    return os;
}
