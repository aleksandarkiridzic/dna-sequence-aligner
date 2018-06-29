#ifndef SUFFIXARRAY_H_INCLUDED
#define SUFFIXARRAY_H_INCLUDED

#include "general.h"
#include "str.h"

immutable_class SuffixArray {
private:
    const Str& str;             // corresponding string
    const unsigned* arr;        // array of suffix positions
    unsigned logStep;           // shift step when sparse, 0 when not
    unsigned sparseMask;        // mask for checking if the value is held; step = sparseMask + 1
public:
    SuffixArray(const Str& str, unsigned step = 1);
    ~SuffixArray() { destroy(); }
    inline unsigned length() const { return (str.len >> logStep) + 1; }
    const int operator[](int i) const;
    SuffixArray sparse(unsigned step, bool keepOriginal = true);
private:
    void destroy();
    SuffixArray(const Str& str, unsigned* arr, unsigned logStep, unsigned sparseMask):
        str(str), arr(arr), logStep(logStep), sparseMask(sparseMask) {}

    friend std::ostream& operator<<(std::ostream& os, const SuffixArray& sufArr);
    friend class StrFact;
    friend class FMStr;
};

#endif // SUFFIXARRAY_H_INCLUDED
