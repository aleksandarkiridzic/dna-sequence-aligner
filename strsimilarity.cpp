#include "strsimilarity.h"
#include "strfact.h"

#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

StrSimilarity::StrSimilarity(vector<char> alphabet, int** table): table(table), activeChars(alphabet.size()) {
    unsigned* ch2indInit = new unsigned[TOTAL_CHARS];
    fill_n(ch2indInit, TOTAL_CHARS, activeChars + 1);
    for (unsigned i = 0; i < alphabet.size(); i++) {
        ch2indInit[(byte)alphabet[i]] = i;
    }
    ch2ind = ch2indInit;
}

StrSimilarity StrSimilarity::defaulStrSim() {
    unsigned activeChars = 4;

    unsigned* ch2ind = new unsigned[TOTAL_CHARS];
    fill_n(ch2ind, TOTAL_CHARS, activeChars + 1);
    ch2ind['A'] = 0;
    ch2ind['C'] = 1;
    ch2ind['G'] = 2;
    ch2ind['T'] = 3;

    int** table = new int*[6];
    table[0] = new int[6] { 1,       -4,     -2,     -4,     -7,     -10};
    table[1] = new int[6] { -4,      1,      -4,     -2,     -7,     -10};
    table[2] = new int[6] { -2,      -4,     1,      -4,     -7,     -10};
    table[3] = new int[6] { -4,      -2,     -4,     1,      -7,     -10};
    table[4] = new int[6] { -7,      -7,     -7,     -7,     -1000,  -1000};
    table[5] = new int[6] { -10,     -10,    -10,    -10,    -1000,  -1000};

    return StrSimilarity(table, ch2ind, activeChars);
}

void StrSimilarity::destroy() {
    for (unsigned i = 0; i < activeChars + 2; i++) {
        delete[] table[i];
    }
    delete[] table;
    delete[] ch2ind;
}

StrSimMatch StrSimilarity::occurence(const Str& pat, const Str& str, unsigned basePos) const {
    unsigned rows = pat.length() + 1, cols = str.length() + 1;
    int** mem = new int*[rows];
    for (unsigned i = 0; i < rows; i++) {
        mem[i] = new int[cols] {0};     // initialize all with 0 except first column
    }
    for (unsigned i = 1; i < rows; i++) {
        mem[i][0] = mem[i - 1][0] + gap(pat[i - 1]);
    }
    char** dir = new char*[rows];
    for (unsigned i = 0; i < rows; i++) {
        dir[i] = new char[cols] {'D'};  // initialize first col with 'D'
    }

    for (unsigned i = 1; i < rows; i++) {
        for (unsigned j = 1; j < cols; j++) {                           // recurrence relation
            int del = mem[i - 1][j] + gap(pat[i - 1]);                  // deletion (D)
            int ins = mem[i][j - 1] + gap(str[j - 1]);                  // insertion (I)
            int mm = mem[i - 1][j - 1] + get(pat[i - 1], str[j - 1]);   // match/mismatch (M/X)

            int tmem; char tdir;
            if (del > ins) {
                tmem = del; tdir = 'D';
            }
            else {
                tmem = ins; tdir = 'I';
            }
            if (tmem > mm) {
                mem[i][j] = tmem;
                dir[i][j] = tdir;
            }
            else {
                mem[i][j] = mm;
                dir[i][j] = (pat[i - 1] == str[j - 1] ? 'M' : 'X');
            }
        }
    }

    unsigned rightEnd = 0;
    for (unsigned j = 0; j < cols; j++) {
        if (mem[rows - 1][j] > mem[rows - 1][rightEnd]) {   // find max score
            rightEnd = j;
        }
    }
    int score = mem[rows - 1][rightEnd];

    ostringstream oss;
    unsigned leftEnd = rightEnd;
    for (unsigned i = rows - 1; i > 0;) {
        oss << dir[i][leftEnd];
        switch (dir[i][leftEnd]) {
        case 'D':
            i--;
            break;
        case 'I':
            leftEnd--;
            break;
        case 'M':
        case 'X':
            i--; leftEnd--;
            break;
        }
    }

    string invEditTranscript = oss.str();   // deletions and mismatches on both ends are actually soft clips
    for (unsigned i = 0; i < invEditTranscript.length() && (invEditTranscript[i] == 'D' || invEditTranscript[i] == 'X'); invEditTranscript[i++] = 'S');
    for (unsigned i = invEditTranscript.length() - 1; i >= 0 && (invEditTranscript[i] == 'D' || invEditTranscript[i] == 'X'); invEditTranscript[i--] = 'S');
    Str invUnpacked = Str(invEditTranscript);
    Str unpacked = StrFact::inverse(invUnpacked, false);
    Str cigar = StrFact::rlEncode(unpacked, false);

    for (unsigned i = 0; i < rows; i++) {
        delete[] mem[i];
    }
    delete[] mem;
    for (unsigned i = 0; i < rows; i++) {
        delete dir[i];
    }
    delete[] dir;

    return StrSimMatch(basePos + leftEnd, score, cigar);
}

ostream& operator<<(std::ostream& os, const StrSimMatch& ssm) {
    return os << "(" << ssm.pos << ", " << ssm.score << ", " << ssm.cigar << ")";
}
