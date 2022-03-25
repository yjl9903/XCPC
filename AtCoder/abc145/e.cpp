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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, t, a[maxn], b[maxn], dp[maxn], p[maxn];

int main() {
  scanf("%d%d", &n, &t);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", a + i, b + i);
    p[i] = i;
  }
  sort(p + 1, p + 1 + n, [&](int x, int y) {
    return a[x] < a[y];
  });
  for (int id = 1; id <= n; id++) {
    int i = p[id];
    for (int j = t - 1; j >= 0; j--) {
      dp[j + a[i]] = max(dp[j + a[i]], dp[j] + b[i]);
    }
  }
  int ans = 0;
  for (int i = 0; i <= 7000; i++) ans = max(ans, dp[i]);
  cout << ans;
  return 0;
}