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

int n, a[maxn];
bool ok[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      ok[i] = a[i] == i;
    }
    int L = 1, R = n;
    while (L <= n && ok[L]) L++;
    while (R >= 1 && ok[R]) R--;
    if (L > R) {
      puts("0");
    } else {
      int cnt = 0;
      for (int i = L; i <= R; i++) {
        cnt += !ok[i];
      }
      assert(cnt > 0);
      if (cnt == R - L + 1) {
        puts("1");
      } else {
        puts("2");
      }
    }
  }
  return 0;
}