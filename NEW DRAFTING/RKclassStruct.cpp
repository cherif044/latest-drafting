#include<iostream>
#include<unordered_set>
#include"File.h"
#include"RabinKarp.h"
using namespace std;

//Constructor than initializes variables
RabinKarp::RabinKarp() :mainIndex{ 0 }, corpus1Index{ 0 }, mainIndexPrint{ 0 }, corpus1IndexPrint{ 0 }, hashCsub{ 0 }, hashMsub{ 0 }, words{ 0 }, mainFile{}, corpusFile{}, isMatch{ false } {}


//reads file and returns string with file content
string RabinKarp::readFile(ifstream* infile) const {

        string line, temp;

        while (getline(*infile, temp)) { line = line + temp; }

        return line;
}


// Double hashing
int RabinKarp :: doubleHashPoly(string str, int i, int m, int p, int q){
    int h1 = RollingQuadraticHashFunction(str, p, m);
    int h2 = djb2Hash(str);
    int offset = q - (h2 % q);
    return (h1 + i * offset) % m;
}

int RabinKarp :: doubleHashFinger(string str, int i, int m, int p, int q){
    int h1 = FingerprintRollingHashFunction(str, p, m);
    int h2 = djb2Hash(str);
    int offset = q - (h2 % q);
    return (h1 + i * offset) % m;
}

