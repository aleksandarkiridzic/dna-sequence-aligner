#include "range.h"
#include "exceptions.h"

using namespace std;

Range::Range(unsigned low, unsigned high): low(low), high(high) {
    if (low > high) {
        throw IndexOutOfBoundsException(low, high - 1);
    }
}

ostream& operator<<(ostream& os, const Range& range) {
    return os << "[" << range.low << ", " << range.high << ")";
}
