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

int n, mx = 0, mn = 1, dep[maxn];
vector<int> edge[maxn];

bool isLeaf(int u) {
  return (int)edge[u].size() == 1;
}

void dfs(int u, int f) {
  bool flag = false;
  for (int v: edge[u]) {
    if (v == f) continue;
    dep[v] = dep[u] + 1;
    if (isLeaf(v)) {
      flag = true;
    } else {
      mx++;
      dfs(v, u);
    }
  }
  if (flag && dep[u] > 1) {
    mx++;
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  int rt = -1;
  for (int i = 1; i <= n; i++) {
    if (isLeaf(i)) {
      rt = i; break;
    }
  }
  dfs(rt, -1);
  for (int i = 1; i <= n; i++) {
    if (isLeaf(i) && dep[i] % 2) {
      mn = 3; break;
    }
  }
  printf("%d %d\n", mn, mx);
  return 0;
}