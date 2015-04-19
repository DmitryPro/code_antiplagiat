#include "headers.h"

void readText(istream& in, vector<string>& text) {
	text.clear();

	string s;
	while (getline(in, s))
		text.push_back(s);
}

void readKeywords(istream& in, set<string>& keywords) {
    keywords.clear();

	string s;
	while (in >> s)
		keywords.insert(s);
}

void readData(vector<string>& text, set<string>& keywords) {
    ifstream fin;

    fin.open("input.txt");
	readText(fin, text);
	fin.close();

	fin.open("keywords.txt");
	readKeywords(fin, keywords);
	fin.close();
}

long long hashFunction(const string& s) {
	long long hash = 0;
	for (size_t i = 0; i < s.length(); i++)
		hash = (hash * 257 + s[i]) % 1000000007;
	return hash;
}

bool isIdentifier(const string& word) {
    bool flag = true;
    for (size_t i = 0; i < word.length(); i++)
        if (!(((word[i] >= '0') && (word[i] <= '9')) ||
              ((word[i] >= 'a') && (word[i] <= 'z')) ||
              ((word[i] >= 'A') && (word[i] <= 'Z')) ||
              word[i] == '_'))
            flag = false;
    if ((word[0] >= '0') && (word[0] <= '9'))
        flag = false;
    return flag;
}

void renameIdentifiers(string& oneLineText, const set<string>& keywords) {
    istringstream in(oneLineText);

    string newLine = "";
    ostringstream out(newLine);

    int count = 0;
    string word;
    while (in >> word) {
        if (keywords.find(word) == keywords.end() && isIdentifier(word))
            out << "ID" << count++ << " ";
        else
            out << word << " ";
    }

    oneLineText = out.str();
}

int main() {

    vector<string> text;
    set<string> keywords;
    readData(text, keywords);

	formatText(text);

	string oneLineText = "";
	for (size_t i = 0; i < text.size(); i++)
		oneLineText += text[i];

	cout << hashFunction(oneLineText) << endl;

    renameIdentifiers(oneLineText, keywords);
    cout << oneLineText << endl;


	return 0;
}

