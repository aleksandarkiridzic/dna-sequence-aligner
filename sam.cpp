#include "sam.h"
#include "exceptions.h"

#include <fstream>
#include <iomanip>

using namespace std;

void Sam::newEntry(const Read& read, bool strandDir, unsigned pos, int score, const Str& cigar) {
    entries.push_back(SamEntry(read, strandDir, pos, score, cigar));
}

void Sam::calcColWidth() {
    // READ_ID
    colWidth[READ_ID] = 7;      // read_id
    for (auto const& entry: entries) {
        if (entry.read.ident.length() > colWidth[READ_ID]) {
            colWidth[READ_ID] = entry.read.ident.length();
        }
    }

    // STRAND_DIR
    colWidth[STRAND_DIR] = 6;   // strand, for, rev

    // POS
    colWidth[POS] = 8;          // position
    unsigned maxPos = 0;
    for (auto const& entry: entries) {
        if (entry.pos > maxPos) {
            maxPos = entry.pos;
        }
    }
    for (maxPos /= 100000000; maxPos; maxPos /= 10) {
        colWidth[POS]++;
    }

    colWidth[SCORE] = 5;        // score
    int minScore = 0, maxScore = 0;
    for (auto const& entry: entries) {
        if (entry.score < minScore) {
            minScore = entry.score;
        }
        else if (entry.score > maxScore) {
            maxScore = entry.score;
        }
    }
    int maxAbsScore = (-minScore * 10 > maxScore) ? (-minScore * 10) : maxScore;
    for (maxAbsScore /= 100000; maxAbsScore; maxAbsScore /= 10) {
        colWidth[SCORE]++;
    }

    // CIGAR
    colWidth[CIGAR] = 5;     // cigar
    for (auto const& entry: entries) {
        if (entry.cigar.length() > colWidth[CIGAR]) {
            colWidth[CIGAR] = entry.cigar.length();
        }
    }

    // READ_SEQ
    colWidth[READ_SEQ] = 13;     // read_sequence
    for (auto const& entry: entries) {
        if (entry.read.seq.length() > colWidth[READ_SEQ]) {
            colWidth[READ_SEQ] = entry.read.seq.length();
        }
    }

    // READ_QUAL
    colWidth[READ_QUAL] = colWidth[READ_SEQ];
}

void Sam::write(const char* filePath) {
    ofstream output(filePath);
    if (!output.is_open()) {
        throw FileNotFoundException(filePath);
    }

    calcColWidth();
    writeHeader(output);
    for (const auto& entry: entries) {
        writeEntry(entry, output);
    }

    output.close();
}

void Sam::writeHeader(ostream& os) const {
    os  << setw(colWidth[READ_ID]) << left << "read_id" << "\t"
        << setw(colWidth[STRAND_DIR]) << left << "strand" << "\t"
        << setw(colWidth[POS]) << left << "position" << "\t"
        << setw(colWidth[SCORE]) << left << "score" << "\t"
        << setw(colWidth[CIGAR]) << left << "cigar" << "\t"
        << setw(colWidth[READ_SEQ]) << left << "read_sequence" << "\t"
        << "read_quality" << endl;
}

void Sam::writeEntry(const SamEntry& entry, ostream& os) const {
    os  << entry.read.ident << string(colWidth[READ_ID] - entry.read.ident.length(), ' ') << "\t"
        << setw(colWidth[STRAND_DIR]) << left << (entry.strandDir ? "FOR" : "REV") << "\t"
        << setw(colWidth[POS]) << left << entry.pos + 1 << "\t"
        << setw(colWidth[SCORE]) << left << entry.score << "\t"
        << entry.cigar << string(colWidth[CIGAR] - entry.cigar.length(), ' ') << "\t"
        << entry.read.seq << string(colWidth[READ_SEQ] - entry.read.seq.length(), ' ') << "\t"
        << entry.read.qual << endl;
}
