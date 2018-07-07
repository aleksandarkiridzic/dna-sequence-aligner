#ifndef MATCH_H_INCLUDED
#define MATCH_H_INCLUDED

#include "fmstr.h"
#include "read.h"

#include <vector>

class ReadMatch {
private:
    struct SeedMatch {
        const unsigned pos;             // seed position in the read
        std::vector<unsigned> matches;  // match results
        SeedMatch(unsigned pos, const std::vector<unsigned>& matches): pos(pos), matches(matches) {}
        inline float uniqueness() const { return 1.0 / matches.size(); }

        friend class Aligner;
    };

    struct PosScore {
        unsigned pos;                   // position in the reference genome
        float score;                    // position score
        PosScore(unsigned pos, float score): pos(pos), score(score) {}
        bool operator<(const PosScore& w) const { return pos < w.pos; }     // for sorting by position
    };

    immutable_struct Window {
        unsigned pos;                   // window starting position in the reference genome; top bit set if for reverse complement
        float score;                    // sum of all scores belonging to the window
        Window(unsigned pos, float score): pos(pos), score(score) {}
        inline bool isRevComp() const { return pos & UNSIGNED_TOP_BIT; }
        inline unsigned realPos() const { return pos & ~UNSIGNED_TOP_BIT; }
        bool operator<(const Window& w) const { return score < w.score; }   // for sorting by score
    };

    Read read;
    bool isMatched = false;
    std::vector<SeedMatch> smFor;       // forward-looking seeds
    std::vector<SeedMatch> smRev;       // reverse-looking seeds
    std::vector<PosScore> psFor;        // forward-looking matches
    std::vector<PosScore> psRev;        // reverse-looking matches
    std::vector<Window> windows;        // all windows
    unsigned seedLength, seedInterval;
    unsigned windowLength, windowDist;
    /*  windowLength = windowLeft + windowDist + windowRight
        windowLeft = windowRight = readLength*/
    enum { EMPTY, SEEDED, SCORED, RANKED, EXTENDED } state = EMPTY;
public:
    ReadMatch(const Read& read): read(read) {}
    void seed(const FMStr& refGenome, unsigned sl, unsigned si);
    void score();
    void rank(float windowReadRatio);
private:
    void score(std::vector<SeedMatch>& sms, std::vector<PosScore>& pss);                        //accumulate scores according to positions
    void calcWindows(std::vector<PosScore>& pss, std::vector<Window>& windows, bool isRevComp); // calculate all windows scores
};


#endif // MATCH_H_INCLUDED
