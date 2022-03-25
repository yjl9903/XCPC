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

int n, x, m, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &x, &m);
    int L = x, R = x;
    for (int i = 1; i <= m; i++) {
      int l, r; scanf("%d%d", &l, &r);
      if (max(L, l) <= min(R, r)) {
        L = min(L, l);
        R = max(R, r);
      }
    }
    printf("%d\n", R - L + 1);
  }
  return 0;
}