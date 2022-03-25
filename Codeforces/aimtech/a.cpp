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
const int maxn = 1000 + 5;

int n, m, a[maxn][maxn], mx[maxn], mn[maxn];
bool okr[maxn], okc[maxn];

int main() {
  scanf("%d%d", &m, &n);
  for (int i = 1; i <= m; i++) {
    mn[i] = inf;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%d", &a[i][j]);
      mx[i] = max(mx[i], a[i][j]);
      mn[j] = min(mn[j], a[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    int cnt = 0;
    for (int j = 1; j <= m; j++) {
      if (a[i][j] == mx[i]) {
        cnt++;
      }
    }
    okr[i] = cnt <= 1;
  }
  for (int j = 1; j <= m; j++) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i][j] == mn[j]) {
        cnt++;
      }
    }
    okc[j] = cnt <= 1;
  }
  PII ans(inf, inf);
  for (int i = 1; i <= n; i++) {
    if (!okr[i]) continue;
    for (int j = 1; j <= m; j++) {
      if (!okc[j]) continue;
      if (a[i][j] == mx[i] && a[i][j] == mn[j]) {
        ans = min(ans, (PII){ i, j });
      }
    }
  }
  if (ans == (PII){inf, inf}) {
    puts("0 0");
  } else {
    printf("%d %d\n", ans.first, ans.second);
  }
  return 0;
}