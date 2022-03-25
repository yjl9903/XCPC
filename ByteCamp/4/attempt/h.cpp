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
#ifdef XLor
  #define dbg(args...) cout  << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const ll inf = 1ll << 60;
const int maxn = 200000 + 5;

int n, L, a[maxn], len[maxn];

struct Node {
  ll val; int len;
  vector<int> pos;

  bool operator < (const Node& b) const {
    if (val != b.val) return val < b.val;
    return len < b.len;
  }
};

bool check(vector<int>& v) {
  priority_queue<int, vector<int>, greater<int> > pq;
  for (int x: v) pq.push(x);
  while (pq.size() > 1) {
    int x = pq.top(); pq.pop();
    int y = pq.top(); pq.pop();
    pq.push(max(x, y) + 1);
  }
  return pq.top() <= L;
}

int main() {
  while (scanf("%d%d", &n, &L) == 2) {
    if (!n && !L) break;
    vector<Node> vec;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      len[i] = 0;
      vec.push_back({ (ll)a[i], 0, { i } });
    }
    if (n == 1) {
      printf("%d\n1\n", a[1]);
      continue;
    }
    while ((int)vec.size() > 1) {
      Node tot; tot.val = inf; tot.len = -1;
      int choose1 = -1, choose2 = -1;
      for (int i = 0; i < (int)vec.size(); i++) {
        for (int j = i + 1; j < (int)vec.size(); j++) {
          vector<int> v = { max(vec[i].len, vec[j].len) + 1 };
          for (int k = 0; k < (int)vec.size(); k++) {
            if (k == i || k == j) continue;
            v.push_back(vec[k].len);
          }
          if (check(v)) {
            Node x;
            x.val = vec[i].val + vec[j].val;
            x.len = max(vec[i].len, vec[j].len) + 1;
            if (x.val > tot.val) continue;
            else if (x.val == tot.val && x.len >= tot.len) continue;
            for (int p: vec[i].pos) {
              x.pos.push_back(p);
            }
            for (int p: vec[j].pos) {
              x.pos.push_back(p);
            }
            choose1 = i; choose2 = j;
            tot = x;
          }
        }
      }
      assert(choose1 != -1 && choose2 != -1);

      vec.erase(vec.begin() + choose2);
      vec.erase(vec.begin() + choose1);
      vec.push_back(tot);

      for (int p: tot.pos) {
        len[p]++;
      }
    }
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
      assert(len[i] <= L);
      sum += 1ll * len[i] * a[i];
    }
    printf("%lld\n", sum);
    for (int i = 1; i <= n; i++) {
      printf("%d%c", len[i], " \n"[i == n]);
    }
  }
  return 0;
}