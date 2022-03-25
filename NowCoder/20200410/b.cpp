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

int n, m;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    if (n > m) swap(n, m);
    int ans = 0;
    while (n + n < m) n += n, ans++;
    if (n == m) {
      ans += n;
    } else if (n + n >= m) {
      int x = n + n - m;
      n -= x; m -= x;
      ans += x + 1 + m;
    }
    printf("%d\n", ans);
  }
  return 0;
}