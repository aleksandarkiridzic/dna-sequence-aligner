#include "strutil.h"

using namespace std;

void StrUtil::sample(Str& str, unsigned n, ostream& os) {
    if (n > (str.len >> 1)) {
        n = str.len / 2;
    }
    for (int i = 0; i < n; os << str.chars[i++]);
    os << "...";
    os << (str.chars + str.len - n) << endl;
}

void StrUtil::histogram(Str& str, ostream& os) {

    unsigned cnt[TOTAL_CHARS] = {0};
    for (unsigned i = 0; i < str.len; cnt[str.chars[i++]]++);
    for (unsigned c = 0; c < TOTAL_CHARS; c++) {
        if (cnt[c] > 0) {
            os << "\'" << (char)c << "\': " << cnt[c] << endl;
        }
    }
}
