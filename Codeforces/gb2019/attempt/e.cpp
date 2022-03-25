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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, pre[maxn];
PII a[maxn];

ll dis(PII a, PII b) {
  ll x = a.first - b.first;
  ll y = a.second - b.second;
  return x * x + y * y;
}

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
  pre[find(x)] = find(y);
}

bool checker(const set<int>& st) {
  if ((int)st.size() == n) return false;
  map<ll,int> mp;
  auto same = [&](int x, int y) {
    if (st.count(x) && st.count(y)) return true;
    if (!st.count(x) && !st.count(y)) return true;
    return false;
  };
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      ll d = dis(a[i], a[j]);
      dbg(j, i, d, same(i, j));
      if (!mp.count(d)) {
        mp[d] = same(i, j);
      } else if (mp[d] != same(i, j)) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    pre[i] = i;
    scanf("%d%d", &a[i].first, &a[i].second);
  }
  for (int i = 1; i <= n; i++) {
    vector<pair<ll,int> > v;
    for (int j = 1; j <= n; j++) {
      if (i == j) continue;
      v.emplace_back(dis(a[i], a[j]), j);
    }
    sort(begin(v), end(v));
    for (int i = 0, j; i < n - 1; i = j) {
      j = i;
      while (j < n - 1 && v[i].first == v[j].first) {
        join(v[i].second, v[j].second); j++;
      }
    }
  }

  vector<int> ans = { 1 };
  for (int i = 2; i <= n; i++) if (find(i) == find(1)) ans.push_back(i);
  set<int> st; for (int x: ans) st.insert(x);
  auto same = [&](int x, int y) {
    if (st.count(x) && st.count(y)) return true;
    if (!st.count(x) && !st.count(y)) return true;
    return false;
  };

  vector<tuple<ll,int,int> > v;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      ll d = dis(a[i], a[j]);
      v.emplace_back(d, j, i);
    }
  }
  sort(begin(v), end(v));
  for (int sz = (int)v.size(), i = 0, j; i < sz; i = j) {
    j = i;
    int sum = 0;
    while (j < sz && get<0>(v[i]) == get<0>(v[j])) {
      sum += same(get<1>(v[j]), get<2>(v[j])); j++;
    }
    // dbg(i, j, get<0>(v[i]), sum);
    if (sum > 0 && sum < j - i) {
      for (int k = i; k < j; k++) {
        join(get<1>(v[k]), get<2>(v[k]));
        if (find(get<1>(v[k])) == find(1)) {
          st.insert(get<1>(v[k]));
        }
        if (find(get<2>(v[k])) == find(1)) {
          st.insert(get<2>(v[k]));
        }
      }
    }
  }
  
  // assert(checker(st));

  printf("%d\n", st.size());
  for (int x: st) printf("%d ", x);
  return 0;
}