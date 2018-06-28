#include "strfact.h"

#include <algorithm>

using namespace std;

int StrFact::constructSuffixArray(Str& str, unsigned*& sufArr) {
    sufArr = nullptr;
    unsigned len = str.len;
    if (len < 4) { // short string, sort manually
        return -1 - len;
    }

    Suffix *suffixes = new Suffix[len];
    for (unsigned i = 0; i < len; i++) {    // initial phase - sort by 2 chars
        suffixes[i].rankHigh = (unsigned char) str.chars[i];
        suffixes[i].rankLow = (unsigned char) str.chars[i + 1];
    }
    sort(suffixes, suffixes + len);

    unsigned *sufRows = new unsigned[len];
    for (unsigned step = 2; step < len; step <<= 1) {   // each next step is doubled
        unsigned newRankHigh = 0;                       // new rankHigh to assign based only on previous iteration ranks
        unsigned compRankHigh = suffixes[0].rankHigh;   // previous rankHigh used for comparison
        suffixes[0].rankHigh = 0;                       // reset first suffix's rankHigh
        sufRows[suffixes[0].index] = 0;

        for (unsigned i = 1; i < len; i++) {                        // rankHigh updating based on previous iteration ranks
            if (suffixes[i].rankHigh == compRankHigh &&             // same rank as previous
                suffixes[i].rankLow == suffixes[i - 1].rankLow) {
                suffixes[i].rankHigh = newRankHigh;
            }
            else {                                                  // different
                compRankHigh = suffixes[i].rankHigh;                // new suffix for rank comparison
                suffixes[i].rankHigh = ++newRankHigh;
            }
            sufRows[suffixes[i].index] = i;
        }

        for (unsigned i = 0; i < len; i++) {            // rankHigh updating based on step ranks
            unsigned stepIndex = suffixes[i].index + step;
            suffixes[i].rankLow = (stepIndex < len) ? suffixes[sufRows[stepIndex]].rankHigh : 0;
        }

        sort(suffixes, suffixes + len);
    }

    delete[] sufRows;

    sufArr = new unsigned[len + 1];
    for (unsigned i = 1; i <= len; i++) {        // assign index each suffix
        sufArr[i] = suffixes[i - 1].index;
    }
    sufArr[0] = len;                            // empty suffix is always first when sorted

    delete[] suffixes;

    return 0;
}

Str StrFact::bwt(Str& str, unsigned*& sufArr, bool keepOriginal) {
    if (sufArr == nullptr) {    // construct suffix array if it doesn't exist
        constructSuffixArray(str, sufArr);
    }

    char* bwt = new char[str.len + 1];
    for (unsigned i = 0; i <= str.len; i++) {
        bwt[i] = sufArr[i] ? str[sufArr[i] - 1] : 0;
    }

    Str bwtStr(bwt, str.len);
    delete[] bwt;

    return bwtStr;
}

// Suffix struct

unsigned StrFact::Suffix::genInd = 0;

inline bool StrFact::Suffix::operator<(const Suffix& s) const {
    return
        this->rankHigh < s.rankHigh ||
        (this->rankHigh == s.rankHigh && this->rankLow < s.rankLow);
}

inline bool StrFact::Suffix::operator==(const Suffix& s) const {
    return this->rankHigh == s.rankHigh && this->rankLow == s.rankLow;
}
