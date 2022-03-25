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
#ifdef XLor
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, k, ch[maxn][26], que[maxn], dep[maxn];
int tot, dfn[maxn], siz[maxn];
bool key[maxn];

void predfs(int u) {
  dfn[u] = key[u] ? ++tot : tot;
  for (int c = 0; c < 26; c++) {
    if (!ch[u][c]) continue;
    int v = ch[u][c];
    dep[v] = dep[u] + 1;
    predfs(v);
    siz[u] += siz[v];
  }
}

int cost[maxn];
vector<int> stk;
void dfs(int u, int f) {
  int val = cost[u] - dfn[u];
  if (key[u]) val++;
  stk.push_back(min(val, stk.back()));
  for (int c = 0; c < 26; c++) {
    if (!ch[u][c]) continue;
    int v = ch[u][c];
    cost[v] = cost[u] + 1;
    if (key[v]) {
      cost[v] = min(cost[v], stk.back() + dfn[v]);
    }
    dfs(v, u);
  }
  stk.pop_back();
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int p; char s[2];
    scanf("%d%s", &p, s);
    ch[p][s[0] - 'a'] = i;
  }
  scanf("%d", &k);
  for (int i = 1, x; i <= k; i++) {
    scanf("%d", que + i);
    key[que[i]] = 1;
  }
  predfs(0);
  stk.push_back(1e9);
  dfs(0, n + 1);
  for (int i = 1; i <= k; i++) {
    printf("%d\n", cost[que[i]]);
  }
  return 0;
}