//djb2Hash double hash functions
 long RabinKarp :: djb2Hash(const string& str) {
    unsigned long hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

 //fingerprint hash
 int RabinKarp::FingerprintRollingHashFunction(string str, long long p, long long x) {
     int result = 0;
     int n = str.length();
     int power = 1;

     // Calculate x^n
     for (int i = 0; i < n - 1; i++) {
         power = (power * x) % p;
     }

     // Calculate the hash value
     for (int i = 0; i < n; i++) {
         result = (result * x + str[i]) % p;
         if (i >= n - 1) {
             // Subtract the contribution of the i-n character and add the contribution of the i+1 character
             int prev_char = str[i - n + 1];
             result = (result - prev_char * power) % p;
             if (result < 0) {
                 result += p;
             }
         }
     }

     return result;
 }



 //Quadratic hash
 int RabinKarp::RollingQuadraticHashFunction(string str, long long p, long long x) {
     int result = 0;
     int x_pow = 1;
     for (int i = 0; i < str.length(); i++) {
         if (str[i] == 's' && str[i + 1] == ' ') {
             continue; // Skip "s " characters
         }
         if (str[i] != ' ' && str[i] != '.' && str[i] != '?' && str[i] != '!' && str[i] != '(' && str[i] != ')' && str[i] != '[' && str[i] != ']' && str[i] != '\0') {
             result = (result + ((str[i] - 'a' + 1) * x_pow) % p) % p;
             x_pow = (x_pow * x) % p;
         }
     }
     return result;
 }




 //Setters
 void RabinKarp::setHash(int x) {
     hashMsub = x;
 }

 void RabinKarp::setWords(int x) {
     words = x;
 }

 void RabinKarp::setMainIndex(int x) {
     mainIndex = x;
 }

 void RabinKarp::setCorpus1Index(int x) {
    corpus1Index = x;
 }

 void RabinKarp::setCorpus2Index(int x) {
     corpus2Index = x;
 }

 void RabinKarp::setCorpus3Index(int x) {
     corpus3Index = x;
 }

 void RabinKarp::setMainIndexPrint(int x) {
     mainIndexPrint = x;
 }

 void RabinKarp::setCorpus1IndexPrint(int x) {
     corpus1IndexPrint = x;
 }

 void RabinKarp::setCorpus2IndexPrint(int x) {
     corpus2IndexPrint = x;
 }

 void RabinKarp::setCorpus3IndexPrint(int x) {
     corpus3IndexPrint = x;
 }

 void RabinKarp::setMainFile(string mainFile) {
     mainFile = mainFile;
 }

 void RabinKarp::setCorpusFile(string corpusFile) {
     corpusFile = corpusFile;
 }

 void RabinKarp::setMatch(bool match) {
     match = match;
 }

 void RabinKarp::setMainSplit(int hashValue, string mainFile) {
     mainSplit[hashValue]=mainFile;
 }

 void RabinKarp::setMainSplitPrint(int hashValue, string mainFile) {
     mainSplitPrint[hashValue]=mainFile;
 }

 void RabinKarp::setC1Split(int hashValue, string corpusFile) {
     c1Split[hashValue]=corpusFile;
 }

 void RabinKarp::setC1SplitPrint(int hashValue, string corpusFile) {
     c1SplitPrint[hashValue]=corpusFile;
 }

 void RabinKarp::setC2Split(int hashValue, string corpusFile) {
     c2Split[hashValue]=corpusFile;
 }

 void RabinKarp::setC2SplitPrint(int hashValue, string corpusFile) {
     c2SplitPrint[hashValue] = corpusFile;
 }

 void RabinKarp::setC3Split(int hashValue, string corpusFile) {
     c3Split[hashValue]=corpusFile;
 }

 void RabinKarp::setC3SplitPrint(int hashValue, string corpusFile) {
     c3SplitPrint[hashValue]=corpusFile;
 }

 void RabinKarp::setFound(string corpusFile, string mainFile) {
     found[corpusFile] = mainFile;
 }


 //Getters
 int RabinKarp::getHash() const {
     return hashMsub;
 }

 int RabinKarp::getWords() const {
     return words;
 }

 int RabinKarp::getMainIndex() const {
     return mainIndex;
 }

 int RabinKarp::getCorpus1Index() const {
     return corpus1Index;
 }

 int RabinKarp::getCorpus2Index() const {
     return corpus2Index;
 }

 int RabinKarp::getCorpus3Index() const {
     return corpus3Index;
 }

 int RabinKarp::getMainIndexPrint() const {
     return mainIndexPrint;
 }

 int RabinKarp::getCorpus1IndexPrint() const {
     return corpus1IndexPrint;
 }

 int RabinKarp::getCorpus2IndexPrint() const {
     return corpus2IndexPrint;
 }

 int RabinKarp::getCorpus3IndexPrint() const {
     return corpus3IndexPrint;
 }

 string RabinKarp::getMainFile() const {
     return mainFile;
 }

 string RabinKarp::getCorpusFile() const {
     return corpusFile;
 }

 bool RabinKarp::getIsMatch() const {
     return isMatch;
 }

 unordered_map<int, string> RabinKarp::getMainSplit() const {
     return mainSplit;
 }

 unordered_map<int, string> RabinKarp::getMainSplitPrint() const {
     return mainSplitPrint;
 }

 unordered_map<int, string> RabinKarp::getC1Split() const {
     return c1Split;
 }

 unordered_map<int, string> RabinKarp::getC1SplitPrint() const {
     return c1SplitPrint;
 }

 unordered_map<int, string> RabinKarp::getC2Split() const {
     return c2Split;
 }

 unordered_map<int, string> RabinKarp::getC2SplitPrint() const {
     return c2SplitPrint;
 }


 unordered_map<int, string> RabinKarp::getC3Split() const {
     return c3Split;
 }

 unordered_map<int, string> RabinKarp::getC3SplitPrint() const {
     return c3SplitPrint;
 }


 unordered_map<string, string> RabinKarp::getFound() const {
     return found;
 }


 //function that removes any space characters from string for the parameter word length of the phrase for the given index
 string RabinKarp::removeSpaces(string str, int& i, int words) const
 {
     //Counter that ends while loop when number of words in phrase is reached
     int x = 0;
     //String that is returned as the custom substring
     string sub{};
     //Char type used to remove make all chars lower case
     char c;

     //As long as words per phrase was not reached and the words in the file string are not done while loop will loop
     while (x < words && i <= str.length()) {
        //when space is found do not return it
         if (str[i] == ' ' && str[i + 1] != ' ') {
             x++;
             i++;
         }
         else {
             c = tolower(str[i]);
             sub = sub + c;
             i++;

         }

     }

     return sub;

 }

 string RabinKarp::oneremoveSpaces(string str, int words) const
 {
     //Counter that ends while loop when number of words in phrase is reached
     int x = 0;
     int i = 0;
     //String that is returned as the custom substring
     string sub{};
     //Char type used to remove make all chars lower case
     char c;

     //As long as words per phrase was not reached and the words in the file string are not done while loop will loop
     while (x < words && i <= str.length()) {
         //when space is found do not return it
         if (str[i] == ' ' && str[i + 1] != ' ') {
             x++;
             i++;
         }
         else {
             c = tolower(str[i]);
             sub = sub + c;
             i++;

         }

     }

     return sub;

 }

 string RabinKarp::removeSpaces(string str, int& i) const
 {
     //Counter that ends while loop when a sentence or part of sentence is reached
     int x = 0;
     //String that is returned as the custom substring
     string sub{};
     //Char type used to remove make all chars lower case
     char c;

    //When one sentence or part of sentence is reached
     while (x < 1) {

         //when space is found do not return it
         if (str[i] == ' ' && str[i + 1] != ' ') {
             i++;
         }
         //when punctuation is found increase x
         if (str[i] == '.' || str[i] == '?' || str[i] == ',' || str[i] == ';' || str[i] == '!')
         {
             x++;
             c = tolower(str[i]);
             sub = sub + c;
             i++;
         }

         else
         {

             c = tolower(str[i]);
             sub = sub + c;
             i++;
         }
     }

     return sub;

 }

 string RabinKarp::oneCalcBound(string str, int words) const
 {
     //wprd counter
     int x = 0;
     int i = 0;
     string sub{};
     char c;

     //As long as words per phrase was not reached and the words in the file string are not done while loop will loop
     while (x < words && i <= str.length()) {
         //condition that detects a word and increments the number of words
         if (str[i] == ' ' && str[i + 1] != ' ')
         {
             x++;
             c = tolower(str[i]);
             sub = sub + c;
             i++;
         }

         else
         {

             c = tolower(str[i]);
             sub = sub + c;
             i++;
         }
     }



     return sub;
 }


 //Generate custom substrings using words in value to determine the number of words per phrase
 string RabinKarp::calcBound(string str, int& i, int words) const
 {
     //wprd counter
     int x = 0;
     string sub{};
     char c;

     //As long as words per phrase was not reached and the words in the file string are not done while loop will loop
     while (x < words && i <= str.length()) {
        //condition that detects a word and increments the number of words
         if (str[i] == ' ' && str[i + 1] != ' ')
         {
             x++;
             c = tolower(str[i]);
             sub = sub + c;
             i++;
         }

         else
         {

             c = tolower(str[i]);
             sub = sub + c;
             i++;
         }
     }



     return sub;
 }

 //Generate custom substrings using sentences
 string RabinKarp::calcBound(string str, int& i) const
 {
     //sentance counter
     int x = 0;
     string sub{};
     char c;


     while (x < 1) {
         //condition that detects a sentence and increments ands loop by incrementing x
         if (str[i] == '.' || str[i] == '?' || str[i] == ',' || str[i] == ';' || str[i] == '!')
         {
             x++;
             c = tolower(str[i]);
             sub = sub + c;
             i++;
         }

         else
         {

             c = tolower(str[i]);
             sub = sub + c;
             i++;
         }
     }



     return sub;
 }
