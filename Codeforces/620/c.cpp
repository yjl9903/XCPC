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
const int maxn = 100000 + 5;

int n, m, t[maxn], l[maxn], r[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    ll ml = m, mr = m, last = 0;
    bool flag = true;
    for (int i = 1; i <= n; i++) {
      scanf("%d%d%d", t + i, l + i, r + i);
    }
    for (int i = 1; i <= n && flag; i++) {
      mr += t[i] - last;
      ml -= t[i] - last;
      if (ml <= l[i]) {
        if (mr >= l[i]) {
          ml = l[i]; mr = min(mr, 1ll * r[i]);
        } else {
          flag = false;
        }
      } else if (ml <= r[i]) {
        mr = min(mr, 1ll * r[i]);
      } else {
        flag = false;
      }
      last = t[i];
    }
    puts(flag ? "YES" : "NO");
  }
  return 0;
}