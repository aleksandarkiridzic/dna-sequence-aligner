#include "../str.h"
#include "../strutil.h"
#include "../strfact.h"
#include "../fmstr.h"
#include "../exceptions.h"

#include <iostream>
#include <cstring>
#include <vector>

using namespace::std;

void bwtAndPackAndInverseTest() {
    try {
        // string test = "^banana";
        //string test = "The output is easier to compress because it has many repeated characters. In this example the transformed string, there are a total of eight runs of identical characters: XX, II, XX, SS, PP, .., II, and III, which together make 17 out of the 44 characters.";
        string test = "GATCACAGGTCTATCACCCTATTAACCACTCACGGGAGCTCTCCATGCATTTGGTATTTTCGTCTGGGGGGTATGCACGCGATAGCATTGCGAGACGCTGGAGCCGGAGCACCCTATGTCGCAGTATCTGTCTTTGATTCCTGCCTCATCCTATTATTTATCGCACCTACGTTCAATATTACAGGCGAACATACTTACTAAAGTGTGTTAATTAATTAATGCTTGTAGGACATAATAATAACAATTGAATGTCTGCACAGCCACTTTCCACACAGACATCATAACAAAAAATTTCCACCAAACCCCCCCTCCCCCGCTTCTGGCCACAGCACTTAAACACATCTCTGCCAAACCCCAAAAACAAAGAACCCTAACACCAGCCTAACCAGATTTCAAATTTTATCTTTTGGCGGTATGCACTTTTAACAGTCACCCCCCAACTAACACATTATTTTCCCCTCCCACTCCCATACTACTAATCTCATCAATACAACCCCCGCCCATCCTACCCAGCACACACACACCGCTGCTAACCCCATACCCCGAACCAACCAAACCCCAAAGACACCCCCCACAGTTTATGTAGCTTACCTCCTCAAAGCAATACACTGAAAATGTTTAGACGGGCTCACATCACCCCATAAACAAATAGGTTTGGTCCTAGCCTTTCTATTAGCTCTTAGTAAGATTACACATGCAAGCATCCCCGTTCCAGTGAGTTCACCCTCTAAATCACCACGATCAAAAGGAACAAGCATCAAGCACGCAGCAATGCAGCTCAAAACGCTTAGCCTAGCCACACCCCCACGGGAAACAGCAGTGATTAACCTTTAGCAATAAACGAAAGTTTAACTAAGCTATACTAACCCCAGGGTTGGTCAATTTCGTGCCAGCCACCGCGGTCACACGATTAACCCAAGTCAATAGAAGCCGGCGTAAAGAGTGTTTTAGATCACCCCCTCCCCAATAAAGCTAAAACTCACCTGAGTTGTAAAAAACTCCAGTTGACACAAAATAGACTACGAAAGTGGCTTTAACATATCTGAACACACAATAGCTAAGACCCAAACTGGGATTAGATACCCCACTATGCTTAGCCCTAAACCTCAACAGTTAAATCAACAAAACTGCTCGCCAGAACACTACGAGCCACAGCTT";
        Str str(test.c_str(), test.length());
        cout << str << endl;
        FMStr fmstr = StrFact::constructFMStr(str, 1, 1);
        cout << fmstr << endl;
        str = fmstr.inverse();
        cout << str << endl;
        fmstr.pack();
        cout << fmstr << endl << fmstr.length() << endl;
        fmstr.unpack();
        cout << fmstr << endl << fmstr.length() << endl;
    }
    catch (BetterException& be) {
        cout << be.message();
    }
}

void sparseBwtAndInverseTest() {
    try {
        // string test = "^banana";
        string test = "abracadabra";
        //string test = "The output is easier to compress because it has many repeated characters. In this example the transformed string, there are a total of eight runs of identical characters: XX, II, XX, SS, PP, .., II, and III, which together make 17 out of the 44 characters.";
        Str str(test.c_str(), test.length());
        cout << str << endl;
        FMStr fmstr = StrFact::constructFMStr(str, 3, 3);
        cout << fmstr << endl;
        fmstr.info(cout);
        str = fmstr.inverse();
        cout << str << endl;
    }
    catch (BetterException& be) {
        cout << be.message();
    }
}

void exactMatchTest() {
    try {
        // string test = "^banana";
        string referenceStr = "The Burrows–Wheeler transform (BWT, also called block-sorting compression) rearranges a character string into runs of similar characters. This is useful for compression, since it tends to be easy to compress a string that has runs of repeated characters by techniques such as move-to-front transform and run-length encoding. More importantly, the transformation is reversible, without needing to store any additional data. The BWT is thus a \"free\" method of improving the efficiency of text compression algorithms, costing only some extra computation.";
        // string referenceStr = "aaaaa";
        Str reference(referenceStr);
        cout << reference << endl;
        FMStr fmRef = StrFact::constructFMStr(reference, 2, 2);
        cout << fmRef << endl;
        // fmRef.info();
        string patternStr = "ion";
        Str pattern(patternStr);
        vector<unsigned> allPos = fmRef.allPos(pattern);
        for (auto const& pos: allPos) {
            cout << pos << " ";
        }
        cout << endl;
    }
    catch (BetterException& be) {
        cout << be.message();
    }
}
/*
int main(int argc, char* args[]) {
    // bwtAndPackAndInverseTest();
    // sparseBwtAndInverseTest();
    exactMatchTest();
}*/
