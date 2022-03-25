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
const int inf = 1 << 30;
const int maxn = 400000 + 5;

int n, m, a[maxn];

int get(int x, int y) {
  return x * m + y;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &a[get(i, j)]);
    }
  }
  ll ans = 0;
  for (int j = 0; j < m; j++) {
    set<int> st;
    for (int i = 0; i < n; i++) {
      // dbg(get(i, j) + 1);
      st.insert(get(i, j) + 1);
    }
    map<int,int> mp;
    for (int i = 0; i < n; i++) {
      if (st.count(a[get(i, j)])) {
        int tag = (a[get(i, j)] - 1 - j) / m;
        if (tag <= i) {
          mp[i - tag]++;
        } else {
          mp[n + i - tag]++;
        }
      }
    }
    dbg(j);
    int mn = n;
    for (auto& x: mp) {
      mn = min(mn, x.first + n - x.second);
      dbg(x.first, x.second);
    }
    ans += mn;
  }
  cout << ans << endl;
  return 0;
}