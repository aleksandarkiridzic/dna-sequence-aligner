#include "../str.h"
#include "../strutil.h"
#include "../strfact.h"
#include "../suffixarray.h"

#include <iostream>
#include <cstring>

using namespace::std;

void suffixArrayTest() {
    string test = "abracadabra";
    Str str(test.c_str(), test.length());
    SuffixArray fullSufArr(str, 1);
    cout << fullSufArr << endl;
    SuffixArray sparseSufArr(str, 2);
    cout << sparseSufArr << endl;
    cout << sparseSufArr[0] << " " << sparseSufArr[11] << endl;
}

int main(int argc, char* args[]) {
    suffixArrayTest();
}
