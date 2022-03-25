#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <ctime>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <random>
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
const int maxn = 1000000 + 5;

mt19937_64 rnd(time(nullptr));

namespace sieve {
  const int maxp = 1000000 + 5;
  int vis[maxp], prime[maxp], tot;
  void init() {
    ms(vis, 0);
    for (int i = 2; i < maxp; i++) {
      if (!vis[i]) prime[tot++] = i;
      for (int j = 0; j < tot && prime[j] * i < maxp; j++) {
        vis[i * prime[j]] = 1;
        if (i % prime[j] == 0) break;
      }
    }
  }
}

template<typename T>
int minRotate(const vector<T>& a) {
  int n = a.size(), i = 0, j = 1, k = 0;
  while (i < n && j < n && k < n) {
    if (a[(i + k) % n] == a[(j + k) % n]) {
      k++;
    } else {
      if (a[(i + k) % n] > a[(j + k) % n]) i += k + 1;
      else j += k + 1;
      if (i == j) i++;
      k = 0;
    }
  }
  return min(i, j);
}

int n, m;
vector<int> edge[maxn];

ull gid(ull x) {
  static map<ull,ull> mp {};
  if (mp.count(x)) {
    return mp[x];
  } else {
    return mp[x] = rnd();
  }
}

int main() {
  sieve::init();
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    set<vector<ull> > all;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &m);
      for (int i = 1; i <= m; i++) {
        edge[i].clear();
      }
      for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
      }

      vector<int> fa(m + 1, 0), vis(m + 1, 0), onRing(m + 1, 0), ring;
      function<void(int,int)> getRing = [&](int u, int f) {
        vis[u] = true;
        fa[u] = f;
        for (int v: edge[u]) {
          if (v == f) continue;
          if (vis[v]) {
            if (!ring.empty()) continue;
            int x = u;
            while (x != v) {
              ring.push_back(x);
              onRing[x] = true;  
              x = fa[x];
            }
            ring.push_back(x);
            onRing[x] = true;  
            continue;
          }
          getRing(v, u);
        }
        vis[u] = false;
      };
      getRing(1, 0);

      vector<ull> hshRing;
      for (int x: ring) {
        function<ull(int,int)> dfs = [&](int u, int f) {
          vector<ull> vec;
          for (int v: edge[u]) {
            if (v == f) continue;
            if (onRing[u] && onRing[v]) continue;
            auto val = dfs(v, u);
            vec.push_back(val);
          }
          sort(vec.begin(), vec.end());
          ull sum = 0;
          for (int i = 0; i < vec.size(); i++) {
            sum += vec[i] * sieve::prime[i];
          }
          return gid(sum);
        };
        ull val = dfs(x, 0);
        hshRing.push_back(val);
      }
      vector<ull> hsh1 { hshRing };
      vector<ull> hsh2 { hshRing };
      reverse(hsh2.begin(), hsh2.end());
      rotate(hsh1.begin(), hsh1.begin() + minRotate(hsh1), hsh1.end());
      rotate(hsh2.begin(), hsh2.begin() + minRotate(hsh2), hsh2.end());
      all.insert(min(hsh1, hsh2));
    }
    printf("%d\n", all.size());
  }
  return 0;
}