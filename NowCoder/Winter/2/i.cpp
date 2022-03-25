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
const int maxn = 200000 + 5;

inline int lowbit(int x) {
  return x & -x;
}

int n, a[maxn];
ll ans = 0;

void dfs(int i, vector<int> vec) {
  if (i == 31) return ;
  if ((int)vec.size() <= 1) return ;
  vector<int> v[2];
  for (int x: vec) {
    v[a[x] >> i & 1].push_back(x);
  }
  if (!v[0].empty() && !v[1].empty()) {
    ans += 1ll << i;
  }
  dfs(i + 1, v[0]); dfs(i + 1, v[1]);
}

int main() {
  scanf("%d", &n);
  set<int> st;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    st.insert(a[i]);
  }
  vector<int> v; n = 0;
  for (int x: st) {
    a[++n] = x; v.push_back(n);
  }
  dfs(0, v);
  cout << ans << endl;
  return 0;
}