// blowfish.h     interface file for blowfish.cpp
// _THE BLOWFISH ENCRYPTION ALGORITHM_
// by Bruce Schneier
// Revised code--3/20/94
// Converted to C++ class 5/96, Jim Conger

#ifndef _BLOWFISH_H //added for using in a project by J. Schulze-Wenck 1/01
#define _BLOWFISH_H

#define MAXKEYBYTES     56      // 448 bits max
#define NPASS           16      // SBox passes

/* the following line are added by J. Schulze-Wenck July 2007 */
/* default setting: compile for a 64 bit OS */
/* comment out this line if you compile with a 32 bit Compiler */
#define X86_64

#ifndef X86_64
#define DWORD unsigned long     // 32 bit OS
#else
#define DWORD unsigned int          // 64 bit OS
#endif

#define WORD        unsigned short
#define BYTE        unsigned char

class CBlowFish
{
public:
    CBlowFish();
    ~CBlowFish();

    void        initialize(BYTE key[], int keybytes) ;
    DWORD       getOutputLength(DWORD lInputLong) ;
    DWORD       encode(BYTE * pInput, BYTE * pOutput, DWORD lSize) ;
    void        decode(BYTE * pInput, BYTE * pOutput, DWORD lSize) ;

private:
    DWORD       * PArray ;
    DWORD       (* SBoxes)[256];
    void        blowfishEncipher(DWORD *xl, DWORD *xr) ;
    void        blowfishDecipher(DWORD *xl, DWORD *xr) ;
} ;

// choose a byte order for your hardware
#define ORDER_DCBA  // chosing Intel in this case

#ifdef ORDER_DCBA   // DCBA - little endian - intel
union aword {
    DWORD dword;
    BYTE byte [4];
    struct {
        unsigned int byte3:8;
        unsigned int byte2:8;
        unsigned int byte1:8;
        unsigned int byte0:8;
    } w;
};
#endif

#ifdef ORDER_ABCD   // ABCD - big endian - motorola
union aword {
    DWORD dword;
    BYTE byte [4];
    struct {
        unsigned int byte0:8;
        unsigned int byte1:8;
        unsigned int byte2:8;
        unsigned int byte3:8;
    } w;
};
#endif

#ifdef ORDER_BADC   // BADC - vax
union aword {
    DWORD dword;
    BYTE byte [4];
    struct {
        unsigned int byte1:8;
        unsigned int byte0:8;
        unsigned int byte3:8;
        unsigned int byte2:8;
    } w;
};
#endif

#endif


