#include "headers.h"

void readText(istream& in, vector<string>& text) {
	text.clear();

	string s;
	while (getline(in, s))
		text.push_back(s);
}

long long hashFunction(string s) {
	long long hash = 0;
	for (size_t i = 0; i < s.length(); i++)
		hash = (hash * 257 + s[i]) % 1000000007;
	return hash;
}

int main() {

    vector<string> text;

	ifstream fin("input.txt");
	readText(fin, text);
	fin.close();

	formatText(text);

	string oneLineText = "";
	for (size_t i = 0; i < text.size(); i++)
		oneLineText += text[i];

	cout << oneLineText;

	return 0;
}

