/*#include<iostream>
#include<unordered_set>
#include <utility>
#include "mainwindow.h"
#include "RabinKarp.h"
#include "RKphrases.h"
#include "RKsentences.h"
#include "Main_ahmed.h"





using namespace std;

float jaccardSimilarity(const unordered_set<string>& set1, const unordered_set<string>& set2) {
    unordered_set<string> intersection;
    unordered_set<string> unionSet;

    // Calculate intersection
    for (const auto& ngram : set1) {
        if (set2.count(ngram) > 0) {
            intersection.insert(ngram);
        }
    }

    // Calculate union
    unionSet = set1;
    for (const auto& ngram : set2) {
        unionSet.insert(ngram);
    }

    float jaccard = static_cast<float>(intersection.size()) / unionSet.size();

    return jaccard;
}

//Get N-Grams for Jaccard
vector<string> generateNGrams(const string& str, int n) {
    vector<string> ngrams;
    for (int i = 0; i <= str.length() - n; i++) {
        ngrams.push_back(str.substr(i, n));
    }
    return ngrams;
}

//Calculates the percentage of similarity in the corpus vs the main using Jaccard Similarity
void similarityPercent(string main, string c1, string c2, string c3) {

    vector<string> suspiciousNGrams = generateNGrams(main, 5);
    std::unordered_set<std::string> suspiciousSet(suspiciousNGrams.begin(), suspiciousNGrams.end());

    vector<string> referenceNGrams = generateNGrams(c1, 5);
    std::unordered_set<std::string> referenceSet(referenceNGrams.begin(), referenceNGrams.end());
    //a lot of plagarism trace it
    float similarity = jaccardSimilarity(suspiciousSet, referenceSet);
    if (similarity >= 0.5) {
        cout << "Similarity of: " << similarity * 100 << "% suggests plagarism";
    }
    else if (similarity <= 0.5 && similarity >= 25) {
        cout << "Similarity of: " << similarity * 100 << "% is slightly high";
    }
    else
        cout << "No Plagarism";

}

list<pair<string, string>> printPoly(unordered_map<string, string> foundPolySentences, unordered_map<string, string> foundPoly4Phrases, unordered_map<string, string> foundPoly3Phrases, unordered_map<string, string> foundPoly2Phrases, int document) {
    list<pair<string, string>> foundList;
    string color{};


    if (document == 1) {
        color = "yellow";
    }
    else if (document == 2) {
        color = "blue";
    }
    else
        color = "white";

    if (foundPoly4Phrases.empty()) {
        std::cout << "foundPoly4Phrases is empty!" << std::endl;
    }

    if (foundPoly3Phrases.empty()) {
        std::cout << "foundPoly3Phrases is empty!" << std::endl;
    }

    if (foundPoly2Phrases.empty()) {
        std::cout << "foundPoly2Phrases is empty!" << std::endl;
    }

    if (foundPolySentences.empty()) {
        std::cout << "foundPolySentences is empty!" << std::endl;
    }

    //make first one color and second string
    for (auto it = foundPoly4Phrases.begin(); it != foundPoly4Phrases.end(); it++) {
        foundList.push_back({ color , foundPoly4Phrases[it->first]});
    }

    for (auto it = foundPoly3Phrases.begin(); it != foundPoly3Phrases.end(); it++) {
        foundList.push_back({ color , foundPoly3Phrases[it->first]});
    }

    for (auto it = foundPoly2Phrases.begin(); it != foundPoly2Phrases.end(); it++) {
        foundList.push_back({ color , foundPoly2Phrases[it->first] });

    }

    for (auto it = foundPolySentences.begin(); it != foundPolySentences.end(); it++) {
        foundList.push_back({ color , foundPolySentences[it->first]});

    }


    return foundList;
}

void printFinger() {


}

int v;

vector<wstring> RabinKarp::stem(string str, int i, vector<wstring> w) {
    if (i >= str.size()) {
        return w;
    }
    string strShort{};
    strShort = calcBound(str, i, 1);
    strShort = oneremoveSpaces(strShort, 1);
    stemming::english_stem<> StemEnglish;
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter; // create a converter object

    wstring wide_str = converter.from_bytes(strShort); // convert narrow string to wide string
    StemEnglish(wide_str);

    w.push_back(wide_str);

    return stem(str, i, w);
}

wstring RabinKarp::stem(string str) {
    string strShort{};
    strShort = oneCalcBound(str, 1);
    strShort = oneremoveSpaces(str, 1);
    stemming::english_stem<> StemEnglish;
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter; // create a converter object

    wstring wide_str = converter.from_bytes(strShort); // convert narrow string to wide string
    StemEnglish(wide_str);

  //  stem(str, i);

    return wide_str;
}


void runProgram() {

    //objects
    RabinKarp rk;
    Phrases p;
    Sentences s;

    //maps
    unordered_map<string, string> found = {};
    unordered_map<string, string> foundPoly4Phrases = {};
    unordered_map<string, string> foundPoly3Phrases = {};
    unordered_map<string, string> foundPoly2Phrases = {};
    unordered_map<string, string> foundPolySentences = {};

    list<pair<string, string>> foundList;




    //files
    ifstream c1F("filename1");
    string c1 = p.readFile(&c1F);

    cout<<"!!!!!!!!!!!!"<<"m.filename1";


    ifstream c2F("fff.txt");
    string c2 = p.readFile(&c2F);

    ifstream c3F("ff.txt");
    string c3 = p.readFile(&c3F);

    ifstream infile("m.filename2");
    string main = p.readFile(&infile);

    vector<wstring> w;


    w = rk.stem(main, 0, w);
//I have sent the main now I need to make w work with everyhitng else


    //found = rabinKarp(main, c1, c2, c3);

    foundPoly4Phrases = p.rabinKarpPolyPhrases(main, c1, c2, c3, 4);
    foundPoly3Phrases = p.rabinKarpPolyPhrases(main, c1, c2, c3, 3);
    foundPoly2Phrases = p.rabinKarpPolyPhrases(main, c1, c2, c3, 2);
    //still need to fix in sentences
    foundPolySentences = s.rabinKarpPolySentences(main, c1, c2, c3);


    //firgure out how to send doucment
    foundList = printPoly(foundPolySentences, foundPoly4Phrases, foundPoly3Phrases, foundPoly2Phrases, 0);

    for (const auto& p : foundList) {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }


    //fingerprint
    //figure out how to writw this normally
    /* for (auto it = found.begin(); it != found.end(); it++) {
         cout << it->first << '\t' << it->second << endl;

     }*/




      //similarityPercent(main, c1, c2, c3);

      //Now I have:
      //Jaccard sim working but i need to understand it
      //RK is working with the things need to find a nice way to priont
      // loop i think is solved
      //multiple docs either need to be the same size or I would need to use seperate fucntion or smth else idk yet


//}


//*/

