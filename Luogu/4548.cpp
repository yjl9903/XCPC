#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 10000;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, m, a[maxn], xs[maxn], fail[maxn];

int main() {
  int T; scanf("%d%d", &m, &T);
  xs[0] = 1;
  for (int i = 1; i < maxn; i++) xs[i] = m * xs[i - 1] % mod;
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    fail[1] = 0;
    for (int i = 2; i <= n; i++) {
      int cur = fail[i - 1];
      while (cur && a[cur + 1] != a[i]) cur = fail[cur];
      if (a[cur + 1] == a[i]) cur++;
      fail[i] = cur;
    }
    int ans = 0, cur = n;
    while (cur) {
      ans = (ans + xs[cur]) % mod;
      cur = fail[cur];
    }
    printf("%04d\n", ans);
  }
  return 0;
}