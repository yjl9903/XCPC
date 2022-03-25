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

int n, m, q;

int pre[maxn * 2], cnt[maxn * 2];
int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
  pre[find(x)] = find(y);
}
set<PII> egs;
int solve() {
  for (int i = 1; i <= n + m; i++) {
    pre[i] = i;
    cnt[i] = 0;
  }
  int sum = 0;
  for (auto& e: egs) {
    if (cnt[e.second] == 0) sum++;
    cnt[e.second]++;
    join(e.first, e.second);
  }
  if (sum < m) return -1;
  int ans = 0;
  for (int i = 1; i <= n + m; i++) {
    if (pre[i] == i) {
      ans++;
    }
  }
  return ans;
}

int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= n; i++) {
    int k, x;
    scanf("%d", &k);
    while (k--) {
      scanf("%d", &x);
      egs.emplace(i, x + n);
    }
  }
  for (int i = 1; i <= q; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    PII e = make_pair(y, x + n);
    if (egs.count(e)) {
      egs.erase(e);
    } else {
      egs.insert(e);
    }
    printf("%d\n", solve());
  }
  return 0;
}