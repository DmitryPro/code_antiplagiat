#include "headers.h"

double firstEuristicConst;
double secondEuristicConst;
int firstWidth;
int secondWidth;

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

int lcs(const vector<int>& a, const vector<int>& b) {
    int n = a.size() + 1;
    int m = b.size() + 1;

    int* dp[2];
    dp[0] = new int[m];
    dp[1] = new int[m];
    memset(dp[0], 0, sizeof(int) * m);

    for (int i = 1; i < n; ++i) {
        dp[1][0] = 0;
        for (int j = 1; j < m; ++j) {
            if (a[i - 1] == b[j - 1])
                dp[1][j] = dp[0][j - 1] + 1;
            else
                dp[1][j] = max(dp[0][j], dp[1][j - 1]);
        }
        memcpy(dp[0], dp[1], sizeof(int) * m);
    }
    int ans = dp[0][m - 1];

    delete[] dp[0];
    delete[] dp[1];

    return ans;
}

set<int> makeFingerprint(vector<int> hashSequence) {
    vector<int> hashes;
    set<int> fingerprint;

    int width = firstWidth;
    for (int i = 0; i < hashSequence.size() - width + 1; i++) {
        long long hash = 0;
        for (int j = 0; j < width; j++)
            hash = (hash * 257 + hashSequence[i + j]) % 1000000007;
        hashes.push_back(hash);
    }

    width = secondWidth;
    for (int i = 0; i < hashes.size() - width + 1; i++) {
        int minHash = hashes[i];
        for (int j = 0; j < width; j++)
            minHash = min(minHash, hashes[i + j]);
        fingerprint.insert(minHash);
    }

    return fingerprint;
}

//int main(int argc, char* argv[]) {
int main() {

    /*ifstream fin;
    set<string> keywords;

	fin.open("keywords.txt");
	readKeywords(fin, keywords);
	fin.close();

    vector<string> text;
    fin.open("HelloWorld.cpp");
    readText(fin, text);
    fin.close();

    vector<string> formattedText = formatText(text, keywords);
    //for (int i = 0; i < formattedText.size(); i++)
    //    cout << formattedText[i] << endl;

    return 0;*/

    //string prefix = argv[1];
    //sscanf(argv[2], "%lf", &firstEuristicConst);
    //sscanf(argv[3], "%lf", &secondEuristicConst);
    //sscanf(argv[4], "%d", &firstWidth);
    //sscanf(argv[5], "%d", &secondWidth);

    firstEuristicConst = 0.20831;
    secondEuristicConst = 0.684671;
    firstWidth = 6;
    secondWidth = 31;
    string prefix = "";

    ifstream fin((prefix + "input.txt").c_str());

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

    vector< vector<int> > hashSequences(n);
    vector< set<int> > fingerprints(n);

    for (int i = 0; i < n; i++) {
        vector<string> text;

        fin.open((prefix + fileNames[i]).c_str());
        readText(fin, text);
        fin.close();

        vector<string> formattedText = formatText(text, keywords);
        for (size_t j = 0; j < formattedText.size(); j++)
            hashSequences[i].push_back(hashFunction(formattedText[j]));
        fingerprints[i] = makeFingerprint(hashSequences[i]);
    }

    set<int> used;
    vector< vector< int > > ans;
    for (int i = 0; i < n; i++) {
        vector<int> same;

        if (used.find(i) != used.end())
            continue;

        used.insert(i);
        same.push_back(i);


        for (int j = i + 1; j < n; j++)
            if (used.find(j) == used.end()) {
                vector<int> a = hashSequences[i];
                vector<int> b = hashSequences[j];

                int len = lcs(a, b);
                bool firstEuristic = len >= min(a.size(), b.size()) * firstEuristicConst;

                set<int> f1 = fingerprints[i];
                set<int> f2 = fingerprints[j];
                int count = 0;
                for (set<int>::iterator it = f1.begin(); it != f1.end(); it++)
                    if (f2.find(*it) != f2.end())
                        count++;
                bool secondEuristic = count >= min(f1.size(), f2.size()) * secondEuristicConst;

                if (firstEuristic && secondEuristic) {
                    used.insert(j);
                    same.push_back(j);
                }
            }

        if (same.size() > 1)
            ans.push_back(same);
    }

    ofstream fout((prefix + "output.txt").c_str());
    fout << ans.size() << endl;
    for (size_t i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++)
            fout << fileNames[ans[i][j]] << ' ';
        fout << endl;
    }
    fout.close();

	return 0;
}

