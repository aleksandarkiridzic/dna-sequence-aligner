#ifndef RANGE_H_INCLUDED
#define RANGE_H_INCLUDED

#include <iostream>

#include "general.h"

struct Range {
    unsigned low;
    unsigned high;
    Range(unsigned low, unsigned high);
    inline bool isEmpty() const { return low >= high; }
    inline unsigned size() const { return high - low; }

    friend std::ostream& operator<<(std::ostream& os, const Range& range);
};

#endif // RANGE_H_INCLUDED
