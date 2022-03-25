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

int k, L, ans[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &k, &L);
    if (L >= 2000) {
      puts("-1"); continue;
    }
    ans[1] = -1; int sum = k + 1999;
    for (int i = 2; i <= 1999; i++) {
      ans[i] = min((int)1e6, sum);
      sum -= ans[i];
    }
    if (sum) {
      puts("-1"); continue;
    }
    puts("1999");
    for (int i = 1; i <= 1999; i++) printf("%d ", ans[i]);
    puts("");
  }
  return 0;
}