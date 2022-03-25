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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, m, a[maxn], b[maxn], pos[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i); pos[a[i]] = i;
    }
    for (int i = 1; i <= m; i++) {
      scanf("%d", b + i);
    }
    ll ans = 0;
    int ri = 0;
    for (int i = 1; i <= m; i++) {
      if (pos[b[i]] > ri) {
        ri = pos[b[i]];
        ans += 2 * (pos[b[i]] - i + 1) - 1;
      } else {
        ans++;
      }
    }
    printf("%I64d\n", ans);
  }
  return 0;
}