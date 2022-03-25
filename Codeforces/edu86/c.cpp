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

int a, b, q, cnt[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &a, &b, &q);
    int per = 0;
    cnt[0] = 0;
    for (int i = 1; i <= a * b; i++) {
      cnt[i] = cnt[i - 1];
      if (i % a % b != i % b % a) {
        per++; cnt[i]++;
      }
    }
    auto solve = [&](ll x) -> ll {
      ll ans = x / (a * b) * per;
      x %= a * b;
      return ans + cnt[x];
    };
    for (int i = 1; i <= q; i++) {
      ll l, r;
      scanf("%I64d%I64d", &l, &r);
      printf("%I64d ", solve(r) - solve(l - 1));
    }
    puts("");
  }
  return 0;
}