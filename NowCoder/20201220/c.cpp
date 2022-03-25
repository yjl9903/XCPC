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
const int maxn = 2000 + 5;

int n, k, a[maxn][maxn];
ll pre[maxn][maxn];

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      scanf("%d", &a[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      pre[i][j] = pre[i][j - 1] + a[i][j];
    }
  }
  ll ans = 0;
  for (int i = k; i + k - 1 <= n; i++) {
    for (int j = k; j + k - 1 <= n; j++) {
      ll cur = pre[i][j + k - 1] - pre[i][j - k];
      for (int p = 1; p < k; p++) {
        cur += pre[i - p][j + k - 1 - p] - pre[i - p][j - k + p];
        cur += pre[i + p][j + k - 1 - p] - pre[i + p][j - k + p];
      }
      ans = max(ans, cur);
    }
  }
  cout << ans << endl;
  return 0;
}