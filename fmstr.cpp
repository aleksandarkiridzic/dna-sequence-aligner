#include "fmstr.h"
#include "strfact.h"
#include "range.h"

#include <sstream>
#include <cstring>

using namespace std;

FMStr::FMStr(const Str& str, const SuffixArray& sufArr, const Checkpoint& checkpoint):
    Str(str), sufArr(sufArr), checkpoint(checkpoint) {}

vector<unsigned> FMStr::allPos(const Str& str) const {
    if (str.isEmpty()) {
        return {};         // run only if string is empty
    }

    Range range = checkpoint.rangeAll(str[str.length() - 1]);
    for (int i = str.length() - 2; i >= 0 && !range.isEmpty(); i--) {
        range = checkpoint.range(range, str[i]);
    }

    if (range.isEmpty()) {
        return {};         // no occurrences
    }
    vector<unsigned> result(range.size());

    for (unsigned it = range.low; it < range.high; it++) {
        result[it - range.low] = originalPos(it);   // locate occurrences
    }

    return result;
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
    while (pos < 0) {                           // not found in sparse suffix array
        index = checkpoint.l2f(index);          // find L(index) in F; that's F(index)'s predecessor
        pos = sufArr[index];                    // try with new position
        step++;
    }

    pos += step;
    return pos > len ? pos - len : pos;
}

FMStr::~FMStr() {
    sufArr.destroy();
    checkpoint.destroy();
    destroy();
}

void FMStr::pack() {
    if (isPacked) {     // must not be packed
        return;
    }

    char curCh = chars[0];
    byte runLen = 1;
    constexpr unsigned MAX_BYTE = TOTAL_CHARS - 1;
    ostringstream oss;

    for (unsigned i = 1; i <= len; i++) {
        if (chars[i] == curCh && runLen < MAX_BYTE) {   // continue run up to 255 same chars
            runLen++;
        }
        else {
            oss.put(runLen).put(curCh);                 // print length and the character
            curCh = chars[i];                           // start new run
            runLen = 1;
        }
    }
    oss.put(runLen).put(curCh);

    string packed = oss.str();
    len = packed.length() - 1;
    char* dest = new char[len + 1];
    memcpy(dest, packed.c_str(), (len + 1) * sizeof(char));
    delete[] chars;
    chars = dest;

    isPacked = true;
}

void FMStr::unpack() {
    if (!isPacked) {        // must be packed
        return;
    }

    ostringstream oss;
    for (unsigned i = 0; i <= len; i += 2) {
        byte runLen = chars[i];
        char ch = chars[i + 1];
        oss << string(runLen, ch);
    }

    string unpacked = oss.str();
    len = unpacked.length() - 1;
    char* dest = new char[len + 1];
    memcpy(dest, unpacked.c_str(), (len + 1) * sizeof(char));
    delete[] chars;
    chars = dest;

    isPacked = false;
}

void FMStr::info() const {
    cout << "suffix array\n" << sufArr << endl;
    checkpoint.info();
}
