#include "strsimilarity.h"
#include "strfact.h"

#include <algorithm>
#include <sstream>

using namespace std;

StrSimilarity::StrSimilarity(vector<char> alphabet, const int** table): table(table), activeChars(alphabet.size()) {
    unsigned* ch2indInit = new unsigned[TOTAL_CHARS];
    fill_n(ch2indInit, TOTAL_CHARS, activeChars + 1);
    for (unsigned i = 0; i < alphabet.size(); i++) {
        ch2indInit[(byte)alphabet[i]] = i;
    }
    ch2ind = ch2indInit;
}

StrSimMatch StrSimilarity::occurence(const Str& pat, const Str& str) {
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

    Str invUnpacked = Str(oss.str());
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

    return StrSimMatch(leftEnd, score, cigar);
}

ostream& operator<<(std::ostream& os, const StrSimMatch& ssm) {
    return os << "(" << ssm.pos << ", " << ssm.score << ", " << ssm.cigar << ")";
}
