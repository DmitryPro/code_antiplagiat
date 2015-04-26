/**
http://rain.ifmo.ru/cat/data/theory/unsorted/plagiarism-2006/article.pdf
Используется метод отпечатков - second heuristics
и жадное строковое замощение - third heuristics
Метод на основе Колмогоровской сложности (fourth heuristics) плохо реализован и не используется
Метод на основе наибольшей общей подпоследовательности (first heuristics) ужасен и не используется
*/

#include "headers.h"

double firstHeuristicsConst;
double secondHeuristicsConst;
double thirdHeuristicsConst;
double fourthHeuristicsConst;
int firstWidthConst;
int secondWidthConst;
int minLengthConst;

void readText(istream& in, vector<string>& text) {
	text.clear();

	string s;
	while (getline(in, s)) {
        for (size_t i = 0; i < s.length();)
            if (s[i] < 32)
                s.erase(i, 1);
            else
                i++;
		text.push_back(s);
    }
}

void readKeywords(set<string>& keywords) {
    keywords.clear();

    keywords.insert("False");
    keywords.insert("None");
    keywords.insert("True");
    keywords.insert("absolute");
    keywords.insert("abstract");
    keywords.insert("alignas");
    keywords.insert("alignof");
    keywords.insert("pair");
    keywords.insert("and");
    keywords.insert("and_eq");
    keywords.insert("apply");
    keywords.insert("array");
    keywords.insert("as");
    keywords.insert("asm");
    keywords.insert("assembler");
    keywords.insert("assert");
    keywords.insert("at");
    keywords.insert("atom");
    keywords.insert("auto");
    keywords.insert("automated");
    keywords.insert("begin");
    keywords.insert("bitand");
    keywords.insert("bitor");
    keywords.insert("bool");
    keywords.insert("boolean");
    keywords.insert("break");
    keywords.insert("byte");
    keywords.insert("calloc");
    keywords.insert("car");
    keywords.insert("case");
    keywords.insert("catch");
    keywords.insert("cdecl");
    keywords.insert("cdr");
    keywords.insert("char");
    keywords.insert("char16_t");
    keywords.insert("char32_t");
    keywords.insert("cin");
    keywords.insert("cout");
    keywords.insert("class");
    keywords.insert("compl");
    keywords.insert("cond");
    keywords.insert("cons");
    keywords.insert("const");
    keywords.insert("const_cast");
    keywords.insert("constexpr");
    keywords.insert("constructor");
    keywords.insert("continue");
    keywords.insert("data");
    keywords.insert("decltype");
    keywords.insert("def");
    keywords.insert("default");
    keywords.insert("defun");
    keywords.insert("del");
    keywords.insert("delete");
    keywords.insert("deriving");
    keywords.insert("destructor");
    keywords.insert("dispid");
    keywords.insert("dispinterface");
    keywords.insert("div");
    keywords.insert("do");
    keywords.insert("double");
    keywords.insert("downto");
    keywords.insert("dynamic");
    keywords.insert("dynamic_cast");
    keywords.insert("elif");
    keywords.insert("else");
    keywords.insert("end");
    keywords.insert("enum");
    keywords.insert("eq");
    keywords.insert("eql");
    keywords.insert("equal");
    keywords.insert("equalp");
    keywords.insert("eval");
    keywords.insert("except");
    keywords.insert("explicit");
    keywords.insert("export");
    keywords.insert("exports");
    keywords.insert("extends");
    keywords.insert("extern");
    keywords.insert("external");
    keywords.insert("false");
    keywords.insert("far");
    keywords.insert("file");
    keywords.insert("final");
    keywords.insert("finalization");
    keywords.insert("finally");
    keywords.insert("float");
    keywords.insert("for");
    keywords.insert("forall");
    keywords.insert("foreign");
    keywords.insert("format");
    keywords.insert("forward");
    keywords.insert("free");
    keywords.insert("friend");
    keywords.insert("funcall");
    keywords.insert("function");
    keywords.insert("global");
    keywords.insert("goto");
    keywords.insert("hiding");
    keywords.insert("if");
    keywords.insert("implementation");
    keywords.insert("implements");
    keywords.insert("import");
    keywords.insert("in");
    keywords.insert("include");
    keywords.insert("index");
    keywords.insert("infix");
    keywords.insert("infixl");
    keywords.insert("infixr");
    keywords.insert("inherited");
    keywords.insert("initialization");
    keywords.insert("inline");
    keywords.insert("instance");
    keywords.insert("instanceof");
    keywords.insert("int");
    keywords.insert("interface");
    keywords.insert("is");
    keywords.insert("label");
    keywords.insert("lambda");
    keywords.insert("let");
    keywords.insert("library");
    keywords.insert("list");
    keywords.insert("long");
    keywords.insert("loop");
    keywords.insert("main");
    keywords.insert("malloc");
    keywords.insert("math");
    keywords.insert("map");
    keywords.insert("mdo");
    keywords.insert("message");
    keywords.insert("mod");
    keywords.insert("module");
    keywords.insert("mutable");
    keywords.insert("name");
    keywords.insert("namespace");
    keywords.insert("native");
    keywords.insert("near");
    keywords.insert("new");
    keywords.insert("newtype");
    keywords.insert("nil");
    keywords.insert("nodefault");
    keywords.insert("noexcept");
    keywords.insert("nonlocal");
    keywords.insert("not");
    keywords.insert("not_eq");
    keywords.insert("null");
    keywords.insert("nullptr");
    keywords.insert("object");
    keywords.insert("of");
    keywords.insert("on");
    keywords.insert("operator");
    keywords.insert("or");
    keywords.insert("or_eq");
    keywords.insert("out");
    keywords.insert("overload");
    keywords.insert("override");
    keywords.insert("package");
    keywords.insert("packed");
    keywords.insert("pascal");
    keywords.insert("pass");
    keywords.insert("princ");
    keywords.insert("printf");
    keywords.insert("private");
    keywords.insert("procedure");
    keywords.insert("program");
    keywords.insert("property");
    keywords.insert("protected");
    keywords.insert("public");
    keywords.insert("published");
    keywords.insert("qualified");
    keywords.insert("raise");
    keywords.insert("read");
    keywords.insert("realloc");
    keywords.insert("record");
    keywords.insert("register");
    keywords.insert("reinterpret_cast");
    keywords.insert("reintroduce");
    keywords.insert("repeat");
    keywords.insert("reverse");
    keywords.insert("resident");
    keywords.insert("resourcestring");
    keywords.insert("return");
    keywords.insert("scanf");
    keywords.insert("set");
    keywords.insert("setq");
    keywords.insert("sort");
    keywords.insert("shl");
    keywords.insert("short");
    keywords.insert("shr");
    keywords.insert("signed");
    keywords.insert("sizeof");
    keywords.insert("static");
    keywords.insert("static_assert");
    keywords.insert("static_cast");
    keywords.insert("std");
    keywords.insert("stdcall");
    keywords.insert("stdio");
    keywords.insert("stdlib");
    keywords.insert("stored");
    keywords.insert("strictfp");
    keywords.insert("string");
    keywords.insert("struct");
    keywords.insert("super");
    keywords.insert("switch");
    keywords.insert("synchronized");
    keywords.insert("template");
    keywords.insert("then");
    keywords.insert("this");
    keywords.insert("thread_local");
    keywords.insert("threadvar");
    keywords.insert("throw");
    keywords.insert("throws");
    keywords.insert("transient");
    keywords.insert("true");
    keywords.insert("try");
    keywords.insert("type");
    keywords.insert("typedef");
    keywords.insert("typeid");
    keywords.insert("typename");
    keywords.insert("union");
    keywords.insert("unit");
    keywords.insert("unless");
    keywords.insert("unsigned");
    keywords.insert("until");
    keywords.insert("uses");
    keywords.insert("using");
    keywords.insert("var");
    keywords.insert("vector");
    keywords.insert("virtual");
    keywords.insert("void");
    keywords.insert("volatile");
    keywords.insert("wchar_t");
    keywords.insert("where");
    keywords.insert("while");
    keywords.insert("with");
    keywords.insert("write");
    keywords.insert("xor");
    keywords.insert("xor_eq");
    keywords.insert("yield");
}

