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
const int maxn = 100000 + 5;

char s[maxn];
int n;
set<int> edge[30];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 0; i < 26; i++) {
      edge[i].clear();
    }
    for (int i = 2; i <= n; i++) {
      edge[s[i] - 'a'].insert(s[i - 1] - 'a');
      edge[s[i - 1] - 'a'].insert(s[i] - 'a');
    }
    bool flag = true;
    for (int i = 0; i < 26; i++) {
      if ((int)edge[i].size() > 2) {
        flag = false;
      }
    }
    if (!flag) {
      puts("NO"); continue;
    }
    int step = 1;
    string ans;
    vector<int> vis(26, 0);
    function<void(int,int)> dfs = [&](int u, int f) {
      if (!flag) return ;
      vis[u] = 1; ans += (u + 'a');
      for (int v: edge[u]) {
        if (v == f) continue;
        if (vis[v]) {
          if (step == 1) flag = false;
          return ;
        }
        dfs(v, u);
      }
    };
    for (int i = 0; i < 26 && flag; i++) {
      if (vis[i]) continue;
      dfs(i, -1);
    }
    step = 2;
    vis.assign(26, 0); ans.clear();
    for (int i = 0; i < 26 && flag; i++) {
      if (vis[i] || (int)edge[i].size() > 1) continue;
      dfs(i, -1);
    }
    if (flag) {
      puts("YES");
      puts(ans.c_str());
    } else {
      puts("NO");
    }
  }
  return 0;
}