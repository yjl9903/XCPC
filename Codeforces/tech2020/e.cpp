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

int n, m, a[maxn];

int main() {
  scanf("%d%d", &n, &m);
  int tot = 0, p = 1;
  for (p = 1; p <= n; p++) {
    if (tot + (p - 1) / 2 > m) {
      break;
    }
    tot += (p - 1) / 2;
    a[p] = p;
  }
  if (p > n && tot < m) {
    puts("-1"); return 0;
  }
  if (tot < m) {
    int len = (m - tot);
    a[p] = a[p - len] + a[p - len - 1];
    p++;
  }
  for (int i = p; i <= n; i++) {
    a[i] = a[i - 1] + 10000;
  }
  for (int i = 1; i <= n; i++) printf("%d ", a[i]);
  return 0;
}