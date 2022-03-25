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
#ifdef XLor
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, k;
vector<PII> edge[maxn];

ll ans, dp[maxn][2], sum[maxn];
void dfs(int u, int f) {
  dp[u][0] = dp[u][1] = sum[u] = 0;

  vector<ll> vec0;
  multiset<ll> st0;
  vector<pair<ll,ll> > vec1;
  for (auto& x: edge[u]) {
    int v = x.first;
    if (v == f) continue;
    dfs(v, u);
    sum[u] += x.second + dp[v][0];
    vec0.push_back(x.second + dp[v][0]);
    vec1.emplace_back(x.second + dp[v][1], x.second + dp[v][0]);
  }

  sort(begin(vec0), end(vec0), greater<ll>());
  dp[u][1] = sum[u];
  ll nxt = 0;
  for (int i = 0; i < k && i < vec0.size(); i++) {
    if (i < k - 1) {
      dp[u][0] += vec0[i];
      st0.insert(vec0[i]);
    } else {
      nxt = vec0[i];
    }
  }
  for (auto& x: vec1) {
    ll cur = x.first + dp[u][0];
    if (st0.count(x.second)) {
      cur -= x.second;
      cur += nxt;
    }
    ans = max(ans, cur);
  }

  {
    ll nxt = 0, sum = 0;
    multiset<ll> st0;
    for (int i = 0; i < k - 1 && i < vec0.size(); i++) {
      if (i < k - 2) {
        sum += vec0[i];
        st0.insert(vec0[i]);
      } else {
        nxt = vec0[i];
      }
    }
    for (auto& x: vec1) {
      ll cur = x.first + sum;
      if (st0.count(x.second)) {
        cur -= x.second;
        cur += nxt;
      }
      dp[u][1] = max(dp[u][1], cur);
    }
    ans = max(ans, dp[u][1]);
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
    }
    for (int i = 2, u, v, w; i <= n; i++) {
      scanf("%d%d%d", &u, &v, &w);
      edge[u].emplace_back(v, w);
      edge[v].emplace_back(u, w);
    }
    if (k == 0) {
      puts("0");
    } else if (k == 1) {
      ll ans = 0;
      for (int i = 1; i <= n; i++) {
        ll tot = 0;
        for (auto x: edge[i]) {
          tot += x.second;
        }
        ans = max(ans, tot);
      }
      printf("%lld\n", ans);
    } else {
      ans = 0;
      dfs(1, 0);
      printf("%lld\n", ans);
    }
  }
  return 0;
}