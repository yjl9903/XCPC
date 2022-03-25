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
const int maxn = 200000 + 5;

int n, k, cnt[maxn];
char s[maxn];

int main() {
  scanf("%d%d%s", &n, &k, s + 1);
  for (int i = 1; i <= n; i++) {
    cnt[i] = cnt[i - 1] + (s[i] == '1');
  }
  int ans = 1;
  for (int i = 1; i <= n; i++) {
    int l = i, r = n, tot = -1;
    auto check = [&](int x) {
      int c1 = cnt[x] - cnt[i - 1];
      int c0 = x - i + 1 - c1;
      return min(c0, c1) <= k;
    };
    while (l <= r) {
      int m = (l + r) / 2;
      if (check(m)) {
        tot = m; l = m + 1;
      } else {
        r = m - 1;
      }
    }
    if (tot != -1) {
      ans = max(ans, tot - i + 1);
    }
  }
  printf("%d\n", ans);
  return 0;
}