#include "fasta.h"
#include "exceptions.h"

#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

Str Fasta::read(const char* filePath) {
    ifstream input(filePath);
    if (!input.is_open()) {
        throw FileNotFoundException(filePath);
    }

    string line;
    ostringstream iss;
    while(getline(input, line)) {
        if (!line.empty() && line[0] != '>' && line[0] != ';') { // if not comments
            iss << line;
        }
    }

    input.close();

    string result = iss.str();
    unsigned len = result.length();
    return Str(result.c_str(), len);
}
