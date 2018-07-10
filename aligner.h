#ifndef ALIGNER_H_INCLUDED
#define ALIGNER_H_INCLUDED

#include "read.h"
#include "match.h"
#include "fmstr.h"
#include "range.h"
#include "strsimilarity.h"
#include "sim.h"
#include "sam.h"

#include <vector>

class Aligner {
private:
    const FMStr& refGenome;
    Str refStr;
    std::vector<ReadMatch> rms;
    unsigned seedLength = 20;       // seed phase parameters
    unsigned seedInterval = 10;
    float windowReadRatio = 1.0;
    unsigned maxWindows = 5;
    StrSimilarity strSim = StrSimilarity::defaulStrSim();
    Sam sam;
public:
    Aligner(const FMStr& refGenome, const std::vector<Read>& reads);
    void setSeedParameters(unsigned seedLength, unsigned seedInterval);
    void setWindowReadRatio(float windowReadRatio);
    void setMaxWindows(unsigned maxWindows) { this->maxWindows = maxWindows; }
    void setScoringMatrix(const StrSimilarity& strSim) { this->strSim = strSim; }
    void align(Range readRange, const char* filePath) ;
    void alignAll(const char* filePath) { align(Range(0, rms.size()), filePath); }
    void resetSam() { sam = Sam(); }
    Str& lazyRefStr();
private:
    void align(unsigned readIndex);
};

#endif // ALIGNER_H_INCLUDED
