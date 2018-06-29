#ifndef RANGE_H_INCLUDED
#define RANGE_H_INCLUDED

#include <iostream>

struct Range {
    unsigned low;
    unsigned high;
    Range(unsigned low, unsigned high);

    friend std::ostream& operator<<(std::ostream& os, const Range& range);
};

#endif // RANGE_H_INCLUDED
