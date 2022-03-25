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
const int maxn = 100000 + 5;

int n, m, a[maxn], dp[20][maxn];

int qmax(int l, int r) {
  assert(l <= r);
  int k = __lg(r - l + 1);
  int x = dp[k][l];
  int y = dp[k][r - (1 << k) + 1];
  if (a[x] >= a[y]) return x;
  else return y;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    dp[0][i] = i;
  }
  for (int j = 1; j < 20; j++) {
    for (int i = 1; i + (1 << j) <= n + 1; i++) {
      int l = dp[j - 1][i];
      int r = dp[j - 1][i + (1 << (j - 1))];
      if (a[l] >= a[r]) dp[j][i] = l;
      else dp[j][i] = r;
    }
  }
  int tot = 1;
  for (int i = 1; i <= m; i++) {
    int pos = qmax(tot, n - m + i);
    if (i > 1) putchar(' ');
    printf("%d", a[pos]);
    tot = pos + 1;
  }
  return 0;
}