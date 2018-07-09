#include "../fasta.h"
#include "../fastq.h"
#include "../sim.h"
#include "../exceptions.h"
#include "../strfact.h"
#include "../read.h"
#include "../fmstr.h"
#include "../strsimilarity.h"

#include <iostream>
#include <vector>

using namespace::std;

void readAndPack() {
    try {
        Str str = Fasta::read("C:\\Users\\Aleksandar\\Desktop\\genomics\\DNA Sequence Aligner\\data\\MT.fa");
        cout << str << endl;
        FMStr fmstr = StrFact::constructFMStr(str, 1, 1);
        cout << fmstr << endl;
        fmstr.pack();
        cout << "packed = " << fmstr.length() << endl;
        fmstr.unpack();
        cout << "unpacked = " << fmstr.length() << endl;
    }
    catch (BetterException& be) {
        cout << be.message();
    }
}

int fastaTest() {
    try {
        Str str = Fasta::read("C:\\Users\\Aleksandar\\Desktop\\genomics\\DNA Sequence Aligner\\data\\MT.fa");
        //Str str = readFasta(args[1]);
        StrUtil::sample(str, 3, cout);
        cout << str.length() << endl;
        cout << StrUtil::areAllUpper(str) << endl;
        StrUtil::histogram(str, cout);
    }
    catch (BetterException& e) {
        cout << e.message() << endl;
    }
    return 0;
}

int fastqTest() {
    try {
        vector<Read> reads = Fastq::read("C:\\Users\\Aleksandar\\Desktop\\genomics\\DNA Sequence Aligner\\data\\test.fastq");
        //Str str = readFasta(args[1]);
        cout << reads.size() << endl;
        reads[0].info();
        reads[100].info();
    }
    catch (BetterException& e) {
        cout << e.message() << endl;
    }
    return 0;
}

int simTest() {
    try {
        StrSimilarity strSim = Sim::read("C:\\Users\\Aleksandar\\Desktop\\genomics\\DNA Sequence Aligner\\data\\default.sim");
        strSim.~StrSimilarity();
    }
    catch (BetterException& e) {
        cout << e.message() << endl;
    }
    return 0;
}

/*
int main(int argc, char* args[]) {
    // fastaTest();
    //Read::setAlphabet({'A', 'C', 'G', 'T'});
    //fastqTest();
    //readAndPack();
    simTest();
}*/


