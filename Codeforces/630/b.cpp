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
const int maxn = 1000 + 5;

int n, a[maxn], ans[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      ans[i] = 0;
    }
    int tot = 1;
    for (int d = 2; d <= 1000; d++) {
      int cnt = 0;
      for (int i = 1; i <= n; i++) {
        if (ans[i] == 0 && a[i] % d == 0) {
          ans[i] = tot;
          cnt++;
        }
      }
      if (cnt) tot++;
    }
    printf("%d\n", tot - 1);
    for (int i = 1; i <= n; i++) {
      printf("%d%c", ans[i], i == n ? '\n' : ' ');
    }
  }
  return 0;
}