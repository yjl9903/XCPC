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

int n, a[maxn], nxt[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    set<int> ok, rest;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      ok.insert(i);
      rest.insert(i);
    }
    vector<int> ans;
    int last = 0;
    while (!ok.empty() && !rest.empty()) {
      auto it = ok.lower_bound(last);
      if (it == ok.end()) {
        it = ok.begin();
      }
      if (!rest.count(*it)) {
        ok.erase(it);
        continue;
      }
      int x = *it;
      it = rest.upper_bound(*it);
      if (it == rest.end()) {
        it = rest.begin();
      }
      int y = *it;
      if (__gcd(a[x], a[y]) == 1) {
        ans.push_back(y);
        rest.erase(y);
        last = y + 1;
      } else {
        ok.erase(x);
      }
    }
    printf("%d", ans.size());
    for (int x: ans) printf(" %d", x);
    puts("");
  }
  return 0;
}