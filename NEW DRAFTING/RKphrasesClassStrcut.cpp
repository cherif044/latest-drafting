#include "RKphrases.h"
#include <locale>
#include <codecvt>

using namespace std;




//Calculate the number of phrases with given word in longer file
int Phrases::numberOfPhrases(int length, int phrases)
{
    //# of words/phrases

    int number = 0;
    number = (length / phrases) + 1;

    return number;
}



//function that finds which file is longer
int longer(int n, int m) {

    int l = 0;

    if (m > n)
        l = m;
    else
        l = n;

    return l;

}

unordered_map<string, string> Phrases::rabinKarpPolyPhrases(string main, string c1, string c2, string c3, int words)
{



    vector<string> ngMain;
    vector<string> ngCorpus_1;

    //int corpus2Index = 0;
    //int corpus3Index = 0;
    int n = main.length();
    int m = c1.length();
    int l = 0;
    int probeIM = 0;
    int probeIC = 0;
    mainIndex = 0;
    corpus1Index = 0;
    mainIndexPrint = 0;
    corpus1IndexPrint = 0;


    l = longer(n, m);


    //for loop for RabinKarp first 3 steps algorithm
    for (int i = 0; i <= numberOfPhrases(l, words); i++)
    {

        //removes spaces from both strings and gets substring phrases
        string mSub = calcBound(main, mainIndex, words);
        string c1Sub = calcBound(c1, corpus1Index, words);
        string mSubPrint = calcBound(main, mainIndexPrint, words);
        string c1SubPrint = calcBound(c1, corpus1IndexPrint, words);
        /* string c2Sub = calcBound(c1, corpus2Index, words);
         string c3Sub = calcBound(c1, corpus3Index, words);*/
         //Calculates hash values for each substring per loop
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


    }



    string temp1{};
    string temp2{};
    bool match1 = true;
    int check = 0;
    //bool match2 = true;
    //bool match3 = true;
    //
    //for loop that iterates through the hash maps looking for matches
    for (auto it = mainSplit.begin(); it != mainSplit.end(); it++) {
        if (c1Split.count(it->first)) {
            match1 = true;
            temp1 = (it->second).substr(0, (it->second).size() - 1);
            temp2 = (c1Split[it->first]).substr(0, (c1Split[it->first]).size() - 1);;

            //These two for loops disregard punctuation and plural words to increase accuracy
                  for (int i = 0; i < temp1.length(); i++) {
                     //do not count punctuation aswell
                     if (temp1[i] == 's' && temp1[i + 1] == ' ')
                     {
                        temp1.erase(i);
                     }
                     else if (temp1[i] != ' ' && temp1[i] != '.' && temp1[i] != '?' && temp1[i] != '!' && temp1[i] != '(' && temp1[i] != ')' && temp1[i] != '[' && temp1[i] != ']' && temp1[i] != '\0'){
                        temp1.erase(i);
                     }
                  }

                  for (int i = 0; i < temp2.length(); i++) {
                     //do not count punctuation aswell
                     if (temp2[i] == 's' && temp2[i + 1] == ' ')
                     {
                        temp2.erase(i);
                     }
                     else if (temp2[i] != ' ' && temp2[i] != '.' && temp2[i] != '?' && temp2[i] != '!' && temp2[i] != '(' && temp2[i] != ')' && temp2[i] != '[' && temp2[i] != ']' && temp2[i] != '\0'){
                        temp2.erase(i);
                     }
                  }

            //Performs check step in RabinKarp algorithm
            if (temp1 != temp2) {
                match1 = false;
            }

            else
            {
                if (match1 == true) {
                    //inserst matches found into the results hash map// they may not be updated
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


unordered_map<string, string> Phrases::rabinKarpFingerPrintPhrases(string main, string c1, string c2, string c3, int words)
{
    return unordered_map<string, string>();
}
