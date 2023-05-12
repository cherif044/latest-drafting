#ifndef MAIN_AHMED_H
#define MAIN_AHMED_H
#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include<list>
using namespace std;

//Function that include all program function calls
//Called by main function to execute program


void runProgram(string filename1, string filename2);


float jaccardSimilarity(const unordered_set<string>& set1, const unordered_set<string>& set2);
vector<string> generateNGrams(const string& str, int n);
void similarityPercent(string main, string c1, string c2, string c3);
list<pair<string, string>> printPoly(unordered_map<string, string> foundPolySentences, unordered_map<string, string> foundPoly4Phrases, unordered_map<string, string> foundPoly3Phrases, unordered_map<string, string> foundPoly2Phrases, int document);
#endif // MAIN_AHMED_H
