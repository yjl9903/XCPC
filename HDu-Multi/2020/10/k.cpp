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

int n, m, k, a[maxn], ord[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      ord[i] = i;
    }
    if (k > 0) {
      sort(ord + 1, ord + 1 + n, [&](int lhs, int rhs) {
        if (a[lhs] != a[rhs]) return a[lhs] > a[rhs];
        return lhs < rhs;
      });
    }
    for (int i = 1; i <= n; i++) {
      printf("%d%c", ord[i], " \n"[i == n]);
    }
  }
  return 0;
}