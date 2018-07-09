#include "sim.h"
#include "exceptions.h"

#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

StrSimilarity Sim::read(const char* filePath) {
    ifstream input(filePath);
    if (!input.is_open()) {
        throw FileNotFoundException(filePath);
    }

    string line;
    vector<char> alphabet;       // first non-empty line represents alphabet
    while(alphabet.empty() && getline(input, line)) {
        if (!line.empty()) {
            istringstream iss(line);
            char ch;
            while (iss >> ch) {
                alphabet.push_back(ch);
            }
        }
    }

    unsigned dim = alphabet.size() + 2;
    int** table = new int*[dim];
    for (unsigned i = 0; i < dim; i++) {
        table[i] = new int[dim];
    }
    unsigned rowCnt = 0;
    while(rowCnt < dim && getline(input, line)) {
        if (!line.empty() && line[0] != '#') {      // line not empty or not comment
            istringstream iss(line);
            char ch = '\0';
            while ((iss >> ch) && (ch != '|'));     // find separator
            if (ch == '|') {                        // separator found
                int n;
                for (unsigned j = 0; (j < dim) && (iss >> n); j++) {
                    table[rowCnt][j] = n;
                }
                rowCnt++;
            }
        }
    }

    input.close();

    return StrSimilarity(alphabet, table);
}
