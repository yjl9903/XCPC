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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000 + 5;

int n, k, ans[maxn], vis[maxn];
vector<int> pos[maxn];

vector<int> rest;
int query(int l, int r) {
  vector<int> v;
  for (int x: rest) {
    v.push_back(x);
  }
  for (int i = l; i <= r; i++) {
    for (int x: pos[i]) {
      v.push_back(x);
    }
  }
  cout << "? " << v.size();
  for (int x: v) {
    cout << " " << x;
  }
  cout << endl;
  cin >> r;
  return r;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      vis[i] = 0;
    }
    rest.clear();
    for (int i = 1, m, x; i <= k; i++) {
      ans[i] = -1;
      pos[i].clear();
      cin >> m;
      while (m--) {
        cin >> x;
        vis[x] = true;
        pos[i].push_back(x);
      }
    }
    for (int i = 1; i <= n; i++) {
      if (!vis[i]) {
        rest.push_back(i);
      }
    }
    int mx = query(1, k);
    function<void(int,int)> solve = [&](int l, int r) {
      dbg(l, r);
      if (l == r) {
        vector<int> v;
        for (int x: rest) v.push_back(x);
        for (int i = 1; i <= k; i++) {
          if (i == l) continue;
          for (int x: pos[i]) v.push_back(x);
        }
        cout << "? " << v.size();
        for (int x: v) {
          cout << " " << x;
        }
        cout << endl;
        int res;
        cin >> res;
        ans[l] = res;
        return ;
      }
      int m = (l + r) / 2;
      int tot = query(l, m);
      if (tot == mx) {
        for (int i = m + 1; i <= r; i++) {
          ans[i] = mx;
        }
        solve(l, m);
      } else {
        for (int i = l; i <= m; i++) {
          ans[i] = mx;
        }
        solve(m + 1, r);
      }
    };
    solve(1, k);

    cout << "!";
    for (int i = 1; i <= k; i++) {
      assert(ans[i] != -1);
      cout << " " << ans[i];
    }
    cout << endl;

    string val;
    cin >> val;
  }
  return 0;
}