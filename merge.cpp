#include <iostream>
#include <set>
#include <fstream>

using namespace std;

int main()
{
	ifstream in("keywords.txt");
	ifstream in_t("try.txt");
	set<string> st;
	string s;
	while(in >> s)
		st.insert(s);
	while(in_t >> s)
		st.insert(s);
	in.close();
	ofstream out("keywords.txt");
	for(set<string>::iterator i = st.begin(); i != st.end();i++)
		out << *i << endl;
	return 0;
}
