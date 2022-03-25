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
const int mod = 1e9 + 7;
const int base = 5782344;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, q, A, B, x[maxn], y[maxn];

vector<pair<ll,int> > bag[maxn];

int main() {
  scanf("%d%d", &n, &q);
  vector<ll> lsh;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", x + i, y + i);
    ll val = x[i] + 2ll * y[i];
    lsh.push_back(val);
  }
  sort(lsh.begin(), lsh.end());
  lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
  for (int i = 1; i <= n; i++) {
    int id = lower_bound(lsh.begin(), lsh.end(), x[i] + 2ll * y[i]) - lsh.begin() + 1;
    ll val = x[i] - 2ll * y[i];
    for (; id; id -= id & -id) {
      bag[id].emplace_back(val, i);
    }
  }
  for (int i = 0; i < maxn; i++) {
    if (!bag[i].empty()) {
      sort(bag[i].begin(), bag[i].end(), greater<pair<ll,int> >());
    }
  }

  int ans = 0;
  while (q--) {
    scanf("%d%d", &A, &B);
    int x = -1 - (1ll * ans + A) % mod;
    int y = (1ll * ans + B) % mod;
    int id = lower_bound(lsh.begin(), lsh.end(), x + 2ll * y) - lsh.begin() + 1;
    ll val = x - 2ll * y;
    vector<int> vec;
    for (; id < maxn; id += id & -id) {
      for (auto& x: bag[id]) {
        if (x.first >= val) {
          vec.push_back(x.second);
        } else {
          break;
        }
      }
    }
    sort(vec.begin(), vec.end());
    ans = 0;
    int cur = 1;
    for (int x: vec) {
      ans = (ans + 1ll * cur * x % mod) % mod;
      cur = 1ll * cur * base % mod;
    }
    printf("%d\n", ans);
  }
  return 0;
}