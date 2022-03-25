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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

struct Mat {
  static const int M = 102;
  ll a[M][M];
  Mat() { ms(a, 0); }
  void clear() { ms(a, 0); }
  void eye() { for (int i = 0; i < M; i++) a[i][i] = 1; }
  ll* operator [] (int x) { return a[x]; }
  const ll* operator [] (int x) const { return a[x]; }
  Mat operator * (const Mat& b) {
    const Mat& a = *this; Mat r;
    for (int i = 0; i < M; i++)
      for (int j = 0; j < M; j++)
        for (int k = 0; k < M; k++)
          r[i][j] = (r[i][j] + a[i][k] * b[k][j]) % mod;
    return r;
  }
  Mat pow(ll n) const {
    Mat a = *this, r; r.eye();
    while (n > 0) {
      if (n & 1)  r = r * a;
      n >>= 1; a = a * a;
    }
    return r;
  }
  void print() const {
    for (int i = 0; i < M; i++) for (int j = 0; j < M; j++)
      printf("%lld%c", (*this)[i][j], " \n"[j == M - 1]);
  }
} trans, f;

namespace acam {
  static const int maxp = 10000 + 5;
  static const int S = 26;
  static const int Base = 'a';
  int sz, ch[maxp][S], fail[maxp];
  bool danger[maxp];
  int node() {
    ms(ch[++sz], 0);
    fail[sz] = danger[sz] = 0;
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
    danger[u] = true;
    return u;
  }
  void build() {
    queue<int> q; q.push(1);
    while (!q.empty()) {
      int t = q.front(); q.pop();
      for (int i = 0; i < S; i++) {
        if (ch[t][i]) {
          fail[ch[t][i]] = ch[fail[t]][i];
          danger[ch[t][i]] |= danger[fail[ch[t][i]]];
          q.push(ch[t][i]);
        } else {
          ch[t][i] = ch[fail[t]][i];
        }
      }
    }
    for (int u = 1; u <= sz; u++) {
      for (int c = 0; c < S; c++) {
        int v = ch[u][c];
        if (danger[v]) continue;
        trans[v - 1][u - 1]++;
      }
    }
  }
}

int n, L;
char s[105];

int main() {
  acam::clear();
  scanf("%d%d", &L, &n);
  for (int i = 1, m; i <= n; i++) {
    scanf("%d%s", &m, s);
    acam::insert(s, i);
  }
  acam::build();
  f[0][0] = 1;
  auto ans = trans.pow(L) * f;
  int sum = 0;
  for (int i = 0; i < acam::sz; i++) sum = (sum + ans[i][0]) % mod;
  printf("%d\n", sum);
  return 0;
}