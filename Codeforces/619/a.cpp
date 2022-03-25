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
const int maxn = 100000 + 5;

char a[maxn], b[maxn], c[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s%s%s", a, b, c);
    int n = strlen(a), flag = true;
    for (int i = 0; i < n; i++) {
      // if (a[i] == b[i]) continue;
      if (a[i] == c[i]) continue;
      if (b[i] == c[i]) continue;
      flag = false; break;
    }
    puts(flag ? "YES" : "NO");
  }
  return 0;
}