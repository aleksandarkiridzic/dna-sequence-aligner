#include "../fasta.h"
#include "../fastq.h"
#include "../exceptions.h"
#include "../strfact.h"
#include "../read.h"
#include "../aligner.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace::std;

int sneTest() {
    try {
        Str refStr = Fasta::read("C:\\Users\\Aleksandar\\Desktop\\genomics\\DNA Sequence Aligner\\data\\MT.fa");
        FMStr fmRef = StrFact::constructFMStr(refStr, 1, 16);
/*
        ofstream out("C:\\Users\\Aleksandar\\Desktop\\genomics\\DNA Sequence Aligner\\data\\faout16.txt");
        fmRef.info(out << fmRef << endl);
*/
        Read::setAlphabet({'A', 'C', 'G', 'T'});
        vector<Read> reads = Fastq::read("C:\\Users\\Aleksandar\\Desktop\\genomics\\DNA Sequence Aligner\\data\\test.fastq");
        Aligner aligner(fmRef, reads);
        // aligner.setSeedParameters(12, 8);
        StrSimilarity strSim = Sim::read("C:\\Users\\Aleksandar\\Desktop\\genomics\\DNA Sequence Aligner\\data\\test.sim");
        // aligner.setScoringMatrix(strSim);
        aligner.alignAll("C:\\Users\\Aleksandar\\Desktop\\genomics\\DNA Sequence Aligner\\data\\test.sam");
        //aligner.align(0);
    }
    catch (BetterException& e) {
        cout << e.message() << endl;
    }
    return 0;
}
/*
int main(int argc, char* args[]) {
    sneTest();
}
*/
