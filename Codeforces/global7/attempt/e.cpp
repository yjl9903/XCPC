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
const int maxn = 300000 + 5;

int n, p[maxn], q[maxn], pos[maxn], tag[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", p + i);
    pos[p[i]] = i;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", q + i);
  }
  set<int> ok, del;
  int ans = n;
  auto check = [&]() {
    auto it = del.lower_bound(pos[ans]);
    if (it == del.end()) {
      return false;
    }
    ok.insert(pos[ans]);
    tag[pos[ans]] = *it;
    del.erase(it);
    ans--;
    return true;
  };
  for (int i = 1; i <= n; i++) {
    printf("%d ", ans);
    auto it = ok.upper_bound(q[i]);
    if (it != ok.begin()) {
      it--;
      if (tag[*it] > q[i]) {
        del.insert(tag[*it]);
        tag[*it] = q[i];
      } else {
        del.insert(q[i]);
      }
    } else {
      del.insert(q[i]);
    }
    while (check());
  }
  return 0;
}