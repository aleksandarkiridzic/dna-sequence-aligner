#include "match.h"
#include "general.h"

#include <algorithm>

using namespace std;

void ReadMatch::seed(const FMStr& refGenome, unsigned sl, unsigned si) {
    if (state != EMPTY) {
        return;
    }

    seedLength = sl;
    seedInterval = si;

    for (unsigned i = 0; i + seedLength <= read.seq.length(); i += seedInterval) {
        Str seedFor = read.seq.subStr(i, seedLength);
        vector<unsigned> matchesFor = refGenome.allPos(seedFor);
        smFor.push_back(SeedMatch(i, matchesFor));

        Str seedRev = read.revComp.subStr(i, seedLength);
        vector<unsigned> matchesRev = refGenome.allPos(seedRev);
        smRev.push_back(SeedMatch(i, matchesRev));
{/*
        if (matchesRev.size() > 1) {
            cout << read.ident << " " << i << endl;
            cout << seedRev << " " << matchesRev[0] << " "  << matchesRev[1] << "\n\n";
        }*/}
    }

    state = SEEDED;

{/*
    for (unsigned q = 0; q < smFor.size(); q++)
        if (smFor[q].matches.size() > 1) {
            cout << read.seq.subStr(smFor[q].pos, seedLength) << " -- " << smFor[q].pos << endl;
            for (unsigned c = 0; c < smFor[q].matches.size(); c++) {
                cout << smFor[q].matches[c] << " ";
            }
            cout << endl;
        }
*/
    /*{
        for (unsigned i = 0; i < smFor.size(); i++) {
            cout << read.seq.subStr(smFor[i].pos, seedLength) << " -- " << smFor[i].pos << endl;
            for (unsigned c = 0; c < smFor[i].matches.size(); c++) {
                cout << smFor[i].matches[c] << " ";
            }
            cout << endl;
        }
    }*/}
}

void ReadMatch::score() {
    if (state != SEEDED) {
        return;
    }

    score(smFor, psFor);
    sort(psFor.begin(), psFor.end());
    score(smRev, psRev);
    sort(psRev.begin(), psRev.end());

    {
        cout << "\n\nforward\n\n";
        for (auto const& ps: psFor) {
            cout << ps.pos << " " << ps.score << endl;
        }
        cout << "\n\nreverse\n\n";
        for (auto const& ps: psRev) {
            cout << ps.pos << " " << ps.score << endl;
        }
    }

    state = SCORED;
}

void ReadMatch::score(std::vector<SeedMatch>& sms, std::vector<PosScore>& pss) {
    for (auto const& sm: sms) {
        //cout << "\npos: " << sm.pos << "\nmatches: " << sm.matches.size() << endl;
        for (auto const& pos: sm.matches) {
            //cout << pos << endl;
            bool exists = false;
            for (unsigned i = 0; i < pss.size() && !exists; i++) {
                if (pss[i].pos == pos) {
                    pss[i].score += sm.uniqueness();
                    exists = true;
                }
            }
            if (!exists) {
                pss.push_back(PosScore(pos, sm.uniqueness()));
            }
        }
    }
}

void ReadMatch::rank(float windowReadRatio) {
    if (state != SCORED) {
        return;
    }

    windowDist = windowReadRatio * read.seq.length();
    windowLength = read.seq.length() + windowDist + read.seq.length();  // one read length to the left, one read length to the right
    calcWindows(psFor, windows, false);
    calcWindows(psRev, windows, true);
    sort(windows.begin(), windows.end());

    {
        cout << "\n\nwindows " << windowLength << "\n\n";
        for (auto const& window: windows) {
            cout << (window.isRevComp() ? "REV " : "FOR ") << window.realPos() << "\t\t" << window.score << endl;
        }
    }


    state = RANKED;
}

void ReadMatch::calcWindows(std::vector<PosScore>& pss, std::vector<Window>& windows, bool isRevComp) {
    auto firstIn = pss.cbegin();
    auto firstOut = pss.cbegin();

    float sumScore = 0;
    while (firstOut != pss.cend()) {
        while (firstOut != pss.cend() && firstIn->pos + windowDist > firstOut->pos) {  // take all new scores inside window
            sumScore += (firstOut++)->score;
        }
        unsigned startPos = firstIn->pos < read.seq.length() ? 0 : firstIn->pos - read.seq.length();
        windows.push_back(Window(isRevComp ? startPos | UNSIGNED_TOP_BIT : startPos, sumScore));
        sumScore -= (firstIn++)->score;
    }
}
