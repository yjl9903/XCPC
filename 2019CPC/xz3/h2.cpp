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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, q, a[maxn], dp[maxn][11];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) a[i] = 0;
    int op;
    while (q--) {
      scanf("%d", &op);
      if (op == 1) {
        int pos, x; scanf("%d%d", &pos, &x);
        a[pos] += x;
      } else if (op == 2) {
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        ms(dp[l - 1], 0); dp[l - 1][0] = 1;
        for (int i = l; i <= r; i++) {
          for (int j = 1; j <= k; j++) {
            dp[i][j] = (dp[i - 1][j] + 1ll * dp[i - 1][j - 1] * a[i] % mod) % mod;
          }
        }
        printf("%d\n", dp[r][k]);
      }
    }
  }
  return 0;
}