#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 19;

int n;
ll chain[maxn][1 << maxn], suml[maxn][1 << maxn], ans[1 << maxn];
bool g[maxn][maxn];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    char s[20]; scanf("%s", s);
    for (int j = 0; j < n; j++) {
      g[i][j] = s[j] - '0';
    }
    chain[i][1 << i] = 1;
  }
  int ss = 1 << n;
  for (int s = 0; s < ss; s++) {
    for (int i = 0; i < n; i++) {
      if (s >> i & 1) {
        for (int j = 0; j < n; j++) {
          if (i == j || !g[i][j]) continue;
          if (s >> j & 1) {
            chain[i][s] += chain[j][s ^ (1 << i)];
          }
        }
        suml[__builtin_popcount(s)][s] += chain[i][s];
      }
    }
  }
  for (int len = 1; len <= n; len++) {
    for (int i = 0; i < n; i++) {
      for (int s = 0; s < ss; s++) {
        if (s & (1 << i)) {
          suml[len][s] += suml[len][s - (1 << i)];
        }
      }
    }
  }
  map<vector<int>, vector<int> > pat;
  for (int s = 0; s < ss / 2; s++) {
    vector<int> v;
    int tot = 0;
    for (int i = 0; i < n - 1; i++) {
      if (s >> i & 1) {
        tot++;
      } else {
        v.push_back(tot + 1);
        tot = 0;
      }
    }
    v.push_back(tot + 1);
    sort(begin(v), end(v));
    pat[v].push_back(s);
  }
  vector<int> stk;
  function<void(int,int,vector<ll>)> dfs = [&](int n, int st, vector<ll> g) {
    if (n == 0) {
      ll sum = 0;
      for (int s = 0; s < ss; s++) {
        if (__builtin_popcount(s ^ (ss - 1)) % 2 == 0) {
          sum += g[s];
        } else {
          sum -= g[s];
        }
      }
      for (auto s: pat[stk]) {
        ans[s] = sum;
      }
      return ;
    }
    for (int i = st; i <= n; i++) {
      if (i != n && i + i > n) continue;
      stk.push_back(i);
      auto tot = g;
      for (int s = 0; s < ss; s++) {
        tot[s] *= suml[i][s];
      }
      dfs(n - i, i, tot);
      stk.pop_back();
    }
  };
  dfs(n, 1, vector<ll>(1 << n, 1));
  for (int i = 0; i < (n - 1); i++) {
    for (int s = 0; s < ss / 2; s++) {
      if (((s >> i) & 1) == 0) {
        ans[s] -= ans[s + (1 << i)];
      }
    }
  }
  for (int s = 0; s < ss / 2; s++) {
    printf("%I64d ", ans[s]);
  }
  return 0;
}