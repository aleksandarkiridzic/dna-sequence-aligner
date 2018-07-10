#include "../str.h"
#include "../strutil.h"
#include "../strfact.h"
#include "../strsimilarity.h"
#include "../sim.h"

#include <iostream>
#include <cstring>
#include <iomanip>

using namespace::std;

void constructSuffixArrayTest() {
    //string test = "banana";
    string test = "abracadabra";
    Str str(test.c_str(), test.length());
    unsigned* sufArr;
    StrFact::constructSuffixArray(str, sufArr);
    for (unsigned i = 0; i <= str.length(); i++) {
        cout << sufArr[i] << " ";
    }
    cout << endl;
}

void encodeAndInverseTest() {
    //string test = "banana";
    Str test("aaankcleeenkccc");
    cout << StrFact::rlEncode(test) << endl << StrFact::inverse(test);
}

void strSimTest() {
    //string test = "banana";
    StrSimilarity strSim = Sim::read("C:\\Users\\Aleksandar\\Desktop\\genomics\\DNA Sequence Aligner\\data\\default.sim");
    Str str("AAAAACCCAAAAAA");
    Str pat("GTCCCGT");
    StrSimMatch ssm = strSim.occurence(pat, str);
    cout << ssm << endl;
}

void strWriteTest() {
    Str str("testtest");
    cout << setw(20) << left << str << "dovde";
}

void bwtTest() {
    string test = "ana voli milovana";
    // string test = "abracadabra";
    Str str(test.c_str(), test.length());
    unsigned* sufArr = nullptr;
    Str bwtStr = StrFact::bwt(str, sufArr);
    cout << bwtStr << endl;
    for (unsigned i = 0; i <= str.length(); i++) {
        cout << sufArr[i] << " ";
    }
    cout << endl;
}
/*
int main(int argc, char* args[]) {
    //constructSuffixArrayTest();
    // bwtTest();
    // encodeAndInverseTest();
    // strSimTest();
    strWriteTest();
}
*/
