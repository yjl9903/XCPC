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
const int maxn = 200000 + 5;

int n, m, key[maxn], ans, dis[maxn], cnt[maxn];
vector<int> edge[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) dis[i] = inf;
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  queue<int> q;
  for (int i = 1, x; i <= m; i++) { 
    scanf("%d", &x);
    cnt[x] = 1; dis[x] = 0;
    q.push(x);
  }
  while (!q.empty()) {
    int u = q.front(); q.pop();
    if (cnt[u] == m) {
      puts("YES"); printf("%d\n", u);
      return 0;
    }
    for (int v: edge[u]) {
      if (dis[v] == inf) {
        dis[v] = dis[u] + 1;
        cnt[v] = cnt[u];
        q.push(v);
      } else if (dis[v] == dis[u] + 1) {
        cnt[v] += cnt[u];
      }
    }
  }
  puts("NO");
  return 0;
}