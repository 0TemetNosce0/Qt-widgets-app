/*MD5.CPP based on the RSA Data Security, Inc. MD5 Message-Digest
Algorithm 5, published in the document RFC 1321 (http://www.ietf.org/rfc/rfc1321.txt)
Ported to C++ 2007 by J. Schulze-Wenck.
updated 2009 by J. Schulze-Wenck

The original source text was as far as possible unmodified taken over, in order not to reduce high speed of operation.
*/

/* MD5C.C - RSA Data Security, Inc., MD5 message-digest algorithm
 */

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.
 */

#include "md5hash.h"
//#include "md5TestStrings.cpp"

MD5Hash::MD5Hash(void)
{
    int i;

    context=new MD5_CTX;
    
    PADDING=new unsigned char[64];
    PADDING[0]=0x80;
    for(i=1; i<64; i++)
        PADDING[i]=0;
}

MD5Hash::~MD5Hash()
{
    delete context;
    delete PADDING;
}

/* MD5 initialization. Begins an MD5 operation, writing a new context.*/
void MD5Hash::MD5Init(void)
{
    context->count[0] = context->count[1] = 0;
    /* Load magic initialization constants.
*/
    context->state[0] = 0x67452301;
    context->state[1] = 0xefcdab89;
    context->state[2] = 0x98badcfe;
    context->state[3] = 0x10325476;
}

/* MD5 block update operation. Continues an MD5 message-digest
  operation, processing another message block, and updating the
  context.void MD5Update (unsigned char *, unsigned int);
 */
void MD5Hash::MD5Update(unsigned char *input, unsigned int inputLen)
{
    unsigned int i, index, partLen;
    
    /* Compute number of bytes mod 64 */
    index = (unsigned int)((context->count[0] >> 3) & 0x3F);

    /* Update number of bits */
    if ((context->count[0] += ((UINT4)inputLen << 3)) < ((UINT4)inputLen << 3))
        context->count[1]++;

    context->count[1] += ((UINT4)inputLen >> 29);

    partLen = 64 - index;

    /* Transform as many times as possible.*/
    if (inputLen >= partLen)
    {
        memcpy((POINTER)&context->buffer[index], (POINTER)input, partLen);
        MD5Transform (context->state, context->buffer);

        for (i = partLen; i + 63 < inputLen; i += 64)
            MD5Transform (context->state, &input[i]);

        index = 0;
    }
    else
        i = 0;

    /* Buffer remaining input */
    memcpy((POINTER)&context->buffer[index], (POINTER)&input[i], inputLen-i);
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the
  the message digest and zeroizing the context.
 */
void MD5Hash::MD5Final(unsigned char digest[16])
//unsigned char digest[16]            Returnvalue MD5 
{
    unsigned char bits[8];
    unsigned int index, padLen;

    /* Save number of bits */
    Encode (bits, context->count, 8);

    /* Pad out to 56 mod 64.*/
    index = (unsigned int)((context->count[0] >> 3) & 0x3f);
    padLen = (index < 56) ? (56 - index) : (120 - index);
    MD5Update (PADDING, padLen);

    /* Append length (before padding) */
    MD5Update (bits, 8);

    /* Store state in digest */
    Encode (digest, context->state, 16);

    /* Zeroize sensitive information.*/
    memset((POINTER)context, 0, sizeof (*context));
}

/* MD5 basic transformation. Transforms state based on block.*/
void MD5Hash::MD5Transform (UINT4* state, unsigned char* block)
{
    UINT4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];

    Decode (x, block, 64);

    /* Round 1 */
    FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
    FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
    FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
    FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
    FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
    FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
    FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
    FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
    FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
    FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
    FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
    FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
    FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
    FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
    FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
    FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

    /* Round 2 */
    GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
    GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
    GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
    GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
    GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
    GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
    GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
    GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
    GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
    GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
    GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
    GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
    GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
    GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
    GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
    GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

    /* Round 3 */
    HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
    HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
    HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
    HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
    HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
    HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
    HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
    HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
    HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
    HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
    HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
    HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
    HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
    HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
    HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
    HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

    /* Round 4 */
    II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
    II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
    II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
    II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
    II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
    II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
    II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
    II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
    II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
    II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
    II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
    II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
    II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
    II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
    II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
    II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;

    /* Zeroize sensitive information.*/
    memset((POINTER)x, 0, sizeof (x));
}

/* Encodes input (UINT4) into output (unsigned char). Assumes len is
    a multiple of 4.*/
void MD5Hash::Encode (unsigned char *output, UINT4 *input, unsigned int len)
{
    unsigned int i, j;

    for (i = 0, j = 0; j < len; i++, j += 4)
    {
        output[j] = (unsigned char)(input[i] & 0xff);
        output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
        output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
        output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
    }
}

/* Decodes input (unsigned char) into output (UINT4). Assumes len is
    a multiple of 4.*/
