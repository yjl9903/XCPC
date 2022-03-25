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

int n, m, tag[maxn];
vector<int> edge[maxn];

bool flag = true;
int cnt[3];
void dfs(int u) {
  cnt[tag[u]]++;
  for (int v: edge[u]) {
    if (tag[v]) {
      if ((tag[u] ^ tag[v]) != 3) {
        flag = false;
      }
    } else {
      tag[v] = tag[u] ^ 3;
      dfs(v);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (tag[i]) continue;
    cnt[1] = cnt[2] = 0;
    tag[i] = 1;
    dfs(i);
    ans += min(cnt[1], cnt[2]);
  }
  if (flag) {
    printf("%d\n", ans);
  } else {
    puts("Impossible");
  }
  return 0;
}