#include "../str.h"
#include "../strutil.h"
#include "../strfact.h"
#include "../suffixarray.h"
#include "../exceptions.h"

#include <iostream>
#include <cstring>

using namespace::std;

void suffixArrayTest() {
    try {
        string test = "abracadabra";
        Str str(test.c_str(), test.length());
        SuffixArray fullSufArr(str, 1);
        cout << fullSufArr << endl;
        SuffixArray sparseSufArr = fullSufArr.sparse(2, false);
        cout << sparseSufArr << endl;
        cout << sparseSufArr[0] << " " << sparseSufArr[11] << endl;
        // cout << fullSufArr << endl;
    }
    catch (BetterException& be) {
        cout << be.message();
    }
}
/*
int main(int argc, char* args[]) {
    suffixArrayTest();
}
*/
