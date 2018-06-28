#ifndef SUFFIXARRAY_H_INCLUDED
#define SUFFIXARRAY_H_INCLUDED

#include "general.h"
#include "str.h"

immutable_class SuffixArray {
private:
    const Str& str;             // corresponding string
    const unsigned *arr;        // array of suffix positions
    unsigned logStep;           // shift step when sparse, 0 when not
    unsigned sparseMask;        // mask for checking if the value is held; step = sparseMask + 1
    unsigned len;
public:
    SuffixArray(const Str& str, unsigned step = 1);
    ~SuffixArray() { destroy(); }
    inline unsigned length() const { return len; }
    const int operator[](int i) const;
private:
    void destroy();

    friend std::ostream& operator<<(std::ostream& os, const SuffixArray& sufArr);
};

#endif // SUFFIXARRAY_H_INCLUDED
