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

int n, pre[maxn], siz[maxn];
char s[maxn];
vector<int> edge[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
bool join(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return false;
  if (siz[x] > siz[y]) swap(x, y);
  pre[x] = y; siz[y] += siz[x];
  return true;
}

int main() {
  scanf("%d%s", &n, s + 1);
  for (int i = 1; i <= n; i++) {
    pre[i] = i; siz[i] = 1;
  }
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
    if (s[u] == 'W' && s[v] == 'W') {
      join(u, v);
    }
  }
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i] == 'W') continue;
    int sum = 0; ll tot = 0;
    for (int v: edge[i]) {
      if (s[v] == 'B') continue;
      tot += 1ll * siz[find(v)] * sum;
      sum += siz[find(v)];
    }
    ans += tot + sum;
  }
  cout << ans << endl;
  return 0;
}