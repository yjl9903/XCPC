#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500 + 5;
const long double eps = 1e-100;

int n, m, fin[maxn];
char s[maxn];
long double two[maxn], a[maxn][maxn], ans[maxn];

namespace acam {
  static const int maxp = 100000 + 5;
  static const int S = 2;
  int sz, ch[maxp][S], fail[maxp], len[maxp];
  vector<int> nds[maxp];
  int node() {
    ms(ch[++sz], 0);
    fail[sz] = len[sz] = 0;
    return sz;
  }
  void clear() {
    sz = 0; node();
    for (int i = 0; i < S; i++) ch[0][i] = 1;
  }
  int insert(char* s, int p) {
    int u = 1;
    for (int i = 0; s[i]; i++) {
      int v = s[i] == 'H'; // !
      if (!ch[u][v]) ch[u][v] = node();
      u = ch[u][v];
      len[u] = i + 1;
      nds[u].push_back(p);
    }
    return u;
  }
  void build() {
    queue<int> q; q.push(1);
    while (!q.empty()) {
      int t = q.front(); q.pop();
      for (int i = 0; i < S; i++) {
        if (ch[t][i]) {
          fail[ch[t][i]] = ch[fail[t]][i];
          q.push(ch[t][i]);
        } else {
          ch[t][i] = ch[fail[t]][i];
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      a[i][n + 1] = -1.0;
      int x = fin[i];
      while (x > 1) {
        for (int u: nds[x]) {
          a[u][i] += two[len[x]];
        }
        x = fail[x];
      }
    }
    a[n + 1][n + 2] = 1;
    for (int i = 1; i <= n; i++) {
      a[n + 1][i] = 1;
    }
  }
}

bool solve(int n) {
  for (int i = 1; i <= n; i++) {
    int r = i;
    for (int j = i + 1; j <= n; j++)
      if (abs(a[j][i]) > abs(a[r][i])) r = j;
    if (abs(a[r][i]) < eps) return false;
    swap(a[r], a[i]);
    double inv = a[i][i];
    for (int j = i; j <= n + 1; j++) a[i][j] /= inv;
    for (int j = i + 1; j <= n; j++) {
      double inv = a[j][i];
      for (int k = i; k <= n + 1; k++)
        a[j][k] -= inv * a[i][k];
    }
  }
  for (int i = n; i >= 1; i--) {
    ans[i] = a[i][n + 1];
    for (int j = i + 1; j <= n; j++)
      ans[i] -= a[i][j] * ans[j];
  }
  return true;
}

int main() {
  acam::clear();
  scanf("%d%d", &n, &m);
  two[0] = 1.0;
  for (int i = 1; i <= m; i++) {
    two[i] = two[i - 1] * 2.0;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    fin[i] = acam::insert(s, i);
  }
  acam::build();
  bool f = solve(n + 1);
  for (int i = 1; i <= n; i++) {
    printf("%.6Lf\n", ans[i]);
  }
  return 0;
}