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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

int n, m, a[maxn];
int pre[maxn][23], suf[maxn][23];
vector<int> seq[23];

int qmin() {
  
  return 0;
}

int qsum() {
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int x = a[i];
    int r = qpow(2, m - x);
    if (x < 20) {
      r = sub(r, pre[i - 1][x]);
      int pos = (int)seq[18].size() - n + i + 1;
      r = sub(r, suf[pos][x]);
    }
    ans = add(ans, r);
  }
  int all = mul(n, sub(qpow(2, m), n));
  return sub(all, ans);
}

int main() {
  seq[1] = { 1 };
  for (int i = 2; i < 21; i++) {
    for (int x: seq[i - 1]) seq[i].push_back(x);
    seq[i].push_back(i);
    for (int x: seq[i - 1]) seq[i].push_back(x);
  }
  for (int i = 0; i < (int)seq[18].size(); i++) {
    for (int j = 0; j < 20; j++) {
      pre[i + 1][j] = pre[i][j];
    }
    pre[i + 1][seq[18][i]]++;
  }
  for (int i = (int)seq[18].size() - 1; i >= 0; i--) {
    for (int j = 0; j < 20; j++) {
      suf[i + 1][j] = suf[i + 2][j];
    }
    suf[i + 1][seq[18][i]]++;
  }

  while (scanf("%d%d", &n, &m) == 2) {
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    printf("%d %d\n", qmin(), qsum());
  }
  return 0;
}