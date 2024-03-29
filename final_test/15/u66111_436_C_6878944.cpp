#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define fi first
#define se second
#define px real()
#define py imag()
#define rep(i, n) for (int i=0, _##i=(n); i<_##i; ++i)
#define dwn(i, n) for (int i=(n); --i>=0; )
#define repr(i, l, r) for (int i=(l), _##i=(r); i<_##i; ++i)
#define dwnr(i, l, r) for (int i=(r), _##i=(l); --i>=_##i; )
#define repi(i, n) for (__typeof((n).begin()) i=(n).begin(), _##i=n.end(); i != _##i; ++i)
#define dwni(i, n) for (__typeof((n).rbegin()) i=(n).rbegin(), _##i=(n).rend(); i!=_##i; ++i)
#define repv(i, n) for (int i=0, _##i=((n).size()); i<_##i; ++i)
#define dwnv(i, n) for (int i=((n).size()); --i>=0; )
#define sz(x) int((x).size())
#define print(x) cerr << #x << ": " << x << endl

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<double> pnt;
typedef vector<int> vi;

template <class T> T min(T a, T b, T c) { return min(a, min(b, c)); }
template <class T> T max(T a, T b, T c) { return max(a, max(b, c)); }
template <class T> void setmin(T& a, T b) { if (b < a) a = b; }
template <class T> void setmax(T& a, T b) { if (b > a) a = b; }

const int MAXN = 1005;

int n, m, k, w;
char mat[MAXN][15][15];
int dist[MAXN][MAXN];
int par[MAXN];

typedef pair<int, pii> piii;
vector<piii> edges;

vector<int> adj[MAXN];
bool vis[MAXN];

void dfs(int cur, int p) {
    if (vis[cur]) return;
    vis[cur] = 1;
    if (cur) cout << cur << ' ' << p << '\n';
    for (int i=0; i<adj[cur].size(); i++)
        dfs(adj[cur][i], cur);
}

int getpar(int a) { return par[a] == a ? a : par[a] = getpar(par[a]); }
void merge(int a, int b) { par[getpar(a)] = getpar(b); }

int dif(int a, int b) {
    int ret = 0;
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            if (mat[a][i][j] != mat[b][i][j])
                ret++;
    return ret;
}

int main() {
    ios :: sync_with_stdio(0);

    if (fopen("input.txt", "r")) freopen("input.txt", "r", stdin);

    cin >> n >> m >> k >> w;
    for (int ii=1; ii<=k; ii++)
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                cin >> mat[ii][i][j];
    for (int i=1; i<=k; i++)
        dist[i][0] = dist[0][i] = n*m;
    for (int i=1; i<=k; i++)
        for (int j=1; j<=k; j++)
            dist[i][j] = dist[j][i] = dif(i, j)*w;
    for (int i=0; i<=k; i++)
        for (int j=0; j<=k; j++)
            edges.push_back(piii(dist[i][j], pii(i, j)));
    for (int i=0; i<=k; i++) par[i] = i;

    sort(edges.begin(), edges.end());

    int res = 0;
    for (int i=0; i<edges.size(); i++) {
        pii p = edges[i].se;
        int a = p.fi, b = p.se;
        if (getpar(a) != getpar(b)) {
            merge(a, b);
            res += edges[i].fi;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }

    cout << res << '\n';
    dfs(0, 0);
}
