#include "../fasta.h"
#include "../fastq.h"
#include "../exceptions.h"
#include "../strutil.h"
#include "../read.h"

#include <iostream>
#include <vector>

using namespace::std;

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
/*
int main(int argc, char* args[]) {
    // fastaTest();
    Read::setAlphabet({'A', 'C', 'G', 'T'});
    fastqTest();
}
*/
