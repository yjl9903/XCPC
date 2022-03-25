#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
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
using ll = long long;
using ull = unsigned long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int threshold = 10000000;
const int maxn = 500000 + 5;

ull k1, k2;
ull xorShift() {
  ull k3 = k1, k4 = k2;
  k1 = k4;
  k3 ^= (k3 << 23);
  k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
  return k2 + k4;
}

int n, m, a[maxn], b[maxn], step[maxn];
ll res[maxn];

int main() {
  while (scanf("%d%d%llu%llu", &n, &m, &k1, &k2) == 4) {
    set<PII> st[3];
    for (int i = 1; i <= n; i++) {
      a[i] = xorShift() % threshold + 1;
      b[i] = xorShift() % threshold + 1;
      step[i] = 0;
      st[0].emplace(a[i], i);
      st[1].emplace(a[i] + b[i], i);
      st[2].emplace(a[i] + b[i] + a[i], i);
    }
    ll cur[3] = { 0, 0, 0 };
    vector<PII> plan[3];
    ll ans = 0;
    for (int i = 1; i <= m; i++) {
      if (i >= 3 * n) {
        
        continue;
      }

      ll nxt[3] = { 0, 0, 0 };
      vector<PII> nxtPlan[3];
      vector<PII> vec[2];
      auto it = st[0].rbegin();
      if (it != st[0].rend()) {
        vec[0].push_back(*it);

        nxt[0] = it->first;
        plan[0] = { { it->second, 1 } };
        
        it++;
        if (it != st[0].rend()) {
          vec[0].push_back(*it);
          it++;

          nxt[1] = vec[0][0].first + vec[0][1].first;
          plan[1] = { { vec[0][0].second, 1 }, { vec[0][1].second, 1 } };

          if (it != st[0].rend()) {
            vec[0].push_back(*it);

            nxt[2] = vec[0][0].first + vec[0][1].first + vec[0][2].first;
            plan[2] = { { vec[0][0].second, 1 }, { vec[0][1].second, 1 }, { vec[0][2].second, 1 } };
          }
        }
      }
      it = st[1].rbegin();
      if (it != st[1].rend()) {
        vec[1].push_back(*it);

        if (it->first > nxt[1]) {
          nxt[1] = it->first;
          plan[1] = { { it->second, 2 } };
        }

        if (!vec[0].empty() && vec[0][0].first + it->first > nxt[2]) {
          if (vec[0][0].second != it->second) {
            nxt[2] = vec[0][0].first + it->first;
            plan[2] = { { vec[0][0].first, 1 }, { it->first, 2 } };
          }
        }

        it++;
        if (it != st[1].rend()) {
          vec[1].push_back(*it);
        }
      }

      if (!st[2].empty()) {
        if (st[2].rbegin()->second > nxt[2]) {
          nxt[2] = st[2].rbegin()->second;
          plan[2] = { { st[2].rbegin()->first, 3 } };
        }
      }

      nxt[0] += cur[0];
      nxt[1] += cur[0];
      nxt[2] += cur[0];

      
    }
    printf("%lld\n", ans);
  }
  return 0;
}