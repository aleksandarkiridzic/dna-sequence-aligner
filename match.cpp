#include "match.h"

using namespace std;

void ReadMatch::seed(const FMStr& refGenome, unsigned sl, unsigned si) {
    seedLength = sl;
    seedInterval = si;

    for (unsigned i = 0; i + seedLength <= read.seq.length(); i += seedInterval) {
        Str seed = read.seq.subStr(i, seedLength);
        vector<unsigned> matches = refGenome.allPos(seed);
        /*if (matches.size() > 1) {
            cout << read.ident << " " << i << endl;
            cout << seed << " " << matches[0] <<  " "  << matches[1] << "\n\n";
        }*/
        sms.push_back(SeedMatch(i, matches));
    }

    state = SEEDED;

    /*
    for (unsigned q = 0; q < sms.size(); q++)
        if (sms[q].matches.size() > 1) {
            cout << read.seq.subStr(sms[q].pos, seedLength) << " -- " << sms[q].pos << endl;
            for (unsigned c = 0; c < sms[q].matches.size(); c++) {
                cout << sms[q].matches[c] << " ";
            }
            cout << endl;
        }
*/
    /*{
        for (unsigned i = 0; i < sms.size(); i++) {
            cout << read.seq.subStr(sms[i].pos, seedLength) << " -- " << sms[i].pos << endl;
            for (unsigned c = 0; c < sms[i].matches.size(); c++) {
                cout << sms[i].matches[c] << " ";
            }
            cout << endl;
        }
    }*/
}
