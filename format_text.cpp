#include "format_text.h"

Languages determineLanguage(string fileName) {
    fileName.erase(0, fileName.find('.') + 1);
    if (fileName == "cpp")
        return CPP;
    if (fileName == "java")
        return JAVA;
    if (fileName == "c")
        return C;
    if (fileName == "py")
        return PY;
    if (fileName == "pas")
        return PAS;
    if (fileName == "cs")
        return CS;
    return EXOTIC;
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
              ((word[i] >= 'A') && (word[i] <= 'Z'))) )
            flag = false;
    if (!((word[0] >= '0') && (word[0] <= '9')))
        flag = false;
    return flag;
}

void deleteStrangeSymbols(string& text) {
    string newLine = "";
    for (size_t i = 0; i < text.length(); i++)
        if (32 <= text[i] && 128 > text[i])
            newLine += text[i];
    text = newLine;
}

void deleteDirectives(vector<string>& text) {
    for (size_t i = 0; i < text.size(); i++) {
		istringstream in(text[i]);
		string word;
		in >> word;
		if (word[0] == '#')
            text[i] = "";
    }
}

void deleteTypedefs(string& text, set<string>& typewords) {
    vector< pair<string, string> > needToReplace;

    istringstream in(text);
    string word;

    ostringstream out;
    while (in >> word) {
        if (word == "typedef") {
            vector<string> words;

            while ((in >> word) && (word != ";"))
                words.push_back(word);

            bool isCorrect = true;

            if (word != ";")
                isCorrect = false;

            if (words.size() < 2)
                isCorrect = false;

            if (words.size() > 15)
                isCorrect = false;

            for (int j = 0; j < words.size() - 1; j++)
                if (typewords.find(words[j]) == typewords.end())
                    isCorrect = false;

            if (!isIdentifier(words.back()))
                isCorrect = false;

            if (isCorrect) {
                string a = " ";
                for (size_t j = 0; j < words.size() - 1; j++)
                    a += words[j] + " ";
                string b = " " + words.back() + " ";

                typewords.insert(words.back());

                if (a.find(b) != string::npos)
                    break;

                needToReplace.push_back(make_pair(b, a));
            }
            else {
                out << " typedef ";
                for (size_t j = 0; j < words.size(); j++)
                    out << words[j] << " ";
                out << word << " ";
            }
        }
        else
            out << word << " ";
    }

    text = " " + out.str();

    for (size_t i = 0; i < needToReplace.size(); i++)
        replaceNames(text, needToReplace[i].first, needToReplace[i].second);
}

