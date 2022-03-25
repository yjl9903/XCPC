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

int n, x[maxn], y[maxn];

int sgn(int x) {
  if (x == 0) {
    return 0;
  } else if (x < 0) {
    return -1;
  } else {
    return 1;
  }
}

PII parse(int x, int y) {
  if (x == 0) {
    return { 0, sgn(y) };
  } else if (y == 0) {
    return { sgn(x), 0 };
  }
  int g = __gcd(abs(x), abs(y));
  return { x / g, y / g };
}

int main() {
  scanf("%d", &n);
  map<PII, vector<PII> > mp;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", x + i, y + i);
    if (i > 1) {
      x[i] -= x[1];
      y[i] -= y[1];
      auto dir = parse(x[i], y[i]);
      int len = dir.first != 0 ? abs(x[i] / dir.first) : abs(y[i] / dir.second);
      mp[dir].emplace_back(len, i);
    }
  }
  vector<int> ans = { 1 };
  for (auto x: mp) {
    sort(x.second.begin(), x.second.end());
    for (int i = 0; i < x.second.size(); i++) {
      ans.push_back(x.second[i].second);
    }
    for (int i = (int)x.second.size() - 2; i >= 0; i--) {
      ans.push_back(x.second[i].second);
    }
    ans.push_back(1);
  }
  printf("%d\n", ans.size());
  for (int x: ans) printf("%d ", x);
  return 0;
}