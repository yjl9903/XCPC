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
const int maxn = 2000 + 5;

char s[maxn], t[maxn];
int slen, tlen;
int f[maxn][maxn], g[maxn][maxn];
int pref[maxn][maxn], preg[maxn][maxn];

int max(int x, int y, int z) {
  return max(max(x, y), z);
}

int main() {
  while (scanf("%s%s", s + 1, t + 1) == 2) {
    slen = strlen(s + 1);
    tlen = strlen(t + 1);
    for (int i = 0; i <= slen; i++) {
      for (int j = 0; j <= tlen; j++) {
        f[i][j] = -inf;
        g[i][j] = -inf;
        pref[i][j] = -inf;
        preg[i][j] = -inf;
      }
    }
    int ans = tlen;
    f[0][0] = 0;
    for (int i = 0; i <= slen; i++) {
      pref[i][0] = 0;
    }
    for (int j = 0; j <= tlen; j++) {
      pref[0][j] = 0;
    }
    for (int i = 1; i <= slen; i++) {
      for (int j = 1; j <= tlen; j++) {
        g[i][j] = max(preg[i - 1][j - 1] + 2, preg[i][j - 1] + 1, preg[i - 1][j] + 1);
        if (s[i] <= t[j]) {
          f[i][j] = pref[i - 1][j - 1] + 2;
          ans = max(ans, f[i][j] + tlen - j);
          if (s[i] < t[j]) {
            g[i][j] = max(g[i][j], f[i][j]);
          }
        }

        pref[i][j] = max(f[i][j], pref[i - 1][j], pref[i][j - 1]);
        preg[i][j] = max(g[i][j], preg[i - 1][j], preg[i][j - 1]);
        ans = max(ans, f[i][j]);
        ans = max(ans, g[i][j]);

        // dbg(i, j, f[i][j], g[i][j]);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}