void MD5Hash::Decode (UINT4 *output, unsigned char *input, unsigned int len)
{
    unsigned int i, j;

    for (i = 0, j = 0; j < len; i++, j += 4)
        output[i] = ((UINT4)input[j]) | (((UINT4)input[j+1]) << 8) |
                (((UINT4)input[j+2]) << 16) | (((UINT4)input[j+3]) << 24);
}

void MD5Hash::MD5File(const char *filename, unsigned char result[16])
//the parameter result return the MD5 hash from the open file file
{
    unsigned char buffer [1024];

    ifstream infile(filename, ios_base::in | ios_base::binary);

    if(infile.good())
    {
        MD5Init ();

        while (!infile.eof())
        {
            infile.read((char*) buffer, 1024);
            MD5Update (buffer, infile.gcount());
        }

        MD5Final(result);

        infile.close();
    }
    else
        cout <<     "Can't file open!\n";
}

void MD5Hash::MD5String(char* byteArray, unsigned int quantity, unsigned char result[16])
//the parameter result return the MD5 hash from the given bytearray
{
    MD5Init();
    MD5Update ((unsigned char*)byteArray, quantity);
    MD5Final (result);
}

/* Transform the hash into hexadecimal.*/
void MD5Hash::MD52hex(char md5hex[33], unsigned char digest[16])
//output md5hex = digest as nullterminated hexadecimal string 
{
    unsigned int i;
    
    for (i = 0; i < 16; i++)
    {
        sprintf (md5hex, "%02x", digest[i]);
        md5hex++;
        md5hex++;
    }
}

/* Digests a reference suite of strings and prints the results.*/
void MD5Hash::MD5TestSuite(void)
{
    unsigned char r[16];
    
    QString testData[10];

    testData[0] = "";
    testData[1] = "<Empty string>";
    testData[2] = "a";
    testData[3] = "abc";
    testData[4] = "message digest";
    testData[5] = "abcdefghijklmnopqrstuvwxyz";
    testData[6] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    testData[7] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
    testData[8] = "The quick brown fox jumps over the lazy dog";
    testData[9] = "The quick brown fox jumps over the lazy dog.";
    

    cout<<"MD5 test suite. For the results look into the readme file\n";

    /*MD5String ("", 0, r);
    PrintTestSuite("<Empty string>", r);
    MD5String ("a", 1, r);
    PrintTestSuite("a", r);
    MD5String ("abc", 3, r);
    PrintTestSuite("abc", r);
    MD5String ("message digest", 14, r);
    PrintTestSuite("message digest", r);
    MD5String ("abcdefghijklmnopqrstuvwxyz", 26, r);
    PrintTestSuite("abcdefghijklmnopqrstuvwxyz", r);
    MD5String ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", 62, r);
    PrintTestSuite("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", r);
    MD5String ("12345678901234567890123456789012345678901234567890123456789012345678901234567890", 80, r);
    PrintTestSuite("12345678901234567890123456789012345678901234567890123456789012345678901234567890", r);
    MD5String("The quick brown fox jumps over the lazy dog", 43, r);
    PrintTestSuite("The quick brown fox jumps over the lazy dog", r);
    MD5String("The quick brown fox jumps over the lazy dog.", 44, r);
    PrintTestSuite("The quick brown fox jumps over the lazy dog.", r);*/
    
    MD5String(testData[0].toLatin1().data(), 0, r);
    PrintTestSuite(testData[1], r);
    MD5String(testData[2].toLatin1().data(), 1, r);
    PrintTestSuite("a", r);
    MD5String(testData[3].toLatin1().data(), 3, r);
    PrintTestSuite("abc", r);
    MD5String(testData[4].toLatin1().data(), 14, r);
    PrintTestSuite("message digest", r);
    MD5String (testData[5].toLatin1().data(), 26, r);
    PrintTestSuite("abcdefghijklmnopqrstuvwxyz", r);
    MD5String (testData[6].toLatin1().data(), 62, r);
    PrintTestSuite("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", r);
    MD5String (testData[7].toLatin1().data(), 80, r);
    PrintTestSuite("12345678901234567890123456789012345678901234567890123456789012345678901234567890", r);
    MD5String(testData[8].toLatin1().data(), 43, r);
    PrintTestSuite("The quick brown fox jumps over the lazy dog", r);
    MD5String(testData[9].toLatin1().data(), 44, r);
    PrintTestSuite("The quick brown fox jumps over the lazy dog.", r);
}

void MD5Hash::PrintTestSuite(QString t, unsigned char r[16])
{
    //Output of the result to stdout
    char md5hex[33];
    
    MD52hex(md5hex, r);
    
    if(t.size()>28)
    {
        cout << "MD5 of: " << t.toLatin1().data() << "\n" << " = " << md5hex << "\n\n";
    }
    else
    {
        cout << "MD5 of: " << t.toLatin1().data() << " = " << md5hex << "\n\n";
    }
}
