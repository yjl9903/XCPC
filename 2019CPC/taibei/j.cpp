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
#include <bitset>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500 + 5;

int n, m;
bitset<501> a[maxn], tmp;
char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
      scanf("%s", s);
      for (int j = 0; j < n; j++) {
        a[i].set(j, s[j] - '0');
      }
    }
    int ans = m + 1;
    for (int s = 1; s < (1 << m); s++) {
      tmp.reset();
      for (int i = 0; i < m; i++) {
        if (s >> i & 1) {
          tmp |= a[i];
        }
      }
      int cnt = 0;
      for (int i = 0; i < n; i++) {
        cnt += tmp[i];
      }
      if (cnt == n) {
        ans = min(ans, __builtin_popcount(s));
      }
    }
    if (ans == m + 1) ans = -1;
    printf("%d\n", ans);
  }
  return 0;
}