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
using PDD = pair<double, double>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int X, Y, n;
PDD a[maxn];

double dis(PDD a, PDD b) {
  double x = a.first - b.first;
  double y = a.second - b.second;
  return x * x + y * y;
}

int pre[maxn];
int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
bool join(int x, int y) {
  x = find(x);
  y = find(y);
  if (x != y) {
    pre[x] = y;
    return true;
  } else {
    return false;
  }
}
bool check(double R) {
  for (int i = 1; i <= n + 5; i++) {
    pre[i] = i;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      double x = a[i].first - a[j].first;
      double y = a[i].second - a[j].second;
      if (x * x + y * y < 4 * R * R) {
        join(i, j);
      }
    }
    if (a[i].second < R) {
      join(i, n + 1);
    }
    if (a[i].first < R) {
      join(i, n + 2);
    }
    if (Y - a[i].second < R) {
      join(i, n + 3);
    }
    if (X - a[i].first < R) {
      join(i, n + 4);
    }
  }
  return find(n + 1) != find(n + 3) 
      && find(n + 2) != find(n + 4)
      && find(n + 1) != find(n + 2)
      && find(n + 3) != find(n + 4);
}

int main() {
  scanf("%d%d%d", &X, &Y, &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lf%lf", &a[i].first, &a[i].second);
  }
  double l = 0, r = 1e6 + 1;
  for (int i = 0; i < 200; i++) {
    double m = (l + r) / 2.0;
    if (check(m)) {
      l = m;
    } else {
      r = m;
    }
  }
  printf("%.6lf\n", l);
  return 0;
}