#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

constexpr unsigned CHARSIZE_BITS = 8;
constexpr unsigned TOTAL_CHARS = 1 << (sizeof(char) * CHARSIZE_BITS);
constexpr unsigned UNSIGNED_TOP_BIT = 1 << (sizeof(unsigned) * CHARSIZE_BITS - 1);

#define immutable_class class
#define immutable_struct struct
#define utility_class class

typedef unsigned char byte;

#endif // GENERAL_H_INCLUDED
