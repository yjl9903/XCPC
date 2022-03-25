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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, m, d, c[maxn], suf[maxn], ans[maxn];

int main() {
  scanf("%d%d%d", &n, &m, &d);
  for (int i = 1; i <= m; i++) scanf("%d", c + i);
  for (int i = m; i >= 0; i--) suf[i] = suf[i + 1] + c[i];

  int tot = 0;
  for (int i = 1; i <= m; i++) {
    int flag = 0;
    for (int j = tot + d; j >= tot + 1; j--) {
      int r = j + c[i] - 1;
      if (r > n) continue;
      if (suf[i + 1] > n - r) continue;
      flag = 1;
      for (int k = j; k <= r; k++) ans[k] = i;
      tot = r;
      break;
    }
    if (!flag) return puts("NO"), 0;
  }
  if (tot + d <= n) return puts("NO"), 0;
  puts("YES");
  for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
  return 0;
}