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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;
PII a[maxn];

ll cross(PII i, PII j, PII k) {
  PII a = {j.first - i.first, j.second - i.second};
  PII b = {k.first - i.first, k.second - i.second};
  return 1ll * a.first * b.second - 1ll * a.second * b.first;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
  }
  int op, i, j, k;
  while (cin >> op >> i >> j >> k) {
    if (op == 1) {
      cout << abs(cross(a[i], a[j], a[k])) << endl;
    } else if (op == 2) {
      ll x = cross(a[i], a[j], a[k]);
      if (x < 0) cout << -1 << endl;
      else if (x == 0) cout << 0 << endl;
      else cout << 1 << endl;
    }
  }
  return 0;
}