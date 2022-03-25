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
const int maxn = 200000 + 5;

int n, ed[maxn];
char s[maxn];

namespace sam {
  int sz, last, cnt[maxn << 1];
  int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26], ed[maxn << 1];
  void clear() {
    for (int i = 1; i <= sz; i++) {
      len[i] = link[i] = cnt[i] = ed[i] = 0;
      ms(ch[i], 0);
    }
    sz = last = 1;
  }
  int insert(int c, int i) {
    int cur = ++sz, p = last;
    len[cur] = len[last] + 1;
    cnt[cur] = 1;
    for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
    if (!p) link[cur] = 1;
    else {
      int q = ch[p][c];
      if (len[p] + 1 == len[q]) link[cur] = q;
      else {
        int nq = ++sz;
        len[nq] = len[p] + 1;
        link[nq] = link[q];
        link[q] = link[cur] = nq;
        memcpy(ch[nq], ch[q], sizeof ch[q]);
        for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
      }
    }
    ed[cur] = i;
    return last = cur;
  }
  vector<int> edge[maxn << 1];
  double solve() {
    for (int i = 1; i <= sz; i++) {
      edge[i].clear();
    }
    for (int i = 2; i <= sz; i++) {
      edge[link[i]].push_back(i);
    }
    function<double(int)> dfs = [&](int u) -> double {
      if (ed[u]) return len[u] - len[link[u]];
      double sum = 0;
      for (int v: edge[u]) {
        sum += 1.0 / dfs(v);
      }
      return len[u] - len[link[u]] + 1.0 / sum;
    };
    return dfs(1);
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    sam::clear();
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = n; i >= 1; i--) {
      sam::insert(s[i] - 'a', n - i + 1);
    }
    printf("%.9lf\n", sam::solve());
  }
  return 0;
}