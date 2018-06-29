#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <exception>
#include <sstream>

#include "str.h"
#include "strutil.h"

class BetterException : std::exception {
public:
    virtual std::string message() = 0;
};

struct FileNotFoundException : BetterException {
    const char* filePath;
    FileNotFoundException(const char* filePath) : filePath(filePath) {}
    std::string message() override {
        std::ostringstream output;
        output << "File " << filePath << " not found.";
        return output.str();
    }
};

struct IndexOutOfBoundsException : BetterException {
    int index, bound;
    IndexOutOfBoundsException(int index, int bound) : index(index), bound(bound) {}
    std::string message() override {
        std::ostringstream output;
        output << "Index " << index << " out of bounds [0, " << bound << "].";
        return output.str();
    }
};

struct NoCharInStrException : BetterException {
    char ch;
    const Str& str;
    NoCharInStrException(char ch, const Str& str) : ch(ch), str(str) {}
    std::string message() override {
        std::ostringstream output;
        StrUtil::printChar(output << "No ", ch) << " in ";
        StrUtil::sample(str, 4, output);
        return output.str();
    }
};

#endif // EXCEPTIONS_H_INCLUDED
