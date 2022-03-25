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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const int maxn = 200 + 5;

int n, m, k, a[maxn][maxn];
int sumR[maxn][maxn][maxn], sumC[maxn][maxn][maxn], mxR[maxn][maxn][maxn], mxC[maxn][maxn][maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        scanf("%d", &a[i][j]);
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        mxR[i][j][j] = a[i][j];
        sumR[i][j][j] = a[i][j];
        for (int k = j + 1; k <= m; k++) {
          mxR[i][j][k] = max(a[i][k], mxR[i][j][k - 1]);
          sumR[i][j][k] = a[i][k] + sumR[i][j][k - 1];
        }
      }
    }
    for (int j = 1; j <= m; j++) {
      for (int i = 1; i <= n; i++) {
        mxC[j][i][i] = a[i][j];
        sumC[j][i][i] = a[i][j];
        for (int k = i + 1; k <= n; k++) {
          mxC[j][i][k] = max(a[k][j], mxC[j][i][k - 1]);
          sumC[j][i][k] = a[k][j] + sumC[j][i][k - 1];
        }
      }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        for (int len = 1; i + len - 1 <= n && j + len - 1 <= m; len += 2) {
          int H = (len + 1) / 2;
          ll sum = H - a[i + H - 1][j + H - 1]; bool flag = true;
          if (sum < 0) continue;
          for (int p = 1; p < H; p++) {
            int mx = mxR[i + p - 1][j + p - 1][j + len - p - 1];
            mx = max(mx, mxC[j + len - p][i + p - 1][i + len - p - 1]);
            mx = max(mx, mxR[i + len - p][j + p][j + len - p]);
            mx = max(mx, mxC[j + p - 1][i + p][i + len - p]);
            if (mx > p) {
              flag = false; break;
            }
            sum += 4ll * (len - 2 * p + 1) * p;
            sum -= sumR[i + p - 1][j + p - 1][j + len - p - 1];
            sum -= sumC[j + len - p][i + p - 1][i + len - p - 1];
            sum -= sumR[i + len - p][j + p][j + len - p];
            sum -= sumC[j + p - 1][i + p][i + len - p];
            if (sum > k) {
              flag = false; break;
            }
          }
          if (flag) {
            ans = max(ans, H);
          }
          // dbg(i, j, H, sum);
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}