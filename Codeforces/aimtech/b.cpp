#include <cstdio>
#include <algorithm>
#include <utility>
#include <algorithm>
#include <map>
#include <queue>
#include <bitset>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 50000 + 1;

int n, m, vis[maxn], deg[maxn];

struct Edge {
  int to, nxt;
} e[maxn];
int ecnt, head[maxn];
void adde(int u, int v) {
  e[++ecnt] = { v, head[u] }; head[u] = ecnt;
}

ll ans = 0;

map<int,bitset<maxn> > go;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v; i <= m; i++) {
    scanf("%d%d", &u, &v);
    swap(u, v);
    adde(v, u);
    deg[u]++;
  }
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (deg[i] == 0) {
      q.push(i);
    }
  }
  while (!q.empty()) {
    int u = q.front(); q.pop();
    go[u].set(u - 1, true);
    ans += 1ll * go[u].count() * go[u].count();
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].to;
      go[v] |= go[u];
      deg[v]--;
      if (deg[v] == 0) {
        q.push(v);
      }
    }
    go.erase(u);
  }
  printf("%I64d\n", ans);
  return 0;
}