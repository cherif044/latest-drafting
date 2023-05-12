#ifndef RKSENTENCES_H
#define RKSENTENCES_H
#pragma once
#include "RabinKarp.h"
#include "File.h"




class Sentences : public RabinKarp{
public:
    //Function that counts the number of sentneces in string and returns the number
    //Used as the looping parameter for for loop
    int numberOfSentences(string str);

    //Functions where the RabinKarp algorithm is applied using Quadratic hashing and FingerPrint hashing respectively
    //Here the pattern is sentences
    //Double hashing in applied for any collisions
    unordered_map<string, string> rabinKarpPolySentences(string main, string c1, string c2, string c3);
    unordered_map<string, string> rabinKarpFingerPrintSentences(string main, string c1, string c2, string c3);
};
#endif // RKSENTENCES_H
