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

int n, d, a[maxn], id[maxn];
int pre[maxn], f[maxn];
bool used[maxn];

int main() {
  scanf("%d%d", &d, &n);
  for (int i = 1; i <= n; i++) {
    char buf[16];
    scanf("%s", buf);
    int val = 0;
    for (int i = d - 1; i >= 0; i--) {
      val = val * 2 + (buf[i] - '0');
    }
    a[i] = val;
    id[val] = i;
  }
  vector<int> op;
  int cnt = 0;
  while (cnt < n) {
    for (int s = 1; s < (1 << d); s++) {
      f[s] = -1;
      for (int i = 0; i < d; i++) {
        if (s >> i & 1) {
          if (f[s ^ (1 << i)] > f[s]) {
            f[s] = f[s ^ (1 << i)];
            pre[s] = i;
          }
        }
      }
      f[s] += id[s];
    }
    int mx = -1, pos = -1;
    for (int i = 1; i <= n; i++) {
      if (used[i]) continue;
      if (f[a[i]] > mx) {
        mx = f[a[i]];
        pos = i;
      }
    }
    int cur = a[pos];
    vector<int> plan;
    while (cur) {
      if (id[cur] > 0) {
        used[id[cur]] = true;
        id[cur] = 0;
        cnt++;
      }
      plan.push_back(pre[cur]);
      cur ^= 1 << pre[cur];
    }
    reverse(plan.begin(), plan.end());
    for (int x: plan) {
      op.push_back(x);
    }
    op.push_back(-1);
  }
  op.pop_back();
  printf("%d\n", op.size());
  for (int x: op) {
    if (x == -1) {
      putchar('R');
    } else {
      putchar('0' + x);
    }
    putchar(' ');
  }
  return 0;
}