void deleteComments(vector<string>& text) {
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

void insertSpaces(string& text) {
    string newLine = " ";
    for (size_t i = 0; i < text.length(); i++) {
        if (text[i] == '.')
            newLine += " ";
        else if (! ( ((text[i] >= '0') && (text[i] <= '9')) ||
                     ((text[i] >= 'a') && (text[i] <= 'z')) ||
                     ((text[i] >= 'A') && (text[i] <= 'Z')) ||
                       text[i] == '_')) {
            newLine += " ";
            newLine += text[i];
            newLine += " ";
        }
        else
            newLine += text[i];
    }
    text = newLine + " ";
}

void deleteSpaces(string& text) {
    string newLine = " ";
    istringstream in(text);
    string word;
    while (in >> word)
        newLine += word + " ";
    text = newLine;
}

void replaceNames(string& text, const string& a, const string& b) {
    while (text.find(a) != string::npos)
        text.replace(text.find(a), a.length(), b);
}

void addTypewords(string& text, set<string>& typewords) {
    istringstream in(text);
    string word;
    while (in >> word) {
        if (word == "struct" || word == "class" || word == "enum" || word == "typename") {
            in >> word;
            typewords.insert(word);
        }
    }
}

bool canBeFunction(const vector<string>& words, int pos) {
    if (!isIdentifier(words[pos]))
        return false;

    pos++;
    if (pos >= words.size() || words[pos] != "(")
        return false;

    pos++;
    int balance = 1;
    while (pos < words.size() && balance) {
        if (words[pos] == "(")
            balance++;
        if (words[pos] == ")")
            balance--;
        pos++;
    }

    if (pos >= words.size())
        return false;

    return words[pos] == "{" || words[pos] == "try" || words[pos] == "throws";
}

vector<Function> findFunctions(string& text, const set<string>& typewords) {
                        /** Осторожно, быдлокод! */
    istringstream IN(text);
    string word;
    vector<string> words;
    while (IN >> word)
        words.push_back(word);

    vector<Function> functions;

    States s = START;
    Function f;
    int balance = 0;

    int begin = -1;
    int pos = 0;
    istringstream in(text);
    while (in >> word) {
        switch (s) {
        case FINISH:
            f.body = "";
            begin = -1;
            s = START;
        case START:
            if (canBeFunction(words, pos)) {
                if (begin == -1)
                    f.begin = (int)in.tellg() - word.length();
                else
                    f.begin = begin;

                if (typewords.find(word) != typewords.end())
                    f.name = "__CONSTRUCTOR__";
                else
                    f.name = word;
                s = NAME;
            }
            else if (typewords.find(word) != typewords.end()) {
                if (begin == -1)
                    begin = (int)in.tellg() - word.length();
            }
            else
                begin = -1;
            break;
        case NAME:
            if (word == "(")
                s = BRACE_1;
            else
                s = FINISH;
            break;
        case BRACE_1:
            if (word == ")") {
                if (balance == 0)
                    s = BRACE_2;
                else
                    balance--;
            }
            if (word == "(")
                balance++;
            break;
        case BRACE_2:
            if (word == "{")
                s = BRACE_3;
            else if (word == "throws") {
                while (word != "{") {
                    in >> word;
                    pos++;
                }
                s = BRACE_3;
            }
            else if (word != "try")
                s = FINISH;
            break;
        case BRACE_3:
            if (word == "}") {
                if (balance == 0) {
                    f.end = in.tellg();
                    functions.push_back(f);
                    s = FINISH;
                }
                else
                    balance--;
            }
            else if (word == "{")
                balance++;
            else
                f.body += " " + word + " ";
            break;
        };

        pos++;
    }
    return functions;
}

vector<bool> findUsedFunctions(const vector<Function>& functions) {
    map<string, int> dict;

    for (size_t i = 0; i < functions.size(); i++)
        dict[functions[i].name] = i;

    if (dict.find("main") == dict.end())
        return vector<bool>(functions.size(), true);

    vector<bool> used(functions.size(), false);

    vector<int> q;
    q.push_back(dict["main"]);
    used[dict["main"]] = true;

    for (size_t i = 0; i < functions.size(); i++)
        if (functions[i].name == "__CONSTRUCTOR__") {
            q.push_back(i);
            used[i] = true;
        }

    while (q.size()) {
        int v = q.back();
        q.pop_back();

        istringstream in(functions[v].body);
        string s;
        while (in >> s)
            if (dict.find(s) != dict.end())
                if (!used[dict[s]]) {
                    used[dict[s]] = true;
                    q.push_back(dict[s]);
                }
    }

    return used;
}

vector<string> formatText(vector<string> text, string fileName,
                          const set<string>& keywords, set<string> typewords) {
    Languages l = determineLanguage(fileName);

	deleteComments(text);

	if (l == CPP || l == C || l == CS)
        deleteDirectives(text);

    string oneLineText = "";
	for (size_t i = 0; i < text.size(); i++)
        oneLineText += " " + text[i] + " ";

	deleteStrangeSymbols(oneLineText);

    insertSpaces(oneLineText);
    deleteSpaces(oneLineText);

    if (l == CPP || l == JAVA || l == CS || l == C) {
        replaceNames(oneLineText, " . ",                      " ");
        replaceNames(oneLineText, " - > ",                    " ");
        replaceNames(oneLineText, " : ",                      " ");
        replaceNames(oneLineText, " unsigned long long ", " int ");
        replaceNames(oneLineText, " unsigned long int ",  " int ");
        replaceNames(oneLineText, " long int ",           " int ");
        replaceNames(oneLineText, " long long ",          " int ");
        replaceNames(oneLineText, " unsigned int ",       " int ");
        replaceNames(oneLineText, " unsigned long ",      " int ");
        replaceNames(oneLineText, " unsigned ",           " int ");
        replaceNames(oneLineText, " long ",               " int ");
        replaceNames(oneLineText, " short ",              " int ");
        replaceNames(oneLineText, " size_t ",             " int ");
        replaceNames(oneLineText, " float ",           " double ");
        replaceNames(oneLineText, " long double ",     " double ");
        replaceNames(oneLineText, " public ",                 " ");
        replaceNames(oneLineText, " private ",                " ");
        replaceNames(oneLineText, " protected ",              " ");
        replaceNames(oneLineText, " static ",                 " ");
        replaceNames(oneLineText, " volatile ",               " ");
        replaceNames(oneLineText, " virtual ",                " ");
        replaceNames(oneLineText, " abstract ",               " ");
        replaceNames(oneLineText, " inline ",                 " ");
        replaceNames(oneLineText, " std : : ",                " ");
        replaceNames(oneLineText, " : : ",                    " ");
        replaceNames(oneLineText, " unordered_map ",      " map ");
        replaceNames(oneLineText, " Integer ",            " int ");
        replaceNames(oneLineText, " String ",          " string ");
        replaceNames(oneLineText, " Character ",         " char ");
        replaceNames(oneLineText, " BigInteger ",         " int ");
        replaceNames(oneLineText, " Boolean ",           " bool ");
        replaceNames(oneLineText, " Short ",              " int ");
        replaceNames(oneLineText, " Long ",               " int ");
        replaceNames(oneLineText, " BigDecimal ",      " double ");
        replaceNames(oneLineText, " List ",            " vector ");
        replaceNames(oneLineText, " ArrayList ",       " vector ");
        replaceNames(oneLineText, " Vector ",          " vector ");
        replaceNames(oneLineText, " LinkedList ",      " vector ");
        replaceNames(oneLineText, " Stack ",           " vector ");
        replaceNames(oneLineText, " Set ",                " set ");
        replaceNames(oneLineText, " HashSet ",            " set ");
        replaceNames(oneLineText, " SortedSet ",          " set ");
        replaceNames(oneLineText, " TreeSet ",            " set ");
        replaceNames(oneLineText, " LinkedHashSet ",      " set ");
        replaceNames(oneLineText, " stack ",           " vector ");
        replaceNames(oneLineText, " list ",            " vector ");
        replaceNames(oneLineText, " Deque ",            " deque ");
        replaceNames(oneLineText, " Queue ",            " queue ");
        replaceNames(oneLineText, " Map ",                " map ");
        replaceNames(oneLineText, " SortedMap ",          " map ");
        replaceNames(oneLineText, " TreeMap ",            " map ");
        replaceNames(oneLineText, " HashMap ",            " map ");
        replaceNames(oneLineText, " LinkedHashMap ",      " map ");
        replaceNames(oneLineText, " HashTable ",          " map ");
        replaceNames(oneLineText, " SortedDictionary ",   " map ");
        replaceNames(oneLineText, " Dictionary ",         " map ");
    }

    addTypewords(oneLineText, typewords); /// Добавляет классы, структуры, объединения

    if (l == CPP || l == C)
        deleteTypedefs(oneLineText, typewords);

    vector<Function> functions = findFunctions(oneLineText, typewords);
    set<string> functionNames;
    for (size_t i = 0; i < functions.size(); i++)
        functionNames.insert(functions[i].name);

    if (l == CPP || l == C || l == JAVA) {
        /// Удаляем все, кроме используемых функций и конструкторов.
        /// Конструкторы не удаляются, потому что лень было искать какие из них используются
        vector<bool> used = findUsedFunctions(functions);

        int end = oneLineText.length();
        for (int i = functions.size() - 1; i >= 0; i--) {
            oneLineText.erase(functions[i].end, end - functions[i].end);
            end = functions[i].begin;

            if (!used[i])
                oneLineText.erase(functions[i].begin, functions[i].end - functions[i].begin);
        }
        oneLineText.erase(0, end);
    }

	replaceNames(oneLineText, " ( ", " ");
	replaceNames(oneLineText, " ) ", " ");
	replaceNames(oneLineText, " { ", " ");
	replaceNames(oneLineText, " } ", " ");
	replaceNames(oneLineText, " ; ", " ");

    deleteSpaces(oneLineText);

	vector<string> formattedText;
    istringstream in(oneLineText);
    string word;
    while (in >> word) {
        if (keywords.find(word) != keywords.end())
            formattedText.push_back(word);
        else if (functionNames.find(word) != functionNames.end())
            formattedText.push_back("func");
        else if (typewords.find(word) != typewords.end() && isIdentifier(word))
            formattedText.push_back("type");
        else if (isNumber(word))
            //formattedText.push_back("number");
            formattedText.push_back("id");
        else if (isIdentifier(word))
            formattedText.push_back("id");
        else
            formattedText.push_back(word);
    }

    return formattedText;
}