void readTypewords(set<string>& typewords) {
    typewords.clear();

    typewords.insert("int");
    typewords.insert("long");
    typewords.insert("unsigned");
    typewords.insert("void");
    typewords.insert("char");
    typewords.insert("bool");
    typewords.insert("short");
    typewords.insert("float");
    typewords.insert("double");
    typewords.insert("pair");
    typewords.insert("const");
    typewords.insert("size_t");
    typewords.insert("wchar_t");
    typewords.insert("vector");
    typewords.insert("static");
    typewords.insert("set");
    typewords.insert("map");
    typewords.insert("string");
    typewords.insert("queue");
    typewords.insert("deque");
    typewords.insert("std");
    typewords.insert(",");
    //typewords.insert(":");
    typewords.insert("*");
    typewords.insert("&");
    typewords.insert("[");
    typewords.insert("]");
    typewords.insert("<");
    typewords.insert(">");
    typewords.insert("class");
    typewords.insert("typename");
    typewords.insert("template");
    typewords.insert("Integer");
    typewords.insert("Boolean");
    typewords.insert("String");
    typewords.insert("Character");
    typewords.insert("Short");
    typewords.insert("Long");
    typewords.insert("BigInteger");
    typewords.insert("BigDecimal");
    typewords.insert("List");
    typewords.insert("ArrayList");
    typewords.insert("Vector");
    typewords.insert("Stack");
    typewords.insert("LinkedList");
    typewords.insert("Deque");
    typewords.insert("Queue");
    typewords.insert("Set");
    typewords.insert("HashSet");
    typewords.insert("SortedSet");
    typewords.insert("TreeSet");
    typewords.insert("LinkedHashSet");
}

long long hashFunction(const vector<int>& v) {
    long long Hash = 0;
    for(size_t i = 0; i < v.size(); i++)
        Hash = ((Hash * 1664525) + v[i] + 1013904223) % 1000000007;
    return Hash % 1000000007;
}

set<int> makeFingerprint(vector<int> hashSequence) {
    vector<int> hashes;
    set<int> fingerprint;
    size_t width;

    width = firstWidthConst;
    if (hashSequence.size() < width)
        return set<int>();

    for (size_t i = 0; i < hashSequence.size() - width + 1; i++) {
        vector<int> subsequence;
        for (size_t j = 0; j < width; j++)
            subsequence.push_back(hashSequence[i + j]);
        hashes.push_back(hashFunction(subsequence));
    }

    width = secondWidthConst;
    if (hashes.size() < width)
        return set<int>();

    for (size_t i = 0; i < hashes.size() - width + 1; i++) {
        int minHash = hashes[i];
        for (size_t j = 0; j < width; j++)
            minHash = min(minHash, hashes[i + j]);
        fingerprint.insert(minHash);
    }

    return fingerprint;
}

void createHashTable(const vector<int>& a, const vector<int>& b, int l,
                     vector< unordered_map< int, vector<int> > >& hashTable) {
    long long p = 1000000007;
    long long q = 1664525;

    long long power = 1;
    for (int i = 0; i < l; i++)
        power = power * q % p;

    long long Hash;

    Hash = 0;
    for (int i = 0; i < l; i++)
        Hash = (Hash * q + a[i]) % p;
    hashTable[0][Hash].push_back(0);

    for (size_t i = l; i < a.size(); i++) {
        Hash = (Hash * q + a[i]) % p;
        Hash = (Hash - a[i - l] * power) % p;
        Hash = (Hash + p) % p;
        hashTable[0][Hash].push_back(i - l + 1);
    }

    Hash = 0;
    for (int i = 0; i < l; i++)
        Hash = (Hash * q + b[i]) % p;
    hashTable[1][Hash].push_back(0);

    for (size_t i = l; i < b.size(); i++) {
        Hash = (Hash * q + b[i]) % p;
        Hash = (Hash - b[i - l] * power) % p;
        Hash = (Hash + p) % p;
        hashTable[1][Hash].push_back(i - l + 1);
    }
}

int commonPrefixLength(const vector<int>& a, const vector<int>& b,
                       const vector< vector<bool> >& marked, size_t i, size_t j) {
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

    int l = (min(a.size(), b.size()) + 4 * minLength) / 5;
    while (true) {
        vector< unordered_map< int, vector<int> > > hashTable(2);
        createHashTable(a, b, l, hashTable);

        int maxMatch = 0;
        vector< pair<int, int> > matches;

        for (auto it : hashTable[0]) {
            for (int i : it.second)
                for (int j : hashTable[1][it.first]) {
                    int prefixLength = commonPrefixLength(a, b, marked, i, j);
                    if (prefixLength > minLength) {
                        if (prefixLength > maxMatch) {
                            maxMatch = prefixLength;
                            matches.clear();
                            matches.push_back(make_pair(i, j));
                        }
                        else if (prefixLength == maxMatch)
                            matches.push_back(make_pair(i, j));
                    }

                }
        }

        for (auto it : matches)
            if (commonPrefixLength(a, b, marked, it.first, it.second) == maxMatch) {
                mark(marked, it.first, it.second, maxMatch);
                commonPartLength += maxMatch;
            }

        if (matches.size() == 0) {
            if (l <= minLength)
                break;
            l = (l + 4 * minLength) / 5;
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

vector<int> zf(const vector<int>& s) {
    vector<int> z(s.size());
    z[0] = 0;
    for (int i = 1, l = 0, r = 0; i < s.size(); i++) {
        if (i < r)
            z[i] = min(r - i - 1, z[i - l]);
        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] > r) {
            r = i + z[i];
            l = i;
        }
    }
    return z;
}

int tokenCompress(const vector<int>& a, const vector<int>& b = vector<int>()) {   /// Плохо реализовано
    vector<int> s = a;
    s.push_back(-1);
    s.insert(s.end(), b.begin(), b.end());
    s.push_back(-2);

    int length = 0;

    for (size_t i = 0; i < a.size(); ) {
        vector<int> z = zf(s);

        int best = 0;
        for (size_t j = a.size() - i + 1; j < s.size(); j++)
            best = max(best, z[j]);

        length += 3;
        if (best > 2) {
            i += best;
            s.erase(s.begin(), s.begin() + best);
            s.insert(s.end(), a.begin() + i, a.begin() + i + best);
        }
        else {
            i++;
            s.erase(s.begin());
            s.push_back(a[i]);
        }
    }

    return length;
}

bool firstHeuristics(const vector<int>& a, const vector<int>& b) {   /// Плохо работает
    int len = lcs(a, b);
    return ((double)len) / (a.size() + b.size() - len) > firstHeuristicsConst;
}

bool secondHeuristics(const set<int>& a, const set<int>& b) {
    int count = 0;
    for (set<int>::iterator it = a.begin(); it != a.end(); it++)
        if (b.find(*it) != b.end())
            count++;
    return ((double)count) / (a.size() + b.size() - count) > secondHeuristicsConst;
}

bool thirdHeuristics(const vector<int>& a, const vector<int>& b) {
    int len = gst(a, b);
    return ((double)len) / (a.size() + b.size() - len) > thirdHeuristicsConst;
}

bool fourthHeuristics(const vector<int>& a, const vector<int>& b) {    /// Плохо реализовано
    vector<int> c = a;
    c.insert(c.end(), b.begin(), b.end());
    return (0.0L + tokenCompress(a) - tokenCompress(a, b)) / tokenCompress(c) > fourthHeuristicsConst;
}

int main(int argc, char* argv[]) {

    string prefix = argv[1];
    sscanf(argv[2], "%lf", &secondHeuristicsConst);
    sscanf(argv[3], "%lf", &thirdHeuristicsConst);
    sscanf(argv[4], "%d", &firstWidthConst);
    sscanf(argv[5], "%d", &secondWidthConst);
    sscanf(argv[6], "%d", &minLengthConst);

    /*secondHeuristicsConst = 0.37;
    thirdHeuristicsConst = 0.37;
    firstWidthConst = 5;
    secondWidthConst = 10;
    minLengthConst = 15;
    string prefix = "";*/

    double startTime = clock();

    ifstream fin((prefix + "input.txt").c_str());

    int n;
    fin >> n;
    vector<string> fileNames(n);
    for (int i = 0; i < n; i++)
        fin >> fileNames[i];

    fin.close();

    set<string> keywords;
    set<string> typewords;

	readKeywords(keywords);
    readTypewords(typewords);

    vector< vector<int> > hashSequences(n);
    vector< set<int> > fingerprints(n);

    int count = 0;
    map<string, int> dict;
    for (int i = 0; i < n; i++) {
        vector<string> text;

        fin.open((prefix + fileNames[i]).c_str());
        readText(fin, text);
        fin.close();

        vector<string> formattedText = formatText(text, fileNames[i], keywords, typewords);
        for (size_t j = 0; j < formattedText.size(); j++) {
            if (dict.find(formattedText[j]) == dict.end())
                dict[formattedText[j]] = count++;
            hashSequences[i].push_back(dict[formattedText[j]]);
        }
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
                double currentTime = clock();
                bool isPlagiat = false;

                if ((currentTime - startTime) / CLOCKS_PER_SEC > 28)
                    isPlagiat = secondHeuristics(fingerprints[i], fingerprints[j]);
                else {
                    isPlagiat = secondHeuristics(fingerprints[i], fingerprints[j]) &&
                                thirdHeuristics(hashSequences[i], hashSequences[j]);
                }

                if (isPlagiat) {
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
        for (size_t j = 0; j < ans[i].size(); j++)
            fout << fileNames[ans[i][j]] << ' ';
        fout << endl;
    }

    fout.close();

	return 0;
}

