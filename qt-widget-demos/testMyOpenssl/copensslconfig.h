#ifndef COPENSSLCONFIG_H
#define COPENSSLCONFIG_H

/**
   Direction settings for symmetric algorithms

   For some algorithms, it makes sense to have a "direction", such
   as Cipher algorithms which can be used to encrypt or decrypt.
*/
enum Direction
{
    Unknowcode,
    Encode, ///< Operate in the "forward" direction; for example, encrypting
    Decode  ///< Operate in the "reverse" direction; for example, decrypting
};


#endif // COPENSSLCONFIG_H
