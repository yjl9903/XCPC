#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
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
const int maxn = 1000000 + 5;

int add(int x, int y) {
  x += y;
  return x >= mod ? x - mod : x;
}

int n, a[maxn];
int f[maxn], nxt[maxn][4];
char s[maxn];

int main() {
  scanf("%d%s", &n, s + 1);
  bool same = true;
  for (int i = 1; i <= n; i++) {
    a[i] = a[i - 1] ^ (s[i] - 'A' + 1);
    same &= (a[i] ^ a[i - 1]) == a[1];
  }
  if (same) {
    puts("1");
    return 0;
  }
  for (int j = 0; j < 4; j++) {
    nxt[n][j] = n + 1;
  }
  for (int i = n - 1; i >= 0; i--) {
    memcpy(nxt[i], nxt[i + 1], sizeof nxt[i]);
    nxt[i][a[i + 1]] = i + 1;
  }
  f[0] = 1;
  int ans = 0;
  for (int i = 0; i <= n; i++) {
    if (i > 0 && a[i] == a[n]) {
      ans = add(ans, f[i]);
    }
    for (int j = 0; j < 4; j++) {
      if (j == a[i]) continue;
      int x = nxt[i][j];
      if (x > n) continue;
      f[x] = add(f[x], f[i]);
    }
  }
  cout << ans << endl;
  return 0;
}