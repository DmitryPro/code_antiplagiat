#pragma once

#include "headers.h"

using namespace std;

enum Languages { CPP, C, CS, PY, PAS, JAVA, EXOTIC };

Languages determineLanguage(string fileName);
bool isIdentifier(const string& word);
bool isNumber(const string& word);
void deleteStrangeSymbols(vector<string>& text);
void deleteComments(vector<string>& text);
void deleteDirectives(vector<string>& text);
void deleteBraces(vector<string>& text);
void deleteSemicolons(vector<string>& text);
void deleteTypedefs(vector<string>& text);
void replaceNames(vector<string>& text, const string& a, const string& b);
void insertSpaces(vector<string>& text);
void deleteSpaces(vector<string>& text);
vector<string> formatText(vector<string> text, string fileName, const set<string>& keywords);
