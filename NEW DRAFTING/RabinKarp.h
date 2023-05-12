#ifndef RABINKARP_H
#define RABINKARP_H
#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include "File.h"
#include "english.h"
using namespace std;


class RabinKarp : public File<string> { //RabinKarp class inherits from file with a string parameter for the readFile funciton
protected:

    //Int value used to store the hash values from the suspected file's substrings
    int hashMsub;
    //Int value used to store the hash values from the corpus file's substrings
    int hashCsub;
    //Int value that is sent to calcBound to determine the word count per phrase returned
    int words;
    //Int value that act as the index for the suspected file's substring that is updated
    int mainIndex;
    //Int values that act as the indcies for the corpus files' substrings that is updated
    int corpus1Index;
    int corpus2Index;
    int corpus3Index;
    //Int value that act as the index for the suspected file's substring that is saved for printing
    int mainIndexPrint;
    //Int value that act as the index for the corpus files' substring that is saved for printing
    int corpus1IndexPrint;
    int corpus2IndexPrint;
    int corpus3IndexPrint;

    //String where suspected file is read into a string
    string mainFile;
    //Corpus where corpus file is read into a string
    string corpusFile;
    //Bool value that is set to true when a hash value match is found between files and false otherwise
    bool isMatch;

    //Hash map where the phrases of the suspected file along with their hash value is stored
    unordered_map<int, string> mainSplit{};
    unordered_map<int, string> mainSplitPrint{};

    //Hash map where the phrases of the corpus files along with their hash value is stored
    unordered_map<int, string> c1Split{};
    unordered_map<int, string> c1SplitPrint{};
    unordered_map<int, string> c2Split{};
    unordered_map<int, string> c2SplitPrint{};
    unordered_map<int, string> c3Split{};
    unordered_map<int, string> c3SplitPrint{};

    //Hash map where each string found is stored along with its string match
    unordered_map<string, string> found{};
public:
    //make rabinkarp and file abstract
    string nameFile1{};
    string nameFile2{};
    //Constructor
    RabinKarp();
    /*
    RabinKarp(string fileName1, string fileName2){
        nameFile1  = fileName1;
        nameFile2 = fileName2;
    };
*/
    //Function that takes file object and reads it into a string
    string readFile(ifstream* infile) const;
    //Double hashing functions for Quadratic and Fingerprint hashing using djb2Hash to reduce collisons
    int doubleHashPoly(string str,  int i,  int m,  int p,  int q);
    int doubleHashFinger(string str, int i, int m, int p, int q);

    //Hashing functions for Quadratic and Fingerprint hashing
    int RollingQuadraticHashFunction(string str, long long  p, long long x);
    int FingerprintRollingHashFunction(string str, long long  p, long long x);
    //djb2Hash funciton used for double hashing
    long djb2Hash(const string& str);

    //function that removes any space characters from string for the parameter word length of the phrase for the given index
    string removeSpaces(string str, int& i, int words) const;
    //function that removes any space characters from string for sentences for the given index
    string removeSpaces(string str, int& i) const;
    string oneremoveSpaces(string str, int words) const;
    //function that returns custom substrings for the parameter word length of the phrase for the given index
    //string oneCalcBound(string str, int& i, int words) const;
    string calcBound(string str, int& i, int words) const;
    //function that returns custom substrings for sentences for the given index
    string calcBound(string str, int& i) const;
    string oneCalcBound(string str, int words) const;


    vector<wstring> stem(string str, int i, vector<wstring> w);

    wstring stem(string str);


    //Setters for all member variables and functions
    void setHash(int x);
    void setWords(int x);
    void setMainIndex(int x);
    void setCorpus1Index(int x);
    void setCorpus2Index(int x);
    void setCorpus3Index(int x);
    void setMainIndexPrint(int x);
    void setCorpus1IndexPrint(int x);
    void setCorpus2IndexPrint(int x);
    void setCorpus3IndexPrint(int x);
    void setMainFile(string mainFile);
    void setCorpusFile(string corpusFile);
    void setMatch(bool match);
    void setMainSplit(int hashValue, string mainFile);
    void setMainSplitPrint(int hashValue, string mainFile);
    void setC1Split(int hashValue, string corpusFile);
    void setC1SplitPrint(int hashValue, string corpusFile);
    void setC2Split(int hashValue, string corpusFile);
    void setC2SplitPrint(int hashValue, string corpusFile);
    void setC3Split(int hashValue, string corpusFile);
    void setC3SplitPrint(int hashValue, string corpusFile);
    void setFound(string corpusFile, string mainFile);

    //Getters for all member variables and functions
    int getHash() const;
    int  getWords() const;
    int  getMainIndex() const;
    int  getCorpus1Index() const;
    int  getCorpus2Index() const;
    int  getCorpus3Index() const;
    int  getMainIndexPrint() const;
    int  getCorpus1IndexPrint() const;
    int  getCorpus2IndexPrint() const;
    int  getCorpus3IndexPrint() const;
    string  getMainFile() const;
    string  getCorpusFile() const;
    bool  getIsMatch() const;

    unordered_map<int, string>  getMainSplit() const;
    unordered_map<int, string>  getMainSplitPrint() const;
    unordered_map<int, string>  getC1Split() const;
    unordered_map<int, string>  getC1SplitPrint() const;
    unordered_map<int, string>  getC2Split() const;
    unordered_map<int, string>  getC2SplitPrint() const;
    unordered_map<int, string>  getC3Split() const;
    unordered_map<int, string>  getC3SplitPrint() const;
    unordered_map<string, string>  getFound() const;





};
#endif // RABINKARP_H
