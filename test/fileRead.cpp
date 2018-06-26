#include "../fasta.h"
#include "../exceptions.h"
#include "../strutil.h"

#include <iostream>

using namespace::std;

int main(int argc, char* args[]) {
    try {
        Str str = readFasta("C:\\Users\\Aleksandar\\Desktop\\genomics\\DNA Sequence Aligner\\data\\MT.fa");
        //Str str = readFasta(args[1]);
        StrUtil::sample(str, 3, cout);
        cout << str.length() << endl;
        StrUtil::histogram(str, cout);
    }
    catch (BetterException& e) {
        cout << e.message() << endl;
    }
    return 0;
}
