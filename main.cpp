#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <set>
#include <cstdio>
#include <deque>
#include <fstream>

using namespace std;

vector<string> text;

void readText(istream& in) {
	text.clear();
	
	string s;
	while (getline(in, s))
		text.push_back(s);
}

void deleteComments() {
	bool flag = false;
	size_t beginLine, beginPos;
	
	for (size_t i = 0; i < text.size(); i++) {
		for (size_t j = 1; j < text[i].length(); j++) {
			if (!flag) {
				if (text[i][j - 1] == '/' && text[i][j] == '/')
					text[i].erase(j - 1, text[i].length() - (j - 1));	
			}
				
			if (text[i][j - 1] == '/' && text[i][j] == '*') {
				flag = true;
				beginLine = i;
				beginPos = j - 1;
			}
			
			if (text[i][j - 1] == '*' && text[i][j] == '/') {
				flag = false;
				if (i == beginLine) {
					text[i].erase(beginPos, j + 1 - beginPos);
					j = beginPos;
				}
				else {
					text[beginLine].erase(beginPos, text[beginLine].length() - beginPos);
					text[i].erase(0, j + 1);
					for (size_t k = beginLine + 1; k < i; k++)
						text[k] = "";
					j = 0;
				}
			}
		}
	}
}

void insertSpaces() {
	for (size_t i = 0; i < text.size(); i++) {
		string newLine = "";
		for (size_t j = 0; j < text[i].length(); j++) {
			if (! ( ((text[i][j] >= '0') && (text[i][j] <= '9')) ||
					((text[i][j] >= 'a') && (text[i][j] <= 'z')) ||
					((text[i][j] >= 'A') && (text[i][j] <= 'Z')) ||
					text[i][j] == '_'
				  )) {
				newLine += " ";
				newLine += text[i][j];
				newLine += " ";
			}
			else
				newLine += text[i][j];
		}
		text[i] = newLine;
	}
}

void deleteSpaces() {
	for (size_t i = 0; i < text.size(); i++) {
		if (text[i] == "") {
			text.erase(text.begin() + i);
			i--;
		}
		else {
			string newLine = "";
			for (size_t j = 1; j < text[i].length(); j++) {
				if (! (text[i][j] == ' ' && text[i][j - 1] == ' '))
					newLine += text[i][j];
			}
			text[i] = newLine;
		}
	}
}
					
				

int main() { 

	ifstream fin("input.txt");
	readText(fin);
	fin.close();
	
	deleteComments();
	insertSpaces();
	deleteSpaces();
	
	for (int i = 0; i < text.size(); i++)
		cout << text[i] << endl;
	
	return 0;
}
		
