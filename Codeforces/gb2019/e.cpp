#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

ll dis(PII a, PII b) {
  ll x = a.first - b.first;
  ll y = a.second - b.second;
  return x * x + y * y;
}

int n, col[maxn], vis[maxn];
PII a[maxn];
vector<int> edge[maxn];

bool checker(const vector<int>& v) {
  if ((int)v.size() == n) return false;
  set<int> st; for (int x: v) st.insert(x);
  map<ll,int> mp;
  auto same = [&](int x, int y) {
    if (st.count(x) && st.count(y)) return true;
    if (!st.count(x) && !st.count(y)) return true;
    return false;
  };
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      ll d = dis(a[i], a[j]);
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
    scanf("%d%d", &a[i].first, &a[i].second);
  }
  ll g = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      ll d = dis(a[i], a[j]);
      g = __gcd(g, d);
    }
  }
  vector<int> ans = { 1 };
  for (int i = 2; i <= n; i++) {
    if (dis(a[1], a[i]) / g % 2 == 0) {
      ans.push_back(i);
    }
  }
  printf("%d\n", ans.size());
  for (int x: ans) printf("%d ", x);
  return 0;
}