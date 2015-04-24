#pragma once

#include "headers.h"

using namespace std;

enum Languages { CPP, C, CS, PY, PAS, JAVA, EXOTIC };

enum States { START, TYPENAME, NAME, BRACE_1, BRACE_2, BRACE_3, FINISH };

struct Function {
    int begin, end;
    string name;
    string body;
};

Languages determineLanguage(string fileName);
bool isIdentifier(const string& word);
bool isNumber(const string& word);
void addTypewords(string& text, set<string>& typewords);
vector<Function> findFunctions(string& text, const set<string>& typewords);
vector<bool> findUsedFunctions(const vector<Function>& functions);
void deleteFunctions(string& text, const vector<Function>& functions);
void deleteStrangeSymbols(vector<string>& text);
void deleteComments(vector<string>& text);
void deleteDirectives(vector<string>& text);
void deleteBraces(vector<string>& text);
void deleteSemicolons(vector<string>& text);
void deleteTypedefs(vector<string>& text);
void replaceNames(vector<string>& text, const string& a, const string& b);
void insertSpaces(vector<string>& text);
void deleteSpaces(vector<string>& text);
vector<string> formatText(vector<string> text, string fileName,
                          const set<string>& keywords, set<string> typewords);
