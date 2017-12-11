// File md5hash.h for class MD5Hash and file md5.cpp

#ifndef MD5HASH_H
#define MD5HASH_H

#include <QString>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* the following line are added by J. Schulze-Wenck July 2007 */
/* default setting: compile for a 64 bit OS */
/* comment out this line if you compile with a 32 bit Compiler */
#define X86_64

/* POINTER defines a generic pointer type */
typedef unsigned char *POINTER;

/* UINT2 defines a two byte word */
typedef unsigned short int UINT2;

/* the following lines are changed by J. Schulze-Wenck July 2007 */
/* UINT4 defines a four byte word */
#ifndef X86_64      
    typedef unsigned long int UINT4;        // 32 bit OS
#else
    typedef unsigned int UINT4;     // 64 bit OS
#endif

/* MD5 context. */
typedef struct {
  UINT4 state[4];                                   /* state (ABCD) */
  UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;

/* Constants for MD5Transform routine.
 */

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21



/* F, G, H and I are basic MD5 functions.
 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits.
 */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation.
 */
#define FF(a, b, c, d, x, s, ac) { \
 (a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) { \
 (a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) { \
 (a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) { \
 (a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

class MD5Hash
{
    public:
        MD5Hash(void);
        ~MD5Hash();

        void MD5Init (void);
        void MD5Update (unsigned char *input, unsigned int inputLen);
        void MD5Final (unsigned char digest[16]);
        void MD52hex(char md5hex[33], unsigned char digest[16]);
        void MD5TestSuite(void);

        void MD5File(const char *filename, unsigned char result[16]);
        void MD5String(char* byteArray, unsigned int quantity, unsigned char result[16]);

    private:
        MD5_CTX *context;
        unsigned char* PADDING;

        void MD5Transform (UINT4 [4], unsigned char [64]);
        void Encode (unsigned char *, UINT4 *, unsigned int);
        void Decode (UINT4 *, unsigned char *, unsigned int);
        void PrintTestSuite(QString t, unsigned char r[16]);
};


#endif
