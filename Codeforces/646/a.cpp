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

int n, x, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &x);
    int cnt[2] = { 0, 0 };
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      cnt[a[i] % 2]++;
    }
    if (cnt[1] == 0) {
      puts("No");
    } else {
      if (cnt[1] % 2 == 0) cnt[1]--;
      // puts(cnt[1] + cnt[0] >= x ? "Yes" : "No");
      if (x % 2 == 0) {
        x -= min(x - 1, cnt[1]);
        puts(x <= cnt[0] ? "Yes" : "No");
      } else {
        x -= min(x, cnt[1]);
        puts(x <= cnt[0] ? "Yes" : "No");
      }
    }
  }
  return 0;
}