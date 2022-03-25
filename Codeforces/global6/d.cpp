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
#include <queue>
#include <random>
#include <ctime>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
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
const int maxn = 100000 + 5;

int n, m, vis[maxn];
ll det[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v, d; scanf("%d%d%d", &u, &v, &d);
    det[u] += d;
    det[v] -= d;
  }
  vector<int> va, vb;
  for (int i = 1; i <= n; i++) {
    if (det[i] > 0) va.push_back(i);
    else if (det[i] < 0) vb.push_back(i);
  }
  vector<tuple<int,int,ll> > ans;
  while (!va.empty() && !vb.empty()) {
    int a = va.back();
    int b = vb.back();
    ll w = min(det[a], -det[b]);
    ans.emplace_back(a, b, w);
    det[a] -= w;
    det[b] += w;
    if (det[a] == 0) va.pop_back();
    if (det[b] == 0) vb.pop_back();
  }
  printf("%d\n", ans.size());
  for (auto& x: ans) {
    int a, b; ll c;
    tie(a, b, c) = x;
    printf("%d %d %I64d\n", a, b, c);
  }
  return 0;
}