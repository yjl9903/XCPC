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
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 2e18 + 1;
const int maxn = 100000 + 5;

ll mul(ll x, ll y) {
  if (!x || !y) return 0;
  if (inf / x < y) return inf;
  return x * y;
}

int n;
ll k, fac[100], dp[100];

int main() {
  fac[0] = fac[1] = 1;
  for (int i = 2; i < 100; i++) fac[i] = mul(i - 1, fac[i - 1]);
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%I64d", &n, &k);
    dp[n + 1] = 1;
    for (int i = n; i >= 1; i--) {
      dp[i] = 0;
      for (int j = i; j <= n; j++) {
        dp[i] += mul(fac[j - i], dp[j + 1]);
        dp[i] = min(dp[i], inf);
      }
    }
    k--;
    if (k >= dp[1]) {
      puts("-1"); continue;
    }
    vector<int> ans;
    auto gen = [&](int len, ll k, int shift) {
      vector<int> fa(len);
      for (int i = 0; i < len; i++) fa[i] = i;
      function<int(int)> find = [&](int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
      };
      function<void(int,int)> join = [&](int x, int y) {
        fa[find(x)] = find(y);
      };
      set<int> st = { len - 1 };
      ans.push_back(len - 1 + shift);
      join(0, len - 1);
      int cnt = len - 2;
      for (int i = 1; i < len; i++) {
        for (int j = 0; j + 1 < len; j++) {
          if (st.count(j)) continue;
          if (i == len - 1) {
            ans.push_back(j + shift);
            break;
          }
          if (find(i) == find(j)) continue;
          if (k >= (cnt >= 0 ? fac[cnt] : 1)) {
            k -= (cnt >= 0 ? fac[cnt] : 1);
          } else {
            cnt--;
            ans.push_back(j + shift);
            st.insert(j); join(i, j);
            break;
          }
        }
      }
    };
    for (int i = 1; i <= n; ) {
      for (int j = i; j <= n; j++) {
        ll val = mul(fac[j - i], dp[j + 1]);
        if (val <= k) {
          k -= val;
        } else {
          gen(j - i + 1, k / dp[j + 1], i);
          k %= dp[j + 1]; i = j + 1;
          break;
        }
      }
    }
    for (int x: ans) printf("%d ", x);
    puts("");
  }
  return 0;
}