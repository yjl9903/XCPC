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

int n, a[maxn], ans[maxn], last[maxn];

struct Bit {
  int a[maxn];
  void clear() {
    for (int i = 0; i <= n; i++) a[i] = 0;
  }
  void update(int i, int x) {
    for (; i <= n; i += i & -i) a[i] += x;
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
  int query(int L, int R) {
    return query(R) - query(L - 1);
  }
} f;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    f.clear();
    for (int i = 1; i <= n; i++) {
      last[i] = -1;
      ans[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      ans[1]++;
      if (last[a[i]] == -1) {
        last[a[i]] = i;
        f.update(i, 1);
      } else {
        int k = f.query(last[a[i]], i);
        ans[k]--;
        f.update(last[a[i]], -1);
        f.update(i, 1);
        last[a[i]] = i;
      }
    }
    for (int i = 1; i <= n; i++) {
      ans[i] += ans[i - 1];
      printf("%d%c", ans[i], " \n"[i == n]);
    }
  }
  return 0;
}