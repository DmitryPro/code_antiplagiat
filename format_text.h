#pragma once

#include "headers.h"

using namespace std;

void deleteComments(vector<string>& text);
void deleteDirectives(vector<string>& text);
void deleteTypedefs(vector<string>& text);
void insertSpaces(vector<string>& text);
void deleteSpaces(vector<string>& text);
void formatText(vector<string>& text);
