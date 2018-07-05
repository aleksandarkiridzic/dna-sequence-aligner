#include "fastq.h"
#include "exceptions.h"
#include "str.h"

#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

vector<Read> Fastq::read(const char* filePath) {
    ifstream input(filePath);
    if (!input.is_open()) {
        throw FileNotFoundException(filePath);
    }

    vector<Read> result;
    ReaderState next = ID;
    unsigned lineCnt = 0;
    string line;
    ostringstream iss;
    Str ident, seq, qual;

    while(getline(input, line)) {
        lineCnt++;
        if (!line.empty()) {                // skip empty lines
            switch (next) {
            case ID:
                ident = Str(line);
                next = SEQ;
                break;
            case SEQ:
                seq = Str(line);
                next = PLUS;
                break;
            case PLUS:
                if (line[0] != '+') {
                    throw ReadIllegalDefException(lineCnt);
                }
                next = QUAL;
                break;
            case QUAL:
                qual = Str(line);
                next = ID;
                result.push_back(Read(ident, seq, qual));
                break;
            }
        }
    }

    if (next != ID) {
        throw ReadIllegalDefException(lineCnt);
    }

    input.close();

    return result;
}
