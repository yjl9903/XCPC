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
const int maxn = 500000 + 5;

int n, k, m, deg[maxn];
vector<int> edge[maxn];
int c[maxn], cnt[maxn], ans[maxn];

int main() {
  scanf("%d%d%d", &n, &k, &m);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    deg[v]++;
  }
  for (int i = 1; i <= n * k; i++) {
    scanf("%d", c + i);
    cnt[c[i]]++;
    printf("%d ", cnt[c[i]]);
  }
  
  return 0;
}