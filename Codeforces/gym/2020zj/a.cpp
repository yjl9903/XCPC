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

int n, m, val[maxn];
vector<PII> evs[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int l, r;
    scanf("%d%d%d", &l, &r, val + i);
    evs[l].push_back({ i, 1 });
    evs[r + 1].push_back({ i, -1 });
  }
  ll ans = 0;
  set<PII> st;
  for (int i = 1; i <= n; i++) {
    for (auto x: evs[i]) {
      if (x.second == 1) {
        st.insert({ val[x.first], x.first });
      } else {
        st.erase({ val[x.first], x.first });
      }
    }
    if (st.empty()) {
      puts("-1");
      return 0;
    }
    auto it = st.begin();
    ans += it->first;
    st.erase(it);
  }
  printf("%lld\n", ans);
  return 0;
}