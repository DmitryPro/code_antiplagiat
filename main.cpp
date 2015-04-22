#include "headers.h"

double firstHeuristicsConst;
double secondHeuristicsConst;
double thirdHeuristicsConst;
int firstWidthConst;
int secondWidthConst;
int minLengthConst;

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
    hash<string> hf;
    return hf(s);
}

long long hashFunction(const vector<int>& v) {
    unsigned int Hash = 0;
    for(int i = 0; i < v.size(); i++)
        Hash = (Hash * 1664525) + v[i] + 1013904223;
    return Hash % 1000000007;
}

set<int> makeFingerprint(vector<int> hashSequence) {
    vector<int> hashes;
    set<int> fingerprint;
    int width;

    width = firstWidthConst;
    for (int i = 0; i < hashSequence.size() - width + 1; i++) {
        vector<int> subsequence;
        for (int j = 0; j < width; j++)
            subsequence.push_back(hashSequence[i + j]);
        hashes.push_back(hashFunction(subsequence));
    }

    width = secondWidthConst;
    for (int i = 0; i < hashes.size() - width + 1; i++) {
        int minHash = hashes[i];
        for (int j = 0; j < width; j++)
            minHash = min(minHash, hashes[i + j]);
        fingerprint.insert(minHash);
    }

    return fingerprint;
}

void createHashTable(const vector<int>& a, const vector<int>& b, int l,
                     vector< unordered_map< int, vector<int> > >& hashTable) {
    int p = 1000000007;
    int q = 1664525;

    long long power = 1;
    for (int i = 0; i < l; i++)
        power = power * q % p;

    long long Hash;

    Hash = 0;
    for (int i = 0; i < l; i++)
        Hash = (Hash * q + a[i]) % p;
    hashTable[0][Hash].push_back(0);

    for (int i = l; i < a.size(); i++) {
        Hash = (Hash * q + a[i]) % p;
        Hash = (Hash - a[i - l] * power) % p;
        Hash = (Hash + p) % p;
        hashTable[0][Hash].push_back(i - l + 1);
    }

    Hash = 0;
    for (int i = 0; i < l; i++)
        Hash = (Hash * q + b[i]) % p;
    hashTable[1][Hash].push_back(0);

    for (int i = l; i < b.size(); i++) {
        Hash = (Hash * q + b[i]) % p;
        Hash = (Hash - b[i - l] * power) % p;
        Hash = (Hash + p) % p;
        hashTable[1][Hash].push_back(i - l + 1);
    }
}

int commonPrefixLength(const vector<int>& a, const vector<int>& b,
                       const vector< vector<bool> >& marked, int i, int j) {
    int prefixLength = 0;
    while (i < a.size() && j < b.size() && a[i] == b[j] && !marked[0][i] && !marked[1][j]) {
        i++;
        j++;
        prefixLength++;
    }
    return prefixLength;
}

void mark(vector< vector<bool> >& marked, int i, int j, int length) {
    for (int k = 0; k < length; k++)
        marked[0][i + k] = marked[1][j + k] = true;
}

int gst(const vector<int>& a, const vector<int>& b) {
    int commonPartLength = 0;
    int minLength = minLengthConst;

    vector< vector<bool> > marked(2);
    marked[0] = vector<bool>(a.size(), false);
    marked[1] = vector<bool>(b.size(), false);

    int l = (min(a.size(), b.size()) + minLength) / 2;
    while (true) {
        vector< unordered_map< int, vector<int> > > hashTable(2);
        createHashTable(a, b, l, hashTable);

        int maxMatch = 0;
        vector< pair<int, int> > matches;

        for (auto it : hashTable[0]) {
            for (int i : it.second)
                for (int j : hashTable[1][it.first]) {
                    int prefixLength = commonPrefixLength(a, b, marked, i, j);
                    if (prefixLength > minLength)
                        if (prefixLength > maxMatch) {
                            maxMatch = prefixLength;
                            matches.clear();
                            matches.push_back(make_pair(i, j));
                        }
                        else if (prefixLength == maxMatch)
                            matches.push_back(make_pair(i, j));

                }
        }

        for (auto it : matches)
            if (commonPrefixLength(a, b, marked, it.first, it.second) == maxMatch) {
                mark(marked, it.first, it.second, maxMatch);
                commonPartLength += maxMatch;
            }

        if (matches.size() == 0) {
            if (l == minLength)
                break;
            l = (l + minLength) / 2;
        }
    }

    return commonPartLength;
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

bool firstHeuristics(const vector<int>& a, const vector<int>& b) {
    int len = lcs(a, b);
    return 1.0L * len / (a.size() + b.size() - len) > firstHeuristicsConst;
}

bool secondHeuristics(const set<int>& a, const set<int>& b) {
    int count = 0;
    for (set<int>::iterator it = a.begin(); it != a.end(); it++)
        if (b.find(*it) != b.end())
            count++;
    return 1.0L * count / (a.size() + b.size() - count) > secondHeuristicsConst;
}

bool thirdHeuristics(const vector<int>& a, const vector<int>& b) {
    int len = gst(a, b);
    return 1.0L * len / (a.size() + b.size() - len) > thirdHeuristicsConst;
}

int main(int argc, char* argv[]) {

    /*ifstream fin;
    set<string> keywords;

	fin.open("keywords.txt");
	readKeywords(fin, keywords);
	fin.close();

    vector<string> text;
    fin.open("38121.cpp");
    readText(fin, text);
    fin.close();

    vector<string> formattedText = formatText(text, keywords);
    //for (int i = 0; i < formattedText.size(); i++)
    //    cout << formattedText[i] << endl;

    return 0;*/

    /*string prefix = argv[1];
    sscanf(argv[2], "%lf", &firstHeuristicsConst);
    sscanf(argv[3], "%lf", &secondHeuristicsConst);
    sscanf(argv[4], "%lf", &thirdHeuristicsConst);
    sscanf(argv[5], "%d", &firstWidthConst);
    sscanf(argv[6], "%d", &secondWidthConst);
    sscanf(argv[7], "%d", &minLengthConst);*/

    firstHeuristicsConst = 0.55;
    secondHeuristicsConst = 0.55;
    thirdHeuristicsConst = 0.55;
    firstWidthConst = 4;
    secondWidthConst = 13;
    minLengthConst = 14;
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

        vector<string> formattedText = formatText(text, fileNames[i], keywords);
        for (size_t j = formattedText.size() * 0; j < formattedText.size(); j++)
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
                if (firstHeuristics(hashSequences[i], hashSequences[j]) &&
                    secondHeuristics(fingerprints[i], fingerprints[j]) &&
                    thirdHeuristics(hashSequences[i], hashSequences[j])) {

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

