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

int n, q, a[maxn];
ll pre[maxn];

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i); pre[i] = pre[i - 1] + a[i];
  }
  ll sum = 0;
  while (q--) {
    ll k; scanf("%I64d", &k);
    sum += k;
    int pos = upper_bound(pre + 1, pre + n + 1, sum) - pre - 1;
    if (pos < n) {
      printf("%d\n", n - pos);
    } else {
      sum = 0;
      printf("%d\n", n);
    }
  }
  return 0;
}