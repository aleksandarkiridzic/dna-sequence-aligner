#ifndef SIM_H_INCLUDED
#define SIM_H_INCLUDED

#include "strsimilarity.h"
#include "general.h"

// utility class for working with sim files
utility_class Sim {
public:
    static StrSimilarity read(const char* filePath);
};

#endif // SIM_H_INCLUDED
