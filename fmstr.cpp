#include "fmstr.h"
#include "strfact.h"
#include "range.h"

using namespace std;

FMStr::FMStr(const Str& str, const SuffixArray& sufArr, const Checkpoint& checkpoint):
    Str(str), sufArr(sufArr), checkpoint(checkpoint) {}

int* FMStr::allPos(const Str& str) const {
    if (str.isEmpty()) {
        return nullptr;         // run only if string is empty
    }

    Range range = checkpoint.rangeAll(str[str.length() - 1]);
    for (int i = str.length() - 2; i >= 0 && !range.isEmpty(); i--) {
        range = checkpoint.range(range, str[i]);
    }

    if (range.isEmpty()) {
        return nullptr;         // no occurrences
    }
    int* posList = new int[range.size() + 1];
    for (unsigned it = range.low; it < range.high; it++) {
        posList[it - range.low] = originalPos(range.low);   // locate occurrences
    }
    posList[range.size()] = -1;                             // end list with -1

    return posList;
}

Str FMStr::inverse() const {
    char* dest = new char[len + 1];     // of same length as the transform

    unsigned pos = 0;
    dest[len] = 0;                      // original ends with a 0

    for (int i = len - 1; i >= 0; i--) {
        dest[i] = chars[pos];
        pos = checkpoint.l2f(pos);      // find L(pos) in F
    }

    return Str(dest, len);
}

unsigned FMStr::originalPos(unsigned index) const {
    int pos = sufArr[index];
    unsigned step = 0;
    while (pos == -1) {                         // not found in sparse suffix array
        index = checkpoint.l2f(chars[index]);   // find L(index) in F; that's F(index)'s predecessor
        pos = sufArr[index];                    // try with new position
        step++;
    }

    return pos + step;
}
