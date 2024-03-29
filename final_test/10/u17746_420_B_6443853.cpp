//gskhirtladze

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <string>

#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define Pii pair < int , int >
#define f_upd(i,a,b) for (int i=a;i<=b;i=(i|(i+1)))
#define f_sum(i,a) for (int i=a;i>=0;i=(i&(i+1))-1)
#define tree int t,int l,int r
#define left 2*t,l,(l+r)/2
#define right 2*t+1,(l+r)/2+1,r
#define g_i(a) scanf("%d",&a)
#define LL long long
#define INF 1000000000
#define eps 0.0000001
#define P7 1000000007
#define P9 1000000009
#define Nmax 500010
#define NB Nmax
#define N 20108
#define S system("pause")

using namespace std;

vector < int > ans;
int in[Nmax],out[Nmax];
int shevida[Nmax],iyo[Nmax];
char a[Nmax];
int b[Nmax];
int n,m,ar,iy,i;
int f[Nmax];
int can[Nmax],k,ma;

main()
 {
  cin>>n>>m;
  for (i=1;i<=m;i++)
   {
    cin>>a[i]>>b[i];
    if (f[b[i]] == 0)
     {
      f[b[i]]=1;
      if (a[i] == '+') shevida[b[i]]=i;
      if (a[i] == '-') iyo[b[i]]=true;
     }
    if (a[i] == '+')
     { ma++; in[b[i]]=1; out[b[i]]=0; } else
     { if (in[b[i]]) ma--; in[b[i]]=0; out[b[i]]=1; }
    if (a[i] == '-')
     {
      if (ma > 0) can[b[i]]=true;
     }
   }
  for (i=1;i<m;i++)
   {
    if (a[i] == '-')
     {
      if (a[i+1] != '+' || b[i+1] != b[i])
       can[b[i]]=true;
     }
   }
  for (k=1;k<=n;k++)
   {
    if (iyo[k]) iy++;
    if (in[k]) ar++;
   }
  if (a[m] == '-')
   {
    if (ar) can[b[m]]=true; else 
     { { in[b[m]]=true; ar++; out[b[m]]=false; } }
   }
  ma=iy;
  for (i=1;i<=m;i++) 
   {
    if (a[i] == '+') ma++; else ma--;
    if (a[i] == '-' && ma > 0) can[b[i]]=true;
   } 
  for (i=1;i<=n;i++)
   {
    if (!in[i] && !out[i])
     { ans.pb(i); continue; }
    if (can[i]) continue;
    if (iyo[i])
     {
      if (in[i]) ans.pb(i); 
      continue;
     }
    if (iy || shevida[i] > 1) continue;
    if (in[i]) ans.pb(i);
   }
  sort(ans.begin(),ans.end());
  cout<<ans.size()<<endl;
  for (i=0;i<ans.size();i++)
   cout<<ans[i]<<" ";
  cout<<endl;
 }
