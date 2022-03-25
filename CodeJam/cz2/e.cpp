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
const int maxn = 500000 + 5;

int n, L, a[maxn];
vector<int> bag[maxn];

int query(int c, int l, int r) {
  return upper_bound(begin(bag[c]), end(bag[c]), r) - lower_bound(begin(bag[c]), end(bag[c]), l);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &L);
    for (int i = 1; i <= n; i++) {
      bag[i].clear();
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      bag[a[i]].push_back(i);
    }
    if (L == 1) {
      L++;
    }
    ll ans = 0; int last = 1;
    for (int i = 1; i <= n; i++) {
      if (a[i] == a[i - 1]) {
        last = i;
      } else {
        if (i - L + 1 >= last) {
          ans += i - L + 1 - last + 1 - query(a[i], last, i - L + 1);
        }
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}