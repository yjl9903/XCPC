#include <bits/stdc++.h>
using namespace std;
using PII = pair<int,int>;
using ll = long long;
const int maxn = 100000 + 5;

int n, q;
map<int,int> port[maxn];

ll cal() {
  ll ans = 0;
  // cout << "?" << endl;
  for (int i = 1; i <= n; i++) {
    int x = i, y = 0;
    while (true) {
      auto it = port[x].lower_bound(y);
      if (it == port[x].end()) break;
      y = it->first + 1;
      x = it->second;
    }
    ans += 1ll * i * x;
    // cout << i << ' ' << x << endl;
  }
  return ans;
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= q; i++) {
    char op[4];
    int x1, x2, y;
    scanf("%s%d%d%d", op, &x1, &x2, &y);
    if (op[0] == '+') {
      port[x1][y] = x2;
      port[x2][y] = x1;
    } else if (op[0] == '-') {
      port[x1].erase(y);
      port[x2].erase(y);
    }
    printf("%lld\n", cal());
  }
  return 0;
}