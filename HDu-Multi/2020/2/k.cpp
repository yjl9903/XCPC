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
const int maxn = 300000 + 5;

int n;
PII a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &a[i].first, &a[i].second);
    }
    sort(a + 1, a + 1 + n);

    set<int> st;
    int j = 1;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
      while (j <= n && a[j].first <= ans) {
        st.insert(a[j].second);
        j++;
      }
      if (st.empty()) {
        assert(ans < a[j].first);
        ans = 1ll * a[j].first + a[j].second;
        j++;
      } else {
        ans += *st.begin();
        st.erase(st.begin());
      }
      printf("%lld%c", ans, " \n"[i == n]);
    }
  }
  return 0;
}