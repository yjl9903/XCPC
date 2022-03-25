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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n;

bool check(int x) {
  return x == (x & -x);
}

vector<PII> get(vector<int>& a) {
  vector<PII> ans;
  int sz = a.size();
  function<void(int,int)> dfs = [&](int l, int r) {
    if (l == r) return ;
    int m = (l + r) / 2;
    dfs(l, m);
    dfs(m + 1, r);
    assert(m - l + 1 == r - m);
    for (int i = l, j = m + 1; i <= m; i++, j++) {
      ans.emplace_back(a[i], a[j]);
    }
  };
  dfs(0, sz - 1);
  return ans;
}

int main() {
  scanf("%d", &n);
  vector<PII> ans;
  vector<int> Lhalf, Rhalf;
  for (int i = 20, j = 0; i >= 0; i--) {
    if (n >> i & 1) {
      int k = 1 << i;
      vector<int> vec;
      while (k--) {
        vec.push_back(++j);
      }
      if (Lhalf.empty()) {
        for (int x: vec) {
          Lhalf.push_back(x);
        }
      } else {
        for (int x: vec) {
          Rhalf.push_back(x);
        }
      }
      for (auto x: get(vec)) {
        ans.push_back(x);
      }
    }
  }
  if (!Rhalf.empty()) {
    while (!check(Rhalf.size())) {
      Rhalf.push_back(Lhalf.back());
      Lhalf.pop_back();
    }
    for (auto x: get(Rhalf)) {
      ans.push_back(x);
    }
  }
  printf("%d\n", ans.size());
  for (auto x: ans) {
    printf("%d %d\n", x.first, x.second);
  }
  return 0;
}