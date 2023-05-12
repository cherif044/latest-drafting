
#include "RKsentences.h"
using namespace std;


//Count the number of sentences in the larger file
int Sentences::numberOfSentences(string str)
{
    int sentences = 0;
    string sub{};
    char c;
    int i = 0;

    for (int i = 0; i < str.length(); i++) {
        //Condition that detects each sentences
        if (str[i] == '.' || str[i] == '?' || str[i] == ',' || str[i] == ';' || str[i] == '!')
        {
            sentences++;
        }

    }


    return sentences;
}

//function that finds which file is longer
string longer(int n, int m, string main, string c) {

    string l{};

    if (m > n)
        l = main;
    else
        l = c;

    return l;

}

//Function that runs the RabinKarp algorithm
unordered_map<string, string> Sentences::rabinKarpPolySentences(string main, string c1, string c2, string c3)
{




        //int corpus2Index = 0;
        //int corpus3Index = 0;
        int n = main.length();
        int m = c1.length();
        int probeIM = 0;
        int probeIC = 0;


        string longest{};

        //function that finds the longer file
        longest = longer(n, m, main, c1);


        //need it to run one more time it stops a sentecne short

        //for loop for RabinKarp first 3 steps algorithm
        for (int i = 0; i < numberOfSentences(longest); i++)
        {
            //removes spaces from both strings and gets substring sentences
            string mSub = removeSpaces(main, mainIndex);
            string c1Sub = removeSpaces(c1, corpus1Index);
            string mSubPrint = calcBound(main, mainIndexPrint);
            string c1SubPrint = calcBound(c1, corpus1IndexPrint);
            /* string c2Sub = calcBound(c1, corpus2Index, words);
             string c3Sub = calcBound(c1, corpus3Index, words);*/
            //Calculates hash values for each sentences per loop
            hashMsub = RollingQuadraticHashFunction(mSub, 1000000007, 263);
            hashCsub = RollingQuadraticHashFunction(c1Sub, 1000000007, 263);

            //Condition to check for hash value collisions
            if (mainSplit.count(hashMsub)) {
                probeIM++;
                //update hash value with double hashing if needed
                hashMsub = doubleHashPoly(mSub, probeIM, mainSplit.size(), 1000000007, 263);
            }

            if (c1Split.count(hashCsub)) {
                probeIC++;
                //update hash value with double hashing if needed
                hashCsub = doubleHashPoly(c1Sub, probeIC, mainSplit.size(), 1000000007, 263);
            }

            //Filling up hash map
            mainSplit.insert({ hashMsub, mSub });
            mainSplitPrint.insert({ hashMsub, mSubPrint });

            c1Split.insert({ hashCsub, c1Sub });
            c1SplitPrint.insert({ hashCsub, c1SubPrint });

            /*      c1Split.insert({ polynomialRollingHash(c2Sub, 101, 257), c2Sub });
                  c1Split.insert({ polynomialRollingHash(c3Sub, 101, 257), c3Sub });*/



        }

        string temp1{};
        string temp2{};
        bool match1 = true;
        //bool match2 = true;
        //bool match3 = true

        //for loop that iterates through the hash maps looking for matches
        for (auto it = mainSplit.begin(); it != mainSplit.end(); it++) {
            if (c1Split.count(it->first)) {
                match1 = true;
                //temp1 = (it->second).substr(0, (it->second).size() - 1);
                //temp2 = (c1Split[it->first]).substr(0, (c1Split[it->first]).size() - 1);;

                //These two for loops disregard punctuation and plural words to increase accuracy
                for (int i = 0; i < (it->second).length(); i++) {
                    //do not count punctuation aswell
                    if ((it->second)[i] == 's' && (it->second)[i + 1] == ' ')
                    {
                        (it->second).erase(i);
                    }
                    else if ((it->second)[i] != ' ' && (it->second)[i] != '.' && (it->second)[i] != '?' && (it->second)[i] != '!' && (it->second)[i] != '(' && (it->second)[i] != ')' && (it->second)[i] != '[' && (it->second)[i] != ']' && (it->second)[i] != '\0') {
                        (it->second).erase(i);
                    }
                }

                for (int i = 0; i < (c1Split[it->first]).length(); i++) {
                    //do not count punctuation aswell
                    if ((c1Split[it->first])[i] == 's' && (c1Split[it->first])[i + 1] == ' ')
                    {
                        (c1Split[it->first]).erase(i);
                    }
                    else if ((c1Split[it->first])[i] != ' ' && (c1Split[it->first])[i] != '.' && (c1Split[it->first])[i] != '?' && (c1Split[it->first])[i] != '!' && (c1Split[it->first])[i] != '(' && (c1Split[it->first])[i] != ')' && (c1Split[it->first])[i] != '[' && (c1Split[it->first])[i] != ']' && (c1Split[it->first])[i] != '\0') {
                        (c1Split[it->first]).erase(i);
                    }
                }

                //Performs check step in RabinKarp algorithm
                if (it->second != c1Split[it->first]) {
                    match1 = false;
                }

                else
                {
                    //inserst matches found into the results hash map
                    if (match1 == true) {
                        found.insert({ c1SplitPrint[it->first] , mainSplitPrint[it->first] + "\t From Document 1 \t" });


                    }

                }
            }





            //
            //if (c2Split.count(it->first)) {
            //    if (it->second != c2Split[it->first]) {
            //        match2 = false;
            //    }

            //    else
            //    {
            //        if (match2 == true) {
            //            found.insert({ c2Split[it->first] , mainSplit[it->first] + "\t From Document 2 \t" });


            //        }

            //    }
            //}
            ////
            //if (c3Split.count(it->first)) {
            //    if (it->second != c3Split[it->first]) {
            //        match3 = false;
            //    }

            //    else
            //    {
            //        if (match3 == true) {
            //            found.insert({ c3Split[it->first] , mainSplit[it->first] + "\t From Document 3 \t" });


            //        }

            //    }
            //}

        }


        //match1 = true;
        //if (it->second != c1Split[it->first]) {
        //    match1 = false;
        //}
        //else
        //{
        //    if (match1 == true) {
        //        found.insert({ c1Split[it->first] , mainSplit[it->first] + "\t From Document 1 \t" });


        //    }

        //}

        return found;
    }

unordered_map<string, string> Sentences::rabinKarpFingerPrintSentences(string main, string c1, string c2, string c3)
{
    return found;
}
