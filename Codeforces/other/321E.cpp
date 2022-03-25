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
const int maxn = 4000 + 5;

struct fastIO {
  static const int SIZE = 1 << 20;
  char s[SIZE]; int it, len;
  fastIO() { it = len = 0; }
  inline char get() {
    if (it < len) return s[it++];
    it = 0; len = fread(s, 1, SIZE, stdin);
    if (len == 0) return EOF;
    else return s[it++];
  }
  inline bool notend() {
    char c = get();
    while (c == ' ' || c == '\n') c = get();
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

int n, k, a[maxn][maxn];
int f[maxn], g[maxn];

int cal(int y, int x) {
  return a[x][x] - a[x][y - 1] - a[y - 1][x] + a[y - 1][y - 1];
}

void dfs(int l, int r, int L, int R) {
  if (l > r) return ;
  int m = (l + r) / 2;
  int pos = L, val = f[pos] + cal(pos + 1, m);
  for (int i = L + 1; i <= R && i < m; i++) {
    int cur = f[i] + cal(i + 1, m);
    if (cur < val) {
      val = cur;
      pos = i;
    }
  }
  g[m] = val;
  dfs(l, m - 1, L, pos);
  dfs(m + 1, r, pos, R);
}

int main() {
  n = gi();
  k = gi();
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      a[i][j] = gi();
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      a[i][j] += a[i - 1][j];
      a[i][j] += a[i][j - 1];
      a[i][j] -= a[i - 1][j - 1];
    }
  }
  for (int i = 1; i <= n; i++) {
    f[i] = cal(1, i);
  }
  for (int i = 2; i <= k; i++) {
    dfs(1, n, 1, n);
    swap(f, g);
  }
  printf("%d\n", f[n] / 2);
  return 0;
}