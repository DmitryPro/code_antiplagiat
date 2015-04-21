#include <algorithm>
#include <iomanip>
#include <istream>
#include <limits>
#include <map>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
// Solution template generated by caide


class Solution {
public:
	const int UNKNOWN = numeric_limits<int>::min();

    void solve(std::istream& in, std::ostream& out) {
		int n, k;
		in >> n >> k;
		vector<int> a(n);
		for (int i = 0; i < n; ++i) {
			string s;
			in >> s;
			if (s[0] == '?')
				a[i] = UNKNOWN;
			else {
				istringstream is(s);
				is >> a[i];
			}
		}
		
		for (int i = 0; i < k; ++i) {
			vector<int> u;
			for (int j = i; j < n; j += k)
				u.push_back(a[j]);
			if (!solve(u)) {
				out << "Incorrect sequence" << endl;
				return;
			}
			for (int j = i, t = 0; t < u.size(); j += k, ++t) {
				a[j] = u[t];
			}
		}

		for (int i : a)
			out << i << " ";
		out << endl;
    }

	bool solve(vector<int>& a) {
		const int n = a.size();
		int first = 0;
		while (first < n && a[first] == UNKNOWN)
			++first;
		if (first == n) {
			first = -(n / 2);
			for (int i = 0; i < n; ++i)
				a[i] = first++;
			return true;
		}
		vector<int> prefix = solveOneSide(first, a[first]);
		if (prefix.size() != first)
			return false;
		for (int i = 0; i < first; ++i)
			a[i] = prefix[i];

		while (true) {
			int next = first + 1;
			while (next < n && a[next] == UNKNOWN) {
				++next;
			}
			if (next == n) {
				vector<int> suffix = solveOneSide(n - first - 1, -a[first]);
				if (suffix.size() != n - first - 1)
					return false;
				for (int i = 0; i < n - first - 1; ++i) {
					a[n - i - 1] = -suffix[i];
				}
				return true;
			}
			if (a[first] >= a[next])
				return false;
			vector<int> infix = solveTwoSide(a[first], next - first - 1, a[next]);
			if (infix.size() != next - first - 1)
				return false;
			for (int i = 0; i < next - first - 1; ++i)
				a[first + i + 1] = infix[i];
			first = next;
		}
	}

	vector<int> solveOneSide(int sz, int last) {
		vector<int> res(sz);
		if (sz == 0)
			return res;

		last = min(last - 1, sz / 2);
		for (int i = sz - 1; i >= 0; --i)
			res[i] = last--;
		return res;
	}

	vector<int> solveTwoSide(int first, int sz, int last) {
		vector<int> res(sz);
		if (sz == 0 || last - first < sz + 1)
			return vector<int>();
		if (last <= 0) {
			for (int i = sz - 1; i >= 0; --i)
				res[i] = --last;
			return res;
		}
		if (first >= 0) {
			for (int i = 0; i < sz; ++i)
				res[i] = ++first;
			return res;
		}
		set<int> nums;
		nums.insert(0);
		for (int i = 1; nums.size() < sz; ++i) {
			if (i < last)
				nums.insert(i);
			if (-i > first)
				nums.insert(-i);
		}
		std::copy(nums.begin(), nums.end(), res.begin());
		return res;
	}
};

void solve(std::istream& in, std::ostream& out)
{
    out << std::setprecision(12);
    Solution solution;
    solution.solve(in, out);
}
#include <fstream>
#include <iostream>


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;

    ostream& out = cout;
    solve(in, out);
    return 0;
}
