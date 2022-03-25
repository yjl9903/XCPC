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
using ll = long long;
using PII = pair<int,int>;
using PLL = pair<ll,ll>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n;
PII a[maxn];

PLL pos[maxn];

PLL make(int i, int j) {
  // dbg(j, i, a[j].second, a[i].second);
  int fz = a[i].first - a[j].first;
  int fm = a[j].second - a[i].second;
  int g = __gcd(fz, fm);
  assert(fm > 0);
  return PLL { fz / g, fm / g };
}

bool cmp(PLL a, PLL b) { // a <= b
  return a.first * b.second <= b.first * a.second;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    map<PII, int> mp;
    map<int, int> mxA;
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &a[i].first, &a[i].second);
      mp[a[i]]++;
      mxA[a[i].first] = max(mxA[a[i].first], a[i].second);
    }
    n = 0;
    for (auto it = mxA.rbegin(); it != mxA.rend(); it++) {
      a[++n] = *it;
      dbg(n, it->first, it->second);
    }

    vector<int> vec;
    for (int i = 1; i <= n; i++) {
      while (!vec.empty()) {
        if (a[i].second <= a[vec.back()].second) {
          break;
        }
        auto itx = make(vec.back(), i);
        if (cmp(itx, pos[vec.back()])) {
          vec.pop_back();
        } else {
          break;
        }
      }

      if (i == 1) {
        pos[1] = PLL { 0, 1 };
        vec.push_back(1);
      } else {
        assert(!vec.empty());
        if (a[i].second > a[vec.back()].second) {
          pos[i] = make(vec.back(), i);
          vec.push_back(i);
        }
      }
    }
    
    int ans = 0;
    for (int id: vec) {
      if (mp[a[id]] == 1) {
        ans++;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}