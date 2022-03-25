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

int n, a[maxn], b[maxn];

bool check(int x) {
  b[1] = a[1];
  for (int i = 2; i <= n; i++) {
    if (a[i] >= b[i - 1]) {
      b[i] = a[i]; continue;
    }
    int val = b[i - 1] - a[i];
    if (31 - __builtin_clz(val) < x) {
      b[i] = b[i - 1];
    } else {
      return false;
    }
  }
  return true;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    int ans = -1;
    for (int i = 0; i <= 35; i++) {
      if (check(i)) {
        ans = i; break;
      }
    }
    assert(ans != -1);
    printf("%d\n", ans);
  }
  return 0;
}