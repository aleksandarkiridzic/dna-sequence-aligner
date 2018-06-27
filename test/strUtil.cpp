#include "../strutil.h"
#include "../str.h"

#include <iostream>
#include <cstring>

using namespace::std;

int main(int argc, char* args[]) {
    //string test = "banana";
    string test = "abracadabra";
    Str str(test.c_str(), test.length());
    unsigned* sufArr;
    StrUtil::constructSuffixArray(str, sufArr);
    for (unsigned i = 0; i <= str.length(); i++) {
        cout << sufArr[i] << " ";
    }
    cout << endl;
}
