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
const int maxn = 300000 + 5;

int n, k, last[maxn];
bool a[maxn];
char s[maxn];
vector<int> bag[maxn], vis[maxn];

int main() {
  scanf("%d%d%s", &n, &k, s + 1);
  for (int i = 1; i <= n; i++) a[i] = s[i] - '0';
  for (int i = 1; i <= k; i++) {
    int m, x; scanf("%d", &m);
    while (m--) {
      scanf("%d", &x);
      bag[i].push_back(x);
      vis[x].push_back(i);
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i]) {
      printf("%d\n", ans);
    } else {
      int cho = vis[i][0];
      if ((int)vis[i].size() == 2) {
        if (cho == last[i]) {
          cho = vis[i][1];
        } else {
          int s1 = end(bag[vis[i][0]]) - upper_bound(begin(bag[vis[i][0]]), end(bag[vis[i][0]]), i);
          int s2 = end(bag[vis[i][1]]) - upper_bound(begin(bag[vis[i][1]]), end(bag[vis[i][1]]), i);
          if (s1 > s2) {
            cho = vis[i][1];
          }
        }
      }
      ans++;
      set<int> st;
      for (int x: bag[cho]) {
        a[x] ^= 1; last[x] = cho;
        if (x < i) {
          st.insert(x);
        }
      }
      function<void(int)> dfs = [&](int u) {
        assert((int)vis[u].size() == 2);
        int i = vis[u][0];
        if (vis[u][0] == last[u]) i = vis[u][1];
        ans++;
        for (int x: bag[i]) {
          a[x] ^= 1; last[x] = i;
          if (x < i && a[x]) {
            st.erase(x);
          }
        }
      };
      while (!st.empty()) {
        dfs(*st.begin());
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}