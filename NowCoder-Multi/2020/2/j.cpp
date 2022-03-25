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

int n, k, ans[maxn], a[maxn], pre[maxn];
vector<int> blk[maxn];

int temp[maxn], b[maxn], c[maxn];
void qpow(const vector<int>& vec, long long k) {
  for (const int& x: vec) c[x] = b[x] = a[x];
  while (k) {
    if (k % 2) {
      for (const int& x: vec) temp[x] = b[c[x]];
      for (const int& x: vec) c[x] = temp[x];
    }
    for (const int& x: vec) temp[x] = b[b[x]];
    for (const int& x: vec) b[x] = temp[x];
    k >>= 1;
  }
}

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    pre[i] = i;
  }
  for (int i = 1; i <= n; i++) {
    int x = find(i), y = find(a[i]);
    if (x != y) {
      pre[x] = y;
    }
  }
  for (int i = 1; i <= n; i++) {
    blk[find(i)].push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    if (blk[i].empty()) continue;
    if (blk[i].size() == 1) {
      ans[i] = i;
      continue;
    }
    vector<int> ring { i };
    int x = a[i];
    while (x != i) {
      ring.push_back(x);
      x = a[x];
    }
    assert(ring.size() == blk[i].size());

    int turn = (int)ring.size() - k % (int)ring.size();
    qpow(ring, turn);
    for (int x: ring) {
      ans[x] = c[x];
    }
  }
  for (int i = 1; i <= n; i++) {
    printf("%d%c", ans[i], " \n"[i == n]);
  }
  return 0;
}