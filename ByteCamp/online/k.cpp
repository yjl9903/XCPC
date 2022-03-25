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
const int maxn = 200000 + 5;

int n, k, a[maxn], b[maxn];

void update(int i, int x) {
  for (; i <= n; i += i & -i) b[i] += x;
}
int query(int i) {
  int r = 0;
  for (; i; i -= i & -i) r += b[i];
  return r;
}

ll pre[maxn], suf[maxn];

int main() {
  scanf("%d%d", &n, &k);
  vector<int> p;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    if (a[i] <= k) p.push_back(i);
  }

  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    pre[i] = pre[i - 1];
    if (a[i] <= k) {
      cnt++;
    } else {
      pre[i] += cnt;
    }
  }
  cnt = 0;
  ll ans = pre[n];
  for (int i = n; i >= 1; i--) {
    suf[i] = suf[i + 1];
    if (a[i] <= k) {
      cnt++;
    } else {
      suf[i] += cnt;
    }
    ans = min(ans, suf[i] + pre[i - 1]);
  }

  ll sum = 0;
  for (int i = k - 1; i >= 0; i--) {
    sum += query(a[p[i]]);
    update(a[p[i]], 1);
  }
  printf("%lld\n", sum + ans);
  return 0;
}