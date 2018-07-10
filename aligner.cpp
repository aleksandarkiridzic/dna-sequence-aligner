#include "aligner.h"
#include "exceptions.h"

#include <utility>

Aligner::Aligner(const FMStr& refGenome, const std::vector<Read>& reads): refGenome(refGenome) {
    for (auto const& read: reads) {
        rms.push_back(ReadMatch(read));
    }
}

void Aligner::setSeedParameters(unsigned seedLength, unsigned seedInterval) {
    if (seedLength < seedInterval) {
        throw SeedInvalidException(seedLength, seedInterval);
    }

    this->seedLength = seedLength;
    this->seedInterval = seedInterval;
}

void Aligner::setWindowReadRatio(float windowReadRatio) {
    if (windowReadRatio < 0.0) {
        throw WindowInvalidException(windowReadRatio);
    }

    this->windowReadRatio = windowReadRatio;
}

void Aligner::align(Range readRange, const char* filePath) {
    for (unsigned i = readRange.low; i < readRange.high; i++) {
        align(i);
    }
    sam.write(filePath);
}

void Aligner::align(unsigned readIndex) {
    rms[readIndex].seed(refGenome, seedLength, seedInterval);
    rms[readIndex].score();
    rms[readIndex].rank(windowReadRatio);
    std::pair<StrSimMatch, bool> ssm = rms[readIndex].extend(lazyRefStr(), strSim, maxWindows);
    if (!ssm.first.isEmpty()) {
        sam.newEntry(rms[readIndex].getRead(), ssm.second, ssm.first.pos, ssm.first.score, ssm.first.cigar);
    }
    // std::cout << ssm.first;
}

Str& Aligner::lazyRefStr() {
    if (refStr.isEmpty()) {
        refStr = refGenome.inverse();
    }
    return refStr;
}
