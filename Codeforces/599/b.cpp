#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, m, ans, nxt[maxn], pre[maxn], tag[maxn];
vector<int> edge[maxn];

void bfs(int s) {
  int sum = 0;
  queue<int> q; q.push(s);
  while (!q.empty()) {
    sum++;
    int u = q.front(); q.pop();
    for (int v: edge[u]) tag[v] = u;
    for (int i = nxt[0]; i <= n; i = nxt[i]) {
      if (i != s && tag[i] != u) {
        q.push(i); 
        nxt[pre[i]] = nxt[i]; pre[nxt[i]] = pre[i];
      }
    }
  }
  ans++;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v; i <= m; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v); 
    edge[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    nxt[i] = i + 1; pre[i] = i - 1;
  }
  nxt[0] = 1; pre[n + 1] = n;
  for (int i = 1; i <= n; ) {
    bfs(i); int tmp = nxt[i];
    nxt[pre[i]] = nxt[i]; pre[nxt[i]] = pre[i];
    i = tmp;
  }
  cout << ans - 1;
  return 0;
}