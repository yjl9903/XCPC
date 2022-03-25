#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <map>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;
PII a[maxn];

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    map<int,vector<int> > row;
    map<int,int> col, colcnt;
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &a[i].first, &a[i].second);
      col[a[i].second]++;
      if (row.count(a[i].first)) {
        row[a[i].first].push_back(a[i].second);
      } else {
        row[a[i].first] = vector<int>(1, a[i].second);
      }
    }
    for (auto& x: col) colcnt[x.second]++;
    pair<int,ll> ans;
    auto merge = [&](int x, int y) {
      if (x > ans.first) {
        ans.first = x; ans.second = y;
      } else if (x == ans.first) {
        ans.second += y;
      }
    };
    for (auto& r: row) {
      for (auto& x: r.second) {
        colcnt[col[x]]--;
        if (colcnt[col[x]] == 0) {
          colcnt.erase(col[x]);
        }
        col[x]--;
        colcnt[col[x]]++;
      }
      int mx = (int)r.second.size() + colcnt.rbegin()->first;
      int sum = colcnt.rbegin()->second;
      dbg(mx, sum);
      merge(mx, sum);
      for (auto& x: r.second) {
        colcnt[col[x]]--;
        if (colcnt[col[x]] == 0) {
          colcnt.erase(col[x]);
        }
        col[x]++;
        colcnt[col[x]]++;
      }
    }
    if (ans.first == 2) {
      ans.second = 1ll * n * (n - 1) / 2;
    }
    printf("Case %d: %d %I64d\n", ++kase, ans.first, ans.second);
  }
  return 0;
}