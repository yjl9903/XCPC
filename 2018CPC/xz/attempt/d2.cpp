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

int n, a[maxn], g[maxn][maxn];
char s[maxn];
int f[maxn][maxn][maxn][3];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%s", s + 1);
      for (int j = 1; j <= n; j++) {
        g[i][j] = s[j] - '0';
      }
    }
    ms(f, 0);
    auto trans = [&](int x, int y, int z, int t) {
      if (t == 0) {
        for (int i = 1; i < z; i++) {
          if (!g[a[i]][a[z]]) continue;
          f[x][y][z][t] = add(f[x][y][z][t], f[x][y][i][2]);
        }
      } else if (t == 1) {
        for (int i = 1; i < x; i++) {
          f[x][y][z][t] = add(f[x][y][z][t], f[i][y][z][0]);
        }
      } else if (t == 2) {
        for (int i = 1; i < y; i++) {
          f[x][y][z][t] = add(f[x][y][z][t], f[x][i][z][1]);
        }
      }
    };
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        for (int k = 1; k <= n; k++) {
          trans(i, j, k, 2);
          trans(i, j, k, 1);
          if (a[i] == a[j] && a[j] == a[k]) {
            trans(i, j, k, 0);
            f[i][j][k][0] = add(f[i][j][k][0], 1);
            ans = add(ans, f[i][j][k][0]);
          }
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}