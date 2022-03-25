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
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const ll inf = 1ll << 60;
const int maxn = 200000 + 5;

int n, s;

struct DS {
  ll base = 0;
  map<int, ll> f;
  set<pair<ll,int> > bag;

  int size() {
    return f.size();
  }

  bool count(int x) {
    return f.count(x);
  }

  ll get(int x) {
    if (f.count(x)) {
      return f[x] + base;
    } else {
      return inf;
    }
  }

  void set(int x, ll v) {
    if (f.count(x)) {
      v = std::min(v, erase(x));
    }
    v -= base;
    f[x] = v;
    bag.emplace(v, x);
  }

  ll erase(int x) {
    if (f.count(x)) {
      ll val = f[x];
      f.erase(x);
      bag.erase({ val, x });
      return val + base;
    } else {
      return inf;
    }
  }

  ll min() {
    return bag.begin()->first + base;
  }
};

int main() {
  scanf("%d%d", &n, &s);
  vector<DS> stk { {} };
  vector<int> cond;
  stk.back().set(0, 0);
  for (int i = 1; i <= n; i++) {
    char op[8];
    scanf("%s", op);
    if (op[0] == 's') {
      int x, v;
      scanf("%d%d", &x, &v);
      ll mn = stk.back().min();
      stk.back().base += v;
      if (x != s) {
        stk.back().set(x, mn);
      }
    } else if (op[0] == 'i') {
      int x;
      scanf("%d", &x);
      DS u;
      u.set(x, stk.back().get(x));
      stk.back().erase(x);
      stk.push_back(u);
      cond.push_back(x);
    } else if (op[0] == 'e') {
      int c = cond.back();
      cond.pop_back();

      int sz = stk.size();
      auto& x = stk[sz - 1];
      auto& y = stk[sz - 2];

      if (x.size() > y.size()) swap(x, y);
      for (auto u: x.f) {
        y.set(u.first, x.get(u.first));
      }
      stk.pop_back();
    }
  }
  printf("%lld\n", stk.back().min());
  return 0;
}