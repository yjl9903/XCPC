#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 100000 + 5;

int n, m, A, B;
vector<int> edge[maxn];

set<int> reach;
ll f[maxn];
ll dfs(int u) {
  if (f[u] != -1) return f[u];
  ll ans = u == B;
  if (edge[u].empty()) {
    reach.insert(u);
    return f[u] = ans;
  }
  if (u == B) {
    return f[u] = ans;
  }
  for (int v: edge[u]) {
    ans += dfs(v);
  }
  return f[u] = ans;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i <= n; i++) {
    f[i] = -1;
  }
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
  }
  scanf("%d%d", &A, &B);
  ll ans = dfs(A);
  printf("%lld ", ans);
  if (reach.size() == 1 && *reach.begin() == B && edge[B].empty()) {
    puts("Yes");
  } else {
    puts("No");
  }
  return 0;
}