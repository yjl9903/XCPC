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

int n, a[maxn], f[maxn], g[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  int ans = 1;
  f[1] = g[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (a[i] > a[i - 1]) {
      f[i] = f[i - 1];
      g[i] = max(f[i - 1], g[i - 1]);
    }
    if (a[i] > a[i - 2]) {
      g[i] = max(g[i], f[i - 2]);
    }
    f[i]++; g[i]++;
    ans = max(ans, f[i]);
    ans = max(ans, g[i]);
  }
  printf("%d\n", ans);
  return 0;
}