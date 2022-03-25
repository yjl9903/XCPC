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
const int maxn = 300000 + 5;

int n, m, a[maxn][2];
ll pre[maxn][2], dp[maxn];

struct Seg {
  int tp, l, r, val;
} b[maxn];
vector<int> bag[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i][0]);
    pre[i][0] = a[i][0] + pre[i][0];
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i][1]);
    pre[i][1] = a[i][1] + pre[i][1];
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d%d", &b[i].tp, &b[i].l, &b[i].r, &b[i].val);
    b[i].tp--;
    bag[b[i].r].push_back(i);
  }

  for (int i = 1; i <= n; i++) {
    dp[i] = dp[i - 1] + max(a[i][0], a[i][1]);
    for (auto id: bag[i]) {
      int tp = b[id].tp, l = b[id].l;
      ll add = pre[i][tp] - pre[l - 1][tp] + b[id].val;
      dp[i] = max(dp[i], dp[l - 1] + add);
    }
  }

  printf("%lld\n", dp[n]);
  return 0;
}