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
const int maxn = 100000 + 5;

int n, m, k, pre[maxn], siz[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
bool join(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y) return false;
  if (siz[x] > siz[y]) swap(x, y);
  pre[x] = y;
  siz[y] += siz[x];
  return true;
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  vector< tuple<int,int,int> > edge[2];
  edge[0].reserve(m);
  edge[1].reserve(m);
  for (int i = 1; i <= m; i++) {
    int u, v, w, col;
    scanf("%d%d%d%d", &u, &v, &w, &col);
    edge[col].emplace_back(w, u, v);
  }

  sort(begin(edge[0]), end(edge[0]));
  sort(begin(edge[1]), end(edge[1]));

  auto check = [&](int cost) {
    for (int i = 1; i <= n; i++) {
      pre[i] = i;
      siz[i] = 1;
    }
    int i = 0, j = 0;
    while (i < edge[0].size() && j < edge[1].size()) {
      int w0 = get<0>(edge[0][i]) - cost;
      int w1 = get<0>(edge[1][j]);
      if (w0 <= w1) {
        int u = get<1>(edge[0][i]);
        int v = get<2>(edge[0][i]);
        join(u, v);

        i++;
      } else {
        int u = get<1>(edge[1][j]);
        int v = get<2>(edge[1][j]);
        join(u, v);

        j++;
      }
    }
    while (i < edge[0].size()) {
      int w0 = get<0>(edge[0][i]) - cost;
      
      i++;
    }
    while (j < edge[1].size()) {
      int w1 = get<0>(edge[1][j]);
      
      j++;
    }
    return true;
  };

  int ans = 0, l = 0, r = 200;
  while (l <= r) {
    int m = (l + r) / 2;
    if (check(m)) {
      ans = m;

    } else {

    }
  }

  return 0;
}