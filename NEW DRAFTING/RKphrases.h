#ifndef RKPHRASES_H
#define RKPHRASES_H
#pragma once
#include "RabinKarp.h"
#include "File.h"


class Phrases : public RabinKarp {
public:
    //Function that calculates the number of phrases and returns the number
    //Used as the looping parameter for for loop
    int numberOfPhrases(int length, int phrases);

    //Functions where the RabinKarp algorithm is applied using Quadratic hashing and FingerPrint hashing respectively
    //Here the pattern is phrases or variable sizes to increase accuracy
    //Double hashing in applied for any collisions
    unordered_map<string, string> rabinKarpPolyPhrases(string main, string c1, string c2, string c3, int words);
    unordered_map<string, string> rabinKarpFingerPrintPhrases(string main, string c1, string c2, string c3, int words);


};
#endif // RKPHRASES_H
