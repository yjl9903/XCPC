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

int n, m, deg[maxn], pre[maxn], siz[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return ;
  pre[x] = y; siz[y] += siz[x];
}

int main() {
  scanf("%d%d", &n, &m);
  vector<PII> egs;
  for (int i = 1, u, v; i <= m; i++) {
    scanf("%d%d", &u, &v);
    deg[u]++; deg[v]++;
    egs.push_back({ u, v });
  }
  for (int i = 1; i <= n; i++) {
    pre[i] = i;
    siz[i] = deg[i] % 2;
  }
  for (PII e: egs) {
    join(e.first, e.second);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (i == find(i)) {
      if (deg[i] != 0) {
        if (!siz[i]) ans++;
        else ans += siz[i] / 2;
      }
    }
  }
  if (ans <= 1) {
    puts("YES");
  } else {
    puts("NO");
    printf("%d\n", ans);
  }
  return 0;
}