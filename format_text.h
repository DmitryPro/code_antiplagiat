#pragma once

#include "headers.h"

using namespace std;

bool isIdentifier(const string& word);
bool isNumber(const string& word);
void deleteComments(vector<string>& text);
void deleteDirectives(vector<string>& text);
void deleteBraces(vector<string>& text);
void deleteSemicolons(vector<string>& text);
void deleteTypedefs(vector<string>& text);
void replaceNames(vector<string>& text, const string& a, const string& b);
void insertSpaces(vector<string>& text);
void deleteSpaces(vector<string>& text);
vector<string> formatText(vector<string> text, const set<string>& keywords);
