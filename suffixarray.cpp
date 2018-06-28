#include "suffixarray.h"
#include "strfact.h"
#include "exceptions.h"

using namespace std;

SuffixArray::SuffixArray(const Str& str, unsigned step): str(str) {
    if (step == 1) {        // not sparse
        logStep = 0;
        sparseMask = 0;
        len = str.len + 1;
    }
    else {                  // sparse
        logStep = sizeof(unsigned) * CHARSIZE_BITS;
        for (sparseMask = -1; sparseMask >= step; sparseMask >>= 1, logStep--);
        len = (str.len >> logStep) + 1;
    }

    unsigned *fullSufArr = nullptr;
    StrFact::constructSuffixArray(str, fullSufArr);

    if (!logStep) {
        arr = fullSufArr;                                   // take full array
    }
    else {
        unsigned *sparseSufArr = new unsigned[len];
        for (unsigned i = 0; i < len; i++) {
            sparseSufArr[i] = fullSufArr[i << logStep];     // take only parts
        }
        delete[] fullSufArr;
        arr = sparseSufArr;
    }
}

const int SuffixArray::operator[](int i) const {
    if (i < 0 || i > str.len) {
        throw IndexOutOfBoundsException(i, len);
    }
    else {
        if (!logStep) {                     // not sparse
            return arr[i];
        }
        else {
            if ((i & sparseMask) == 0) {    // sparse, exists
                return arr[i >> logStep];
            }
            else {
                return -1;                  // sparse, does not exist
            }
        }
    }
}

void SuffixArray::destroy() {
    delete arr;
    arr = nullptr;
    len = 0;
}

ostream& operator<<(std::ostream& os, const SuffixArray& sufArr) {
    for (unsigned i = 0; i < sufArr.len; i++) {
        os << sufArr.arr[i] << ' ';
    }
    return os;
}
