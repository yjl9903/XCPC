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
const int maxn = 1000000 + 5;

int n, a[maxn];
ll pre[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    pre[i] = pre[i - 1] + a[i];
  }
  vector<PII> v;
  auto cmp = [&](PII a, PII b) -> bool {
    ll y1 = pre[a.second] - pre[a.first - 1];
    ll x1 = a.second - a.first + 1;
    ll y2 = pre[b.second] - pre[b.first - 1];
    ll x2 = b.second - b.first + 1;
    return y1 * x2 >= x1 * y2;
  };
  for (int i = 1; i <= n; i++) {
    PII tot(i, i);
    while (!v.empty() && cmp(v.back(), tot)) {
      tot.first = v.back().first;
      v.pop_back();
    }
    v.push_back(tot);
  }
  for (auto& x: v) {
    double r = 1.0 * (pre[x.second] - pre[x.first - 1]) / (x.second - x.first + 1);
    for (int j = x.first; j <= x.second; j++) {
      printf("%.9lf\n", r);
    }
  }
  return 0;
}