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

bool isNumber(const string& word) {
    bool flag = true;
    for (size_t i = 0; i < word.length(); i++)
        if (!(((word[i] >= '0') && (word[i] <= '9')) ||
              ((word[i] >= 'a') && (word[i] <= 'z')) ||
              ((word[i] >= 'A') && (word[i] <= 'Z')) ||
              word[i] == '_'))
            flag = false;
    if (!((word[0] >= '0') && (word[0] <= '9')))
        flag = false;
    return flag;
}

void renameIdentifiers(string& oneLineText, const set<string>& keywords) {
    istringstream in(oneLineText);

    ostringstream out;

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

string makeFingerprint(const string& oneLineText, const set<string>& keywords) {
    istringstream in(oneLineText);

    ostringstream out;

    string word;
    while (in >> word) {
        if (keywords.find(word) != keywords.end())
            out << 'k';
        else if (isIdentifier(word))
            out << 'i';
        else if (isNumber(word))
            out << 'n';
        else
            out << word;
    }

    return out.str();
}

int lcs(const string& a, const string& b) {
    int n = a.length() + 1;
    int m = b.length() + 1;
    int* dp = new int[n * m];
    memset(dp, 0, sizeof(int) * n * m);

    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++) {
            dp[i * m + j] = max(dp[(i - 1) * m + j], dp[i * m + (j - 1)]);
            if (a[i - 1] == b[j - 1])
                dp[i * m + j] = max(dp[i * m + j], dp[(i - 1) * m + (j - 1)] + 1);
        }
    return dp[n * m - 1];
}

int main() {

    ifstream fin("input.txt");

    int n;
    fin >> n;
    vector<string> fileNames(n);
    for (int i = 0; i < n; i++)
        fin >> fileNames[i];

    fin.close();

    set<string> keywords;

	fin.open("keywords.txt");
	readKeywords(fin, keywords);
	fin.close();

    vector<string> fingerprints(n);

    for (int i = 0; i < n; i++) {
        vector<string> text;

        fin.open((fileNames[i]).c_str());
        readText(fin, text);
        fin.close();

        formatText(text);

        string oneLineText = "";
        for (size_t i = 0; i < text.size(); i++)
            oneLineText += text[i];

        renameIdentifiers(oneLineText, keywords);
        fingerprints[i] = makeFingerprint(oneLineText, keywords);
    }

    set<int> was;
    vector< vector< int > > ans;
    for (int i = 0; i < n; i++) {
        vector<int> q;
        vector<int> same;

        if (was.find(i) != was.end())
            continue;

        q.push_back(i);
        while (q.size()) {
            int p = q.back();
            q.pop_back();

            if (was.find(p) != was.end())
                continue;
            was.insert(p);
            same.push_back(p);

            for (int j = 0; j < n; j++)
                if (was.find(j) == was.end()) {
                    int len = lcs(fingerprints[p], fingerprints[j]);
                    if (len >= min(fingerprints[p].length(), fingerprints[j].length()) * 0.9)
                        q.push_back(j);
                }
        }

        if (same.size() > 1)
            ans.push_back(same);
    }

    ofstream fout("output.txt");
    fout << ans.size() << endl;
    for (size_t i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++)
            fout << fileNames[ans[i][j]] << ' ';
        fout << endl;
    }
    fout.close();

	return 0;
}

