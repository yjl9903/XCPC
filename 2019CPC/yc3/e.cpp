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
typedef unsigned long long ull;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

struct fastIO {
  char s[100000]; int it,len;
  fastIO() { it = len = 0; }
  inline char get() {
    if (it < len) return s[it++];
    it = 0; len = fread(s, 1, 100000, stdin);
    if (len == 0) return EOF;
    else return s[it++];
  }
  bool notend() {
    char c = get();
    while(c == ' ' || c == '\n') c = get();
    if (it > 0) it--;
    return c != EOF;
  }
} buff;
inline int gi() {
  int r = 0; bool ng = 0;
  char c = buff.get();
  while (c != '-' && (c < '0' || c > '9')) c = buff.get();
  if (c == '-') ng = 1, c = buff.get();
  while (c >= '0' && c <= '9') r = r * 10 + c - '0', c = buff.get();
  return ng ? -r : r;
}

int n, k, a[maxn], mxd[maxn], son[maxn];
ull ans[maxn];

struct Edge {
  int to, nxt;
} e[maxn * 2];
int ecnt, head[maxn];
void adde(int u, int v) {
  e[++ecnt] = { v, head[u] };
  head[u] = ecnt;
}

void predfs(int u) {
  son[u] = mxd[u] = 0;
  for (int j = head[u]; j; j = e[j].nxt) {
    int v = e[j].to;
    predfs(v);
    if (mxd[v] > mxd[u]) {
      son[u] = v; mxd[u] = mxd[v];
    }
  }
  mxd[u]++;
}

struct Node {
  int a[4];
  void clear() {
    a[0] = a[1] = a[2] = a[3] = 0;
  }
  Node() {
    clear();
  }
  
  int& operator [] (int x) { return a[x]; }
  const int& operator [] (int x) const { return a[x]; }

  Node operator+(const Node& b) {
    Node r;
    r[0] = a[0] + b.a[0];
    r[1] = a[1] + b.a[1];
    r[2] = a[2] + b.a[2];
    r[3] = a[3] + b.a[3];
    return r;
  }
  Node operator-(const Node& b) {
    Node r;
    r[0] = a[0] - b.a[0];
    r[1] = a[1] - b.a[1];
    r[2] = a[2] - b.a[2];
    r[3] = a[3] - b.a[3];
    return r;
  }
} * tot, * f[maxn], dp[maxn];

void make(int u) {
  f[u] = tot; tot += mxd[u];
}

int b1, b2;
int parse(int x) {
  int a = (x >> b1) & 1;
  int b = (x >> b2) & 1;
  return a << 1 | b;
}

ull xs;
void dfs(int u) {
  if (son[u]) {
    int v = son[u];
    f[v] = f[u] + 1;
    dfs(v);
  }

  f[u][0][parse(a[u])]++;
  f[u][0] = f[u][0] + f[u][1];

  for (int j = head[u]; j; j = e[j].nxt) {
    int v = e[j].to;
    if (v == son[u]) continue;
    make(v); dfs(v);
    f[u][0] = f[u][0] + f[v][0];
    for (int i = 0; i < mxd[v]; i++) {
      f[u][i + 1] = f[u][i + 1] + f[v][i];
    }
  }

  auto sum = f[u][0];
  if (k + 1 < mxd[u]) sum = sum - f[u][k + 1];

  ans[u] += xs * sum[0] * sum[3];
  ans[u] += xs * sum[1] * sum[2];
}

void solve(int b1, int b2) {
  ::b1 = b1; ::b2 = b2;
  xs = (1 + (b1 != b2)) * (1ll << (b1 + b2));
  tot = dp;
  for (int i = 0; i <= n; i++) dp[i].clear();
  make(1); dfs(1);
}

int main() {
  n = gi(); k = gi();
  for (int i = 1; i <= n; i++) a[i] = gi();
  for (int i = 2, fa; i <= n; i++) {
    fa = gi(); adde(fa, i);
  }
  predfs(1);
  for (int i = 0; i <= 29; i++) {
    for (int j = 0; j <= i; j++) {
      solve(i, j);
    }
  }
  for (int i = 1; i <= n; i++) printf("%llu\n", ans[i]);
  return 0;
}