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
const int maxn = 1000000 + 5;

int n, k, a[maxn], b[maxn];
vector<int> bag[maxn];

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= k; i++) {
    int p, x;
    scanf("%d%d", &p, &x);
    b[p] = x;
  }
  for (int i = n + 1; i >= 1; i--) {
    assert(i == n + 1 || b[i]);
    int x = b[i];
    i--;
    while (i >= 1 && b[i] == 0) {
      b[i] = --x;
      if (b[i] <= 0) b[i] = 1;
      i--;
    }
    i++;
  }
  for (int i = 1; i <= n; i++) {
    dbg(b[i]);
    assert(1 <= b[i] && b[i] <= n);
    bag[b[i]].push_back(i);
  }

  int cur = 0;
  for (int i = 1; i <= n; i++) {
    if (bag[i].empty()) continue;
    for (int j = 0; j < bag[i].size(); j++) {
      a[bag[i][j]] = cur + (int)bag[i].size() - j;
    }
    cur += bag[i].size();
  }
  
  vector<int> stk;
  for (int i = 1; i <= n; i++) {
    while (!stk.empty() && stk.back() > a[i]) stk.pop_back();
    stk.push_back(a[i]);
    if (stk.size() != b[i]) {
      puts("-1");
      return 0;
    }
  }
  for (int i = 1; i <= n; i++) {
    printf("%d%c", a[i], " \n"[i == n]);
  }
  return 0;
}