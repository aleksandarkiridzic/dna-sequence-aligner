#include "checkpoint.h"
#include "strfact.h"
#include "strutil.h"
#include "exceptions.h"

#include <cstring>

using namespace std;

Checkpoint::Checkpoint(const Str& str, unsigned step): str(str) {
    if (step == 1) {        // not sparse
        logStep = 0;
        sparseMask = 0;
    }
    else {                  // sparse
        logStep = sizeof(unsigned) * CHARSIZE_BITS;
        for (sparseMask = -1; sparseMask >= step; sparseMask >>= 1, logStep--);
    }

    int* ch2colInit = new int[TOTAL_CHARS];
    unsigned* cnt = StrUtil::count(str);
    activeChars = 0;
    for (unsigned i = 0, c = 0; i < TOTAL_CHARS; i++) {
        if (cnt[i]) {
            activeChars++;          // count distinct character in the string
            ch2colInit[i] = c++;    // assign a column
        }
        else {
            ch2colInit[i] = -1;     // assign illegal value
        }
    }
    ch2col = ch2colInit;

    unsigned* limitsInit = new unsigned[activeChars + 1];
    for (unsigned i = 0, prevHigh = 0; i < TOTAL_CHARS; i++) {
        if (cnt[i]) {
            limitsInit[ch2colInit[i]] = prevHigh;   // assign next value
            prevHigh += cnt[i];                     // then raise it
        }
    }
    limitsInit[activeChars] = str.len + 1;
    limits = limitsInit;

    delete[] cnt;

    unsigned len = length();
    unsigned** tableInit = new unsigned*[len];
    for (unsigned i = 0; i < len; i++) {
        tableInit[i] = new unsigned[activeChars];
    }
    for (unsigned c = 0; c < activeChars; c++) {  // initialize first row
        tableInit[0][c] = 0;
    }
    for (unsigned i = 1; i < len; i++) {
        memcpy(tableInit[i], tableInit[i - 1], activeChars * sizeof(unsigned));       // copy values from previous checkpoint
        for (unsigned k = ((i - 1) << logStep); k < (i << logStep); k++) {              // increase for all occurrences
            tableInit[i][ch2col[(byte)str[k]]]++;                                       // previous and current checkpoint
        }
    }
    table = const_cast<const unsigned**>(tableInit);
}

Range Checkpoint::range(const Range& range, char ch) const {
    if (ch2col[(byte)ch] == -1) { // no char in string
        throw NoCharInStrException(ch, str);
    }
    if (range.low > str.len) {
        throw IndexOutOfBoundsException(range.low, str.len);
    }
    if (range.high > str.len) {
        throw IndexOutOfBoundsException(range.high, str.len);
    }

    unsigned low, high;
    unsigned it;

    low = table[range.low >> logStep][ch2col[(byte)ch]];            // last one implicitly counted
    it = range.low & ~sparseMask;
    while (it < range.low) {
        if (str[it++] == ch) {
            low++;
        }
    }

    if ((range.low >> logStep) == (range.low >> logStep)) {         // same segment
        high = low + 1;                                             // start from where previously stopped
    }
    else {
        high = table[range.high >> logStep][ch2col[(byte)ch]];      // different segment
        it = range.high & ~sparseMask;                              // start from anew
    }

    while (it < range.high) {                                       // last one implicitly counted
        if (str[it++] == ch) {
            high++;
        }
    }

    return Range(limits[(byte)ch] + low, limits[(byte)ch] + high);
}

Range Checkpoint::rangeAll(char ch) const {
    if (ch2col[(byte)ch] == -1) { // no char in string
        throw NoCharInStrException(ch, str);
    }

    return Range(limits[ch2col[byte(ch)]], limits[ch2col[byte(ch)] + 1]);
}

unsigned Checkpoint::l2f(unsigned index) const {
    if (index > str.len) {
        throw IndexOutOfBoundsException(index, str.len);
    }

    unsigned res = table[index >> logStep][ch2col[(byte)str[index]]];
    unsigned it = index & ~sparseMask;
    while (it < index) {                    // last one implicitly counted
        if (str[it++] == str[index]) {
            res++;
        }
    }

    return limits[ch2col[(byte)str[index]]] + res;
}

void Checkpoint::destroy() {
    for (unsigned i = 0; i < length(); i++) {
        delete[] table[i];
    }
    table = nullptr;
    delete[] ch2col;
    ch2col = nullptr;
    delete[] limits;
    limits = nullptr;
}

void Checkpoint::info() const {
    cout << "table\n";
    for (unsigned i = 0; i < length(); i++) {
        for (unsigned j = 0; j < activeChars; j++) {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
    cout << "limits\n";
    for (unsigned i = 0; i < activeChars; i++) {
        cout << limits[i] << " ";
    }
    cout << endl;
}
