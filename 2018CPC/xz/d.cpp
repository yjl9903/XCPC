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
  #define dbg(args...) cout << "" << #args << " -> ", err(args)
  void err() { std::cout << "" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 200 + 5;

inline int add(int x, int y) {
  x += y; return x >= mod ? x - mod : x;
}
inline int sub(int x, int y) {
  x -= y; return x < 0 ? x + mod : x;
}

int n, a[maxn];
char mp[maxn][maxn];
int f[maxn][maxn][maxn], g[maxn][maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) scanf("%s", mp[i] + 1);
    ms(f, 0); int ans = 0;
    for (int i = 1; i <= n; i++) {
      ms(g, 0);
      for (int j = 1; j <= n; j++) {
        if (mp[a[j]][a[i]] == '1') {
          for (int k = 1; k <= n; k++) {
            g[j][k] = f[i - 1][j][k];
          }
        }
      }
      for (int j = 1; j <= n; j++) {
        for (int k = 1; k <= n; k++) {
          g[j][k] = add(g[j][k], g[j - 1][k]);
          g[j][k] = add(g[j][k], g[j][k - 1]);
          g[j][k] = sub(g[j][k], g[j - 1][k - 1]);
        }
      }
      for (int j = 1; j <= n; j++) {
        for (int k = 1; k <= n; k++) {
          f[i][j][k] = f[i - 1][j][k];
          if (a[i] == a[j] && a[j] == a[k]) {
            int sum = add(g[j - 1][k - 1], 1);
            f[i][j][k] = add(f[i][j][k], sum);
            ans = add(ans, sum);
          }
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}