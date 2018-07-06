#ifndef MATCH_H_INCLUDED
#define MATCH_H_INCLUDED

#include "fmstr.h"
#include "read.h"

#include <vector>

class ReadMatch {
private:
    struct SeedMatch {
        const unsigned pos;
        std::vector<unsigned> matches;
        SeedMatch(unsigned pos, const std::vector<unsigned>& matches): pos(pos), matches(matches) {}
        inline float importance() const { return 1.0 / matches.size(); }

        friend class Aligner;
    };

    Read read;
    bool isMatched = false;
    std::vector<SeedMatch> sms;
    unsigned seedLength, seedInterval;
    unsigned windowLength, windowInterval;
    enum { EMPTY, SEEDED, EXTENDED } state = EMPTY;
public:
    ReadMatch(const Read& read): read(read) {}
    void seed(const FMStr& refGenome, unsigned sl, unsigned si);


};


#endif // MATCH_H_INCLUDED
