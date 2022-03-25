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
const int maxn = 400000 + 5;

int n, a[maxn], b[maxn], c[maxn];

void update(int i, int x = 1) {
  for (; i < maxn; i += i & -i) c[i] += x;
}
int query(int i) {
  int r = 0;
  for (; i; i -= i & -i) r += c[i];
  return r;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i);
  }
  vector<ll> lsh;
  for (int i = 1; i <= n; i++) {
    lsh.push_back(b[i] - a[i]);
    lsh.push_back(a[i] - b[i] - 1);
  }
  sort(begin(lsh), end(lsh));
  lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
  auto gid = [&](int x) {
    return lower_bound(begin(lsh), end(lsh), x) - begin(lsh) + 1;
  };
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += query(gid(a[i] - b[i] - 1));
    update(gid(b[i] - a[i]));
  }
  cout << ans << endl;
  return 0;
}