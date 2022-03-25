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
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100 + 5;

int n, m, a[maxn][maxn], f[maxn][maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    char buf[16];
    scanf("%s", buf + 1);
    for (int j = 1; j <= m; j++) {
      f[i][j] = a[i][j] = buf[j] == '*' ? 1 : 0;
    }
  }
  for (int i = n; i >= 1; i--) {
    for (int j = m; j >= 1; j--) {
      if (i >= 1) {
        f[i - 1][j] = max(f[i - 1][j], a[i - 1][j] + f[i][j]);
      }
      if (j >= 1) {
        f[i][j - 1] = max(f[i][j - 1], a[i][j - 1] + f[i][j]);
      }
    }
  }
  if (n == 1 || m == 1) {
    printf("%d\n", f[1][1]);
  } else {
    printf("%d\n", min(f[1][2], f[2][1]) + a[1][1]);
  }
  return 0;
}