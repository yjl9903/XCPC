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

int n, m, q, a[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  scanf("%d", &q);
  while (q--) {
    int p, x;
    scanf("%d%d", &p, &x);
    a[p] = x;
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= m - n + i; j++) {
        for (int k = 1; j - k >= i - 1; k++) {

        }
      }
    }
  }
  return 0;
}