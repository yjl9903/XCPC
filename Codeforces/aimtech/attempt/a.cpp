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
  scanf("%d%d", &n, &m);
  swap(n, m);
  for (int i = 1; i <= n; i++) {
    mn[i] = inf;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%d", &a[i][j]);
      mx[j] = max(mx[j], a[i][j]);
      mn[i] = min(mn[i], a[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    int cnt = 0;
    for (int j = 1; j <= m; j++) {
      if (a[i][j] == mn[i]) {
        cnt++;
      }
    }
    okr[i] = cnt <= 1;
  }
  for (int j = 1; j <= m; j++) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i][j] == mx[j]) {
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
      if (a[i][j] == mn[i] && a[i][j] == mx[j]) {
        ans = min(ans, (PII){ j, i });
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