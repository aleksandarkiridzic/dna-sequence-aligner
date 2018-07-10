#include "exceptions.h"
#include "range.h"
#include "fasta.h"
#include "fmstr.h"
#include "read.h"
#include "strfact.h"
#include "fastq.h"
#include "aligner.h"

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <exception>

using namespace::std;

// required
char* fa = nullptr;
char* fq = nullptr;
char* sam = nullptr;
// required with a default value
pair<unsigned, unsigned> sparseFM = pair<unsigned, unsigned>(1, 1);
// optional
Range range = Range(0, 0);
char* sim = nullptr;
pair<unsigned, unsigned> seed;
pair<float, unsigned> window;

string commands[] = {  "fa",    "fq",   "sam",  "sparsefm", "range",    "sim",  "seed", "window" };
enum Commands {         FA,     FQ,     SAM,    SPARSEFM,   RANGE,      SIM,    SEED,   WINDOW };
unsigned argNum[] = {   1,      1,      1,      2,          2,          1,      2,      2 };
char** strArgs[] = {    &fa,    &fq,    &sam,   nullptr,    nullptr,    &sim,   nullptr,nullptr};
pair<unsigned, unsigned>* pairNumArgs[] =
                    {   nullptr,nullptr,nullptr,&sparseFM,  nullptr,    nullptr,&seed,  nullptr};
constexpr unsigned TOTAL_COMMANDS = sizeof(commands) / sizeof(*commands);
bool argFound[TOTAL_COMMANDS] = { false };



int checkCommand(const char* command) {
    if (command[0] != '-') {
        throw CommandSignException(command);
    }

    for (unsigned i = 0; i < TOTAL_COMMANDS; i++) {
        if (commands[i].compare(command + 1) == 0) {    // compare without starting '-' sign
            return i;                                   // index if found
        }
    }

    return -1;                                          // -1 if not found
}

int main(int argc, char* args[]) {
    try {
        for (int i = 1; i < argc; i++) {            // read all arguments
            const char* command = args[i];
            switch (int ind = checkCommand(command)) {
                case FA:                            // one string argument
                case FQ:
                case SAM:
                case SIM:
                    if (i + 1 >= argc) {
                        throw ArgumentNumberException(command + 1, argNum[ind]);
                    }
                    *strArgs[ind] = args[++i];
                    argFound[ind] = true;
                    break;
                case SPARSEFM:                      // two unsigned arguments
                case SEED:
                    if (i + 2 >= argc) {
                        throw ArgumentNumberException(command + 1, argNum[ind]);
                    }
                    unsigned arg1, arg2;
                    try { arg1 = stoul(args[++i]); }
                    catch (exception& e) { throw ArgumentTypeException(command + 1, args[i]); }
                    try { arg2 = stoul(args[++i]); }
                    catch (exception& e) { throw ArgumentTypeException(command + 1, args[i]); }
                    *pairNumArgs[ind] = pair<unsigned, unsigned>(arg1, arg2);
                    argFound[ind] = true;
                    break;
                case RANGE:                         // two unsigned arguments
                    if (i + 2 >= argc) {
                        throw ArgumentNumberException(command + 1, argNum[ind]);
                    }
                    unsigned arg1r, arg2r;
                    try { arg1r = stoul(args[++i]); }
                    catch (exception& e) { throw ArgumentTypeException(command + 1, args[i]); }
                    try { arg2r = stoul(args[++i]); }
                    catch (exception& e) { throw ArgumentTypeException(command + 1, args[i]); }
                    range = Range(arg1r - 1, arg2r);
                    argFound[ind] = true;
                    break;
                case WINDOW:                        // one float argument
                    if (i + 2 >= argc) {
                        throw ArgumentNumberException(command + 1, argNum[ind]);
                    }
                    float argf; unsigned argu;
                    try { argf = stof(args[++i]); }
                    catch (exception& e) { throw ArgumentTypeException(command + 1, args[i]); }
                    try { argu = stoul(args[++i]); }
                    catch (exception& e) { throw ArgumentTypeException(command + 1, args[i]); }
                    window = pair<float, unsigned>(argf, argu);
                    argFound[ind] = true;
                    break;
                default:
                    throw CommandNotExistsException(command + 1);
                    break;
            }
        }

       /* cout << fa << endl
            << fq << endl
            << sam << endl
            << sparseFM.first << " " << sparseFM.second << endl
            << range << endl
            << sim << endl
            << seed.first << " " << seed.second << endl
            << window << endl;
        getchar();*/

        if (!(argFound[FA] && argFound[FQ] && argFound[SAM])) { // check required arguments
            throw RequiredArgumentException();
        }

        Str refStr = Fasta::read(fa);
        FMStr fmRef = StrFact::constructFMStr(refStr, sparseFM.first, sparseFM.second);
        Read::setAlphabet({'A', 'C', 'G', 'T'});
        vector<Read> reads = Fastq::read(fq);
        Aligner aligner(fmRef, reads);
        if (argFound[SEED]) {
            aligner.setSeedParameters(seed.first, seed.second);
        }
        if (argFound[WINDOW]) {
            aligner.setWindowReadRatio(window.first);
            aligner.setMaxWindows(window.second);
        }
        if (argFound[SIM]) {
            StrSimilarity strSim = Sim::read(sim);
            aligner.setScoringMatrix(strSim);
        }
        if (argFound[RANGE] && range.low < reads.size() && range.high < reads.size()) {
            aligner.align(range, sam);
        }
        else {
            aligner.alignAll(sam);
        }

        cout << "Done!\n";
    }
    catch (BetterException& e) {
        cout << e.message() << endl;
    }
    return 0;
}
