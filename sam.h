#ifndef SAM_H_INCLUDED
#define SAM_H_INCLUDED

#include "general.h"
#include "read.h"
#include "str.h"

#include <vector>
#include <iostream>

class Sam {
private:
    immutable_struct SamEntry;
    std::vector<SamEntry> entries;
    enum Cols { READ_ID, STRAND_DIR, POS, SCORE, CIGAR, READ_SEQ, READ_QUAL } ;
    unsigned colWidth[READ_QUAL + 1];
public:
    void newEntry(const Read& read, bool strandDir, unsigned pos, int score, const Str& cigar);
    void write(const char* filePath);
private:
    void calcColWidth();
    void writeHeader(std::ostream& os) const;
    void writeEntry(const SamEntry& entry, std::ostream& os) const;

    immutable_struct SamEntry {
        const Read read;
        const bool strandDir;
        const unsigned pos;
        const int score;
        const Str cigar;
        SamEntry(const Read& read, bool strandDir, unsigned pos, int score, const Str& cigar):
            read(read), strandDir(strandDir), pos(pos), score(score), cigar(cigar) {}
    };
};

#endif // SAM_H_INCLUDED
