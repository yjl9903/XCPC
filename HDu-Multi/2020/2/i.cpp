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
const int maxn = 400 + 5;

int n, m, q, a[maxn][maxn], cnt[maxn * maxn];
char s[4000005];
bool tag[maxn][maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        scanf("%d", &a[i][j]);
      }
    }
    while (q--) {
      int sx, sy;
      scanf("%d%d%s", &sx, &sy, s + 1);
      int len = strlen(s + 1);
      int x1 = sx, x2 = sx, y1 = sy, y2 = sy;
      int x = sx, y = sy;
      for (int i = 1; i <= len; i++) {
        if (s[i] == 'U') {
          y++;
        } else if (s[i] == 'D') {
          y--;
        } else if (s[i] == 'L') {
          x--;
        } else if (s[i] == 'R') {
          x++;
        }
        x1 = min(x1, x);
        y1 = min(y1, y);
        x2 = max(x2, x);
        y2 = max(y2, y);
      }
      for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
          tag[i][j] = 0;
          cnt[a[i][j]] = 0;
        }
      }
      // dbg(x1, x2, y1, y2);
      x = sx; y = sy;
      for (int i = 1; i <= len; i++) {
        if (s[i] == 'U') {
          // dbg(x, y);
          tag[x][y++] ^= 1;
        } else if (s[i] == 'D') {
          // dbg(x, y - 1);
          tag[x][--y] ^= 1;
        } else if (s[i] == 'L') {
          x--;
        } else if (s[i] == 'R') {
          x++;
        }
      }
      int ans = 0;
      for (int j = y1; j <= y2; j++) {
        int tot = 0;
        for (int i = x1; i <= x2; i++) {
          tot ^= tag[i][j];
          if (tot) {
            cnt[a[i][j]]++;
            if (cnt[a[i][j]] == 1) {
              ans++;
            }
          }
        }
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}