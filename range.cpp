#include "range.h"
#include "exceptions.h"

using namespace std;

Range::Range(unsigned low, unsigned high) {
    if (low >= high) {
        throw IndexOutOfBoundsException(low, high - 1);
    }
    this->low = low;
    this->high = high;
}

ostream& operator<<(ostream& os, const Range& range) {
    return os << "[" << range.low << ", " << range.high << ")";
}
