#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int max_n = 100005;
 
int n, k;
int a[max_n], d[max_n];
ll sum[max_n];
ll suf[max_n];
ll pre[max_n];
 
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) scanf("%d", a + i);
  for (int i = 1; i <= n; i++) scanf("%d", d + i);
  for (int i = n; i >= 1; i--) sum[i] = sum[i + 1] + a[i];
  ll ans = 0;
  if (k == 0) {
    for (int i = 1; i <= n; i++) ans = max(ans, sum[i] - d[i]);
  } else if (k >= 2) {
    for (int i = 1; i < n; i++) ans = max(ans, sum[1] - d[i]);
    ans = max(ans, 1ll * a[n] - d[n]);
  } else {
    suf[n] = sum[n] - d[n];
    for (int i = n - 1; i >= 1; i--) suf[i] = max(suf[i + 1], sum[i] - d[i]);
    int mx = d[1];
    for (int i = 2; i < n; i++) {
      mx = min(mx, d[i]);
      ans = max(ans, max(sum[1] - sum[i + 1] - mx, 0ll) + max(suf[i + 1], 0ll));
    }
 
    for (int i = 1; i <= n; i++) pre[i] = max(pre[i - 1], sum[i] - d[i]);
    for (int i = 1; i + 2 <= n; i++) {
      ll res = 0;
      if (a[i + 1] - d[i + 1] > 0) res += a[i + 1] - d[i + 1];
      res += max(pre[i] - a[i + 1], 0ll);
      ans = max(ans, res);
 
      ans = max(ans, suf[i + 1]);
    }
  }
  printf("%lld\n", ans);
  return 0;
}