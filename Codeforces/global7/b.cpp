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

int n, b[maxn];
ll a[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i);
  }
  a[1] = b[1];
  ll mx = a[1];
  for (int i = 2; i <= n; i++) {
    a[i] = b[i] + mx;
    mx = max(mx, a[i]);
  }
  for (int i = 1; i <= n; i++) {
    printf("%I64d ", a[i]);
  }
  puts("");
  return 0;
}