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
const int maxn = 500 + 5;

int n, a[maxn];

int f[maxn][maxn], g[maxn][maxn];
int cal(int l, int r) {
  if (g[l][r] != -1) return g[l][r];
  if (r == l) return a[l];
  for (int k = l; k < r; k++) {
    int x = cal(l, k);
    int y = cal(k + 1, r);
    if (x && y && x == y) {
      return g[l][r] = x + 1;
    }
  }
  return g[l][r] = 0;
}
int solve(int l, int r) {
  if (f[l][r] != -1) return f[l][r];
  if (cal(l, r)) return f[l][r] = 1;
  int ans = r - l + 1;
  for (int k = l; k < r; k++) {
    ans = min(ans, solve(l, k) + solve(k + 1, r));
  }
  return f[l][r] = ans;
}

int main() {
  scanf("%d", &n);
  ms(f, -1); ms(g, -1);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  cout << solve(1, n) << endl;
  return 0;
}