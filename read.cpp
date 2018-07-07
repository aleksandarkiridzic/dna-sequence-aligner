#include "read.h"
#include "exceptions.h"

using namespace std;

const char* Read::inverse = nullptr;

Read::Read(const Str& ident, const Str& seq, const Str& qual) :
    ident(ident), seq(seq), qual(qual) {
        if (seq.length() != qual.length()) {
            throw ReadIllegalQualLenException(ident, seq.length(), qual.length());
        }

        char* dest = new char[seq.length() + 1];
        for (unsigned i = 0, j = seq.length() - 1; i <= j; i++, j--) {
            dest[i] = inverse[(byte)seq[j]];
            dest[j] = inverse[(byte)seq[i]];
        }
        revComp = Str(dest, seq.length());
    }

void Read::setAlphabet(vector<char> alphabet) {
    char* inverseInit = new char[TOTAL_CHARS];
    for (unsigned i = 0; i < TOTAL_CHARS; i++) {
        inverseInit[i] = 0;
    }
    for (unsigned i = 0, j = alphabet.size() - 1; i <= j; i++, j--)  {
        inverseInit[(byte)alphabet[i]] = alphabet[j];
        inverseInit[(byte)alphabet[j]] = alphabet[i];
    }

    inverse = inverseInit;
}
