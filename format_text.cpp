#include "format_text.h"

bool isIdentifier(const string& word) {
    bool flag = true;
    for (size_t i = 0; i < word.length(); i++)
        if (!(((word[i] >= '0') && (word[i] <= '9')) ||
              ((word[i] >= 'a') && (word[i] <= 'z')) ||
              ((word[i] >= 'A') && (word[i] <= 'Z')) ||
              word[i] == '_' || word[i] == '.'))
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
              word[i] == '.'))
            flag = false;
    if (!((word[0] >= '0') && (word[0] <= '9')))
        flag = false;
    return flag;
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

void deleteTypedefs(vector<string>& text) {
    for (size_t i = 0; i < text.size(); i++) {
		istringstream in(text[i]);
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

                if (words.back().length() == 1)
                    isCorrect = false;

               /* for (int j = 0; j < words.size() - 1; j++)
                    if (words[j] != "int" && words[j] != "char" && words[j] != "long" && words[j] != "bool" &&
                        words[j] != "short" && words[j] != "unsigned" && words[j] != "float" && words[j] != "double" &&
                        words[j] != "<" && words[j] != ">" && words[j] != ",")
                        isCorrect = false;*/

                if (!isIdentifier(words.back()))
                    isCorrect = false;

                if (isCorrect) {
                    string a = " ";
                    for (size_t j = 0; j < words.size() - 1; j++)
                        a += words[j] + " ";
                    string b = " " + words.back() + " ";

                    if (a.find(b) != string::npos)
                        break;

                    replaceNames(text, b, a);
                }
                else {
                    out << "typedef ";
                    for (size_t j = 0; j < words.size(); j++)
                        out << words[j] << " ";
                    out << word << " ";
                }
            }
            else
                out << word << " ";
        }

        text[i] = " " + out.str();
    }
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

void insertSpaces(vector<string>& text) {
	for (size_t i = 0; i < text.size(); i++) {
		string newLine = " ";
		for (size_t j = 0; j < text[i].length(); j++) {
			if (! ( ((text[i][j] >= '0') && (text[i][j] <= '9')) ||
					((text[i][j] >= 'a') && (text[i][j] <= 'z')) ||
					((text[i][j] >= 'A') && (text[i][j] <= 'Z')) ||
					text[i][j] == '_' || text[i][j] == '.'
				  )) {
				newLine += " ";
				newLine += text[i][j];
				newLine += " ";
			}
			else
				newLine += text[i][j];
		}
		text[i] = newLine + " ";
	}
}

void deleteSpaces(vector<string>& text) {
	for (size_t i = 0; i < text.size(); i++) {
		bool isEmpty = true;
		for (size_t j = 0; j < text[i].length(); j++)
			if (text[i][j] != ' ' && text[i][j] != '\t')
				isEmpty = false;

		if (isEmpty) {
			text.erase(text.begin() + i);
			i--;
		}
		else {
			string newLine = " ";
			istringstream in(text[i]);
			string word;
			while (in >> word)
				newLine += word + " ";
			text[i] = newLine;
		}
	}
}

void deleteBraces(vector<string>& text) {
    for (size_t i = 0; i < text.size(); i++) {
        string newLine = "";
        for (size_t j = 0; j < text[i].length(); j++)
            if (!(text[i][j] == '{' || text[i][j] == '}' || text[i][j] == '(' || text[i][j] == ')'))
                newLine += text[i][j];
        text[i] = newLine;
	}
}

void deleteSemicolons(vector<string>& text) {
    for (size_t i = 0; i < text.size(); i++) {
        string newLine = "";
        for (size_t j = 0; j < text[i].length(); j++)
            if (!(text[i][j] == ';'))
                newLine += text[i][j];
        text[i] = newLine;
	}
}

void replaceNames(vector<string>& text, const string& a, const string& b) {
    for (size_t i = 0; i < text.size(); i++)
        while (text[i].find(a) != string::npos)
            text[i].replace(text[i].find(a), a.length(), b);
}

vector<string> formatText(vector<string> text, const set<string>& keywords) {
	deleteComments(text);
	deleteDirectives(text);

	insertSpaces(text);
	deleteSpaces(text);

	replaceNames(text, " unsigned long long ", " int ");
	replaceNames(text, " unsigned long int ",  " int ");
	replaceNames(text, " long int ",           " int ");
	replaceNames(text, " long long ",          " int ");
	replaceNames(text, " unsigned int ",       " int ");
	replaceNames(text, " unsigned long ",      " int ");
	replaceNames(text, " unsigned ",           " int ");
	replaceNames(text, " long ",               " int ");
	replaceNames(text, " short ",              " int ");
	replaceNames(text, " size_t ",             " int ");
	replaceNames(text, " char ",               " int ");
	replaceNames(text, " bool ",               " int ");
	replaceNames(text, " float ",           " double ");
	replaceNames(text, " long double ",     " double ");

	deleteTypedefs(text);

	deleteBraces(text);
    deleteSemicolons(text);

    deleteSpaces(text);

	vector<string> formattedText;
    for (size_t i = 0; i < text.size(); i++) {
		istringstream in(text[i]);
		string word;
		while (in >> word) {
            if (keywords.find(word) != keywords.end())
                formattedText.push_back(word);
            else if (isNumber(word)) {
                istringstream in(word);
                double num;
                in >> num;

                ostringstream out;
                out.setf(ios::scientific);
                out << num;

                formattedText.push_back(out.str());
            }
            else if (isIdentifier(word))
                formattedText.push_back("id");
            else
                formattedText.push_back(word);
            //cout << formattedText.back() << " ";
        }
        //cout << endl;
    }

    return formattedText;
}
