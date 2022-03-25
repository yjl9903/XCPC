#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;
const int L = 20;

int n, q, a[maxn], last[maxn];
int nxt[maxn], f[maxn][L];

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    auto push = [&](int x) {
      if (x) {
        nxt[x] = min(nxt[x], i);
      }
    };
    int x = a[i];
    for (int j = 2; 1ll * j * j <= x; j++) {
      if (x % j) continue;
      while (x % j == 0) x /= j;
      if (last[j]) {
        nxt[last[j]] = min(nxt[last[j]], i);
      }
      last[j] = i;
    }
    if (x > 1) {
      if (last[x]) {
        nxt[last[x]] = min(nxt[last[x]], i);
      }
      last[x] = i;
    }
    nxt[i] = n + 1;
  }
  nxt[n + 1] = n + 2;
  for (int j = 0; j < L; j++) {
    f[n + 1][j] = n + 2;
    f[n + 2][j] = n + 2;
  }
  for (int i = n; i >= 1; i--) {
    nxt[i] = min(nxt[i], nxt[i + 1]);
    f[i][0] = nxt[i];
    for (int j = 1; j < L; j++) {
      f[i][j] = f[f[i][j - 1]][j - 1];
    }
  }
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    int ans = 0;
    for (int j = L - 1; j >= 0 && l <= r; j--) {
      if (f[l][j] <= r + 1) {
        l = f[l][j];
        ans += 1 << j;
      }
    }
    printf("%d\n", ans + (l <= r));
  }
  return 0;
}