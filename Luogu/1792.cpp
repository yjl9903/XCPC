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
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, k, used[maxn], L[maxn], R[maxn];
ll a[maxn];

struct Node {
  int id; ll val;

  bool operator < (const Node& rhs) const {
    return val < rhs.val;
  }
};

int main() {
  scanf("%d%d", &n, &k);
  if (k + k > n) return puts("Error!"), 0;
  for (int i = 1; i <= n; i++) {
    scanf("%lld", a + i);
  }
  priority_queue<Node> pq;
  for (int i = 1; i <= n; i++) {
    L[i] = i - 1 >= 1 ? i - 1 : n;
    R[i] = i + 1 <= n ? i + 1 : 1;
    pq.push({ i, a[i] });
  }
  ll ans = 0;
  for (int i = 1; i <= k; i++) {
    while (used[pq.top().id]) pq.pop();
    auto x = pq.top();
    pq.pop();
    int u = x.id;
    ans += a[u];

    int nx = n + i + 1;
    used[L[u]] = used[R[u]] = true;
    a[nx] = a[L[u]] + a[R[u]] - a[u];
    L[R[R[u]]] = R[L[L[u]]] = nx;
    L[nx] = L[L[u]];
    R[nx] = R[R[u]];

    pq.push({ nx, a[nx] });
  }
  printf("%lld\n", ans);
  return 0;
}