#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;

double calculateScore() {
	
	double score = 0;
	
	for (int i = 0; i < 10; i++) {
		char my[100];
		char right[100];
		
		sprintf(my, "test/%02d/output.txt", i + 1);
		sprintf(right, "test/%02d/%02d.a", i + 1, i + 1);
		
		
		ifstream fin(right);
		int n;
		fin >> n;
		
		string line;
		getline(fin, line);
		
		set< pair<string, string> > rightPairs;
		
		for (int j = 0; j < n; j++) {
			getline(fin, line);
			
			istringstream in(line);
			
			string fileName;
			vector<string> fileNames;
			while (in >> fileName)
				fileNames.push_back(fileName);
			
			for (size_t u = 0; u < fileNames.size(); u++)
				for (size_t v = u + 1; v < fileNames.size(); v++) {
					rightPairs.insert(make_pair(fileNames[u], fileNames[v]));
					rightPairs.insert(make_pair(fileNames[v], fileNames[u]));
				}
		}
		
		fin.close();
		
		
		fin.open(my);
		fin >> n;
		
		getline(fin, line);
		
		set< pair<string, string> > myPairs;
		
		for (int j = 0; j < n; j++) {
			getline(fin, line);
			
			istringstream in(line);
			
			string fileName;
			vector<string> fileNames;
			while (in >> fileName)
				fileNames.push_back(fileName);
			
			for (size_t u = 0; u < fileNames.size(); u++)
				for (size_t v = u + 1; v < fileNames.size(); v++) {
					myPairs.insert(make_pair(fileNames[u], fileNames[v]));
					myPairs.insert(make_pair(fileNames[v], fileNames[u]));
				}
		}
		
		fin.close();
		
		bool flag = false;
		for (set< pair<string, string> >::iterator it = myPairs.begin(); it != myPairs.end(); it++)
			if (rightPairs.find(*it) == rightPairs.end()) {
				flag = true;
				break;
			}
		
		if (flag) {
			cout << 0 << endl;
			continue;
		}
		
		cout << 100.0 * myPairs.size() / rightPairs.size() << endl;
		score += 100.0 * myPairs.size() / rightPairs.size();
	}
	
	return score;
}
		

int main() {
	srand(clock());
	
	vector< pair<double, double*> > all(1000);
	
	for (int k = 0; k < 10; k++) {
		double cur[5];
		cur[0] = 0.2 * rand() / RAND_MAX + 0.2;
		cur[1] = 0.2 * rand() / RAND_MAX + 0.2;
		cur[2] = rand() % 10 + 3;
		cur[3] = rand() % 20 + 1;
		cur[4] = rand() % 20 + 10;
		
		//#pragma omp parallel for
		for (int i = 0; i < 10; i++) {
			
			char command[100];
			sprintf(command, "./antiplagiat test/%02d/ %lf %lf %d %d %d", i + 1, 
						cur[0], cur[1], (int)(cur[2] + 0.5), (int)(cur[3] + 0.5), (int)(cur[4] + 0.5));
			cout << command << endl;
			system(command);
		}
		
		double score = calculateScore();
		for (int i = 0; i < 5; i++)
			cout << cur[i] << ' ';
		cout << endl;
		cout << score << endl;
		
		all[k].first = -score;
		all[k].second = new double[5];
		for (int j = 0; j < 5; j++)
			all[k].second[j] = cur[j];
	}
	
	sort(all.begin(), all.end());
	
	cout << all[0].first << endl;
	for (int i = 0; i < 5; i++)
		cout << all[0].second[i] << ' ';
	cout << endl;
	
	return 0;
}
