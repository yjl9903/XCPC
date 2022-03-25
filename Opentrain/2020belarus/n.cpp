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
const int maxn = 1000000 + 5;

int n, a[maxn], dp[21][maxn], ok[maxn];
int qmax(int l, int r) {
  int k = __lg(r - l + 1);
  int x = dp[k][l], y = dp[k][r - (1 << k) + 1];
  if (a[x] >= a[y]) return x;
  else return y;
}

void dfs(int val, int l, int r) {
  if (l > r) return ;
  int pos = qmax(l, r);
  int mx = a[pos];
  if (mx + r - l < val) return ;
  ok[pos] = true;
  {
    int mx = a[pos];
    if (val != -1) {
      mx = max(mx, val - r + pos - 1);
    }
    dfs(mx, l, pos - 1);
  }
  {
    int mx = a[pos];
    if (val != -1) {
      mx = max(mx, val - pos + l - 1);
    }
    dfs(mx, pos + 1, r);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    dp[0][i] = i;
  }
  for (int j = 1; j < 21; j++) {
    for (int i = 1; i + (1 << j) <= n + 1; i++) {
      int l = dp[j - 1][i];
      int r = dp[j - 1][i + (1 << (j - 1))];
      if (a[l] >= a[r]) dp[j][i] = l;
      else dp[j][i] = r;
    }
  }
  dfs(-1, 1, n);
  int cnt = 0;
  for (int i = 1; i <= n; i++) if (ok[i]) cnt++;
  printf("%d\n", cnt);
  for (int i = 1; i <= n; i++) if (ok[i]) printf("%d ", i);
  return 0;
}