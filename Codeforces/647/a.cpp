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
const int maxn = 500000 + 5;

int n, m, tag[maxn], pos[maxn];
vector<int> edge[maxn], bag[maxn];

bool solve() {
  int tot = 0;
  for (int i = 1; i <= n; i++) {
    for (int x: bag[i]) {
      set<int> st;
      for (int v: edge[x]) {
        if (tag[v] == i) {
          return false;
        } else if (tag[v] < i) {
          st.insert(tag[v]);
        }
      }
      if ((int)st.size() == i - 1) {
        pos[++tot] == x;
      } else {
        return false;
      }
    }
  }
  assert(tot == n);
  return true;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v; scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", tag + i);
    bag[tag[i]].push_back(i);
  }
  if (solve()) {
    for (int i = 1; i <= n; i++) {
      printf("%d ", pos[i]);
    }
  } else {
    puts("-1");
  }
  return 0;
}