#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 200000 + 5;

int n, id[maxn], a[maxn], ans[maxn];

ll b[maxn], dp[maxn];
void update(int i, ll x) {
  for (; i <= n; i += i & -i) b[i] = min(b[i], x);
}
ll query(int i) {
  ll r = inf;
  for (; i; i -= i & -i) r = min(r, b[i]);
  return r;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    id[i] = i; b[i] = inf;
  }
  sort(id + 1, id + 1 + n, [&](int x, int y) {
    return a[x] < a[y];
  });
  if (n == 3) {
    printf("%d 1\n1 1 1\n", a[id[3]] - a[id[1]]);
    return 0;
  }
  update(1, -a[id[1]]);
  for (int i = 3; i <= n; i++) {
    dp[i] = a[id[i]] + query(i - 2);
    if (i > 3) {
      update(i, dp[i - 1] - a[id[i]]);
    }
  }
  printf("%I64d", dp[n]);
  int cnt = 0, last = n; ll tot = dp[n] - a[id[n]];
  for (int i = n - 1; i >= 1; i--) {
    if (i == 2 || i == 3) continue;
    if (i == 1 || (dp[i - 1] - a[id[i]] == tot && last - i + 1 >= 3)) {
      cnt++;
      for (int j = i; j <= last; j++) ans[id[j]] = cnt;
      last = i - 1;
      tot = dp[last] - a[id[last]];
    }
  }
  printf(" %d\n", cnt);
  for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
  return 0;
}