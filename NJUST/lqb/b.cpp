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

int n, a[maxn], pre[maxn], suf[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  pre[1] = a[1]; suf[n] = a[n];
  for (int i = 2; i <= n; i++) {
    pre[i] = min(pre[i - 1], a[i]);
  }
  for (int i = n - 1; i >= 1; i--) {
    suf[i] = max(suf[i + 1], a[i]);
  }
  int ans = 0;
  for (int i = 2; i < n; i++) {
    if (a[i] > pre[i - 1] && a[i] < suf[i + 1]) {
      ans++;
    }
  }
  printf("%d\n", ans);
  return 0;
}