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
#include <unordered_map>
#include <bitset>
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
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100 + 5;

int n, a[maxn];
ll pre[maxn];
unordered_map<bitset<maxn>,ll> f[maxn], g[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    pre[i] = pre[i - 1] + a[i];
  }
  ll sum = 0;
  vector<PII> line;
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      sum += pre[j] - pre[i - 1];
      line.emplace_back(i, j);
    }
  }
  sort(line.begin(), line.end(), [&](const PII& lhs, const PII& rhs) {
    ll a = pre[lhs.second] - pre[lhs.first - 1];
    ll b = pre[rhs.second] - pre[rhs.first - 1];
    return a > b;
  });
  f[0][0] = 0;
  for (int i = 0; i < line.size(); i++, swap(f, g)) {
    for (int j = 0; j <= i + 1; j++) {
      g[j].clear();
    }
    ll cur = pre[line[i].second] - pre[line[i].first - 1];
    for (int j = 0; j <= i; j++) {
      for (auto& x: f[j]) {
        auto state = x.first;
        ll val = x.second;
        g[j][state] = max(g[j][state], val);
        for (int l = 1; l <= line[i].first; l++) {
          for (int r = line[i].second; r <= n; r++) {
            if (!state[n * (l - 1) + (r - 1)]) {
              val += cur;
              state[n * (l - 1) + (r - 1)] = 1;
            }
          }
        }
        g[j + 1][state] = max(g[j + 1][state], val);
      }
    }
  }
  for (int i = 1; i <= n * (n + 1) / 2; i++) {
    ll val = 0;
    for (auto& x: f[i]) {
      val = max(val, x.second);
    }
    printf("%lld\n", sum - val);
  }
  return 0;
}