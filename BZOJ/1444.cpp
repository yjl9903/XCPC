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
#include <queue>
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
const int maxn = 1000 + 5;

const double eps = 1e-5;

int n, l, S, fin[maxn];
double p[20];
char s[maxn];

namespace acam {
  static const int maxp = 100000 + 5;
  static const int S = 26;
  static const int Base = 'A';
  int sz, ch[maxp][10], fail[maxp], val[maxp];;
  int node() {
    ms(ch[++sz], 0);
    fail[sz] = val[sz] = 0;
    return sz;
  }
  void clear() {
    sz = 0; node();
    for (int i = 0; i < S; i++) ch[0][i] = 1;
  }
  int insert(char* s, int i) {
    int u = 1;
    for (int i = 0; s[i]; i++) {
      int v = s[i] - Base; // !
      if (!ch[u][v]) ch[u][v] = node();
      u = ch[u][v];
    }
    val[u]++;
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
  }
}
using namespace acam;

double a[maxn][maxn], ans[maxn];
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
  scanf("%d%d%d", &n, &l, &S);
  acam::clear();
  for (int i = 0, a, b; i < S; i++) {
    scanf("%d%d", &a, &b);
    p[i] = double(a) / b;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    fin[i] = acam::insert(s, i);
  }
  acam::build();
  for (int i = 1; i <= sz; i++) {
    a[i][i] = -1;
  }
  for (int i = 1; i <= sz; i++) {
    if (val[i]) continue;
    for (int j = 0; j < S; j++) {
      a[ch[i][j]][i] += p[j];
    }
  }
  a[1][sz + 1] = 1;
  for (int i = 1; i <= sz; i++) {
    if (val[i]) {
      a[1][i] = 1;
    } else {
      a[1][i] = 0;
    }
  }
  bool x = solve(sz);

  for (int i = 1; i <= n; i++) {
    double r = ans[fin[i]];
    if (r > 0) {
      printf("%.2lf\n", r);
    } else {
      puts("0.00");
    }
  }
  return 0;
}