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

int n, m, pre[maxn], cnt[maxn], siz[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      pre[i] = i;
      siz[i] = 1;
      cnt[i] = 0;
    }
    for (int i = 1; i <= m; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      x = find(x);
      y = find(y);
      if (x == y) {
        cnt[x]++;
      } else {
        if (siz[x] > siz[y]) swap(x, y);
        pre[x] = y;
        siz[y] += siz[x];
        cnt[y] += cnt[x];
        cnt[y]++;
      }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      if (i == find(i)) {
        if (siz[i] > 1) {
          if (cnt[i] == siz[i]) {
            ans += cnt[i] + 1;
          } else if (cnt[i] + 1 == siz[i]) {
            ans += cnt[i];
          }
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}