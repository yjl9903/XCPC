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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const int maxn = 400000 + 5;

string words[maxn];
vector<int> edge[maxn];
char s[maxn];
int n, sz = 1, tot, ch[maxn][26], pos[maxn], rId[maxn], ord[maxn];

int insert(char s[]) {
  int u = 1;
  for (int i = 0; s[i]; i++) {
    int c = s[i] - 'a';
    if (!ch[u][c]) {
      ch[u][c] = ++sz;
      edge[u].push_back(sz);
      edge[sz].push_back(u);
    }
    u = ch[u][c];
  }
  return u;
}

void predfs(int u) {
  ord[u] = ++tot;
  for (int c = 0; c < 26; c++) {
    if (ch[u][c]) {
      predfs(ch[u][c]);
    }
  }
}

int mn = inf, rt = -1, siz[maxn];
void dfs(int u) {
  siz[u] = u == 1 || rId[u] != 0;
  int mx = 0;
  for (int c = 0; c < 26; c++) {
    int v = ch[u][c];
    if (!v) continue;
    dfs(v);
    siz[u] += siz[v];
    mx = max(mx, siz[v]);
  }
  mx = max(mx, n + 1 - siz[u]);
  if (mx < mn) {
    mn = mx; rt = u;
  }
}

int aSum = 0, bSum = 0;
int col[maxn];
vector<int> bag[maxn];
void color(int u, int f, int c, int d = 1) {
  if (u == 1 || rId[u]) {
    aSum += d;
  }
  col[u] = c;
  for (int v: edge[u]) {
    if (v == f) continue;
    color(v, u, c, d + 1);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    bSum += strlen(s);
    words[i] = s;
    pos[i] = insert(s);
    rId[pos[i]] = i;
  }
  if (n == 1) {
    puts(s); return 0;
  }
  predfs(1); dfs(1);
  assert(rt != -1);
  for (int i = 0; i < (int)edge[rt].size(); i++) {
    color(edge[rt][i], rt, i + 1);
  }

  bag[col[1]].push_back(1);
  for (int i = 1; i <= n; i++) {
    int u = pos[i];
    bag[col[u]].push_back(u);
  }
  for (int i = 0; i <= (int)edge[rt].size(); i++) {
    if (bag[i].empty()) continue;
    sort(begin(bag[i]), end(bag[i]), [&](int x, int y) {
      return ord[x] > ord[y];
    });
  }
  int last = col[1]; bag[col[1]].pop_back();
  for (int t = 2; t <= n + 1; t++) {
    int choice = -1, co = -1;
    int fS = 0, sS = 0;
    for (int i = 0; i <= (int)edge[rt].size(); i++) {
      int x = bag[i].size();
      if (x >= fS) {
        sS = fS; fS = x;
      } else if (x > sS) {
        sS = x;
      }
    }
    for (int i = 0; i <= (int)edge[rt].size(); i++) {
      if (i == last) continue;
      if (bag[i].empty()) continue;
      if (i == col[1]) {
        int nSz = (int)bag[col[1]].size() - 1;
        if (nSz + nSz >= n + 1 - t) continue;
      } else {
        int nSz = (int)bag[col[1]].size();
        if (nSz + nSz > n + 1 - t) continue;
      }
      int u = bag[i].back();
      int sz = max(fS == (int)bag[i].size() ? sS : fS, (int)bag[i].size() - 1);
      // if (t < n && sz + sz > 1 + n + 1 - t) continue;
      if (sz + sz > 1 + n + 1 - t) continue;
      if (choice == -1 || ord[u] < ord[choice]) {
        choice = u; co = i;
      }
    }
    assert(choice != -1);
    bag[co].pop_back();
    last = co;
    puts(words[rId[choice]].c_str());
  }
  return 0;
}