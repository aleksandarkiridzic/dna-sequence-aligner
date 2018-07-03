#include "suffixarray.h"
#include "strfact.h"
#include "exceptions.h"

using namespace std;

SuffixArray::SuffixArray(const Str& str, unsigned step): str(str) {
    if (step == 1) {        // not sparse
        logStep = 0;
        sparseMask = 0;
    }
    else {                  // sparse
        logStep = sizeof(unsigned) * CHARSIZE_BITS;
        for (sparseMask = -1; sparseMask >= step; sparseMask >>= 1, logStep--);
    }

    unsigned *fullSufArr = nullptr;
    StrFact::constructSuffixArray(str, fullSufArr);

    if (!logStep) {
        arr = fullSufArr;                                   // take full array
    }
    else {
        unsigned len = length();
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
        throw IndexOutOfBoundsException(i, str.len);
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

SuffixArray SuffixArray::sparse(unsigned step, bool keepOriginal) {
    if (logStep || step == 1) {      // already sparse
        return *this;
    }

    unsigned newLogStep = sizeof(unsigned) * CHARSIZE_BITS;     // sparse step
    unsigned newSparseMask;                                     // sparse mask
    for (newSparseMask = -1; newSparseMask >= step; newSparseMask >>= 1, newLogStep--);

    unsigned newLen =(str.len >> newLogStep) + 1;   // length of sparse array
    unsigned *sparseSufArr = new unsigned[newLen];
    for (unsigned i = 0; i < newLen; i++) {
        sparseSufArr[i] = arr[i << newLogStep];        // take only parts
    }

    if (!keepOriginal) {
        destroy();
    }

    return SuffixArray(str, sparseSufArr, newLogStep, newSparseMask);
}

void SuffixArray::destroy() {
    delete arr;
    arr = nullptr;
}

ostream& operator<<(std::ostream& os, const SuffixArray& sufArr) {
    for (unsigned i = 0; i < sufArr.length(); i++) {
        os << sufArr.arr[i] << ' ';
    }
    return os;
}
