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



int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  if (n > m) swap(n, m);
  int ans = (n - 1) * m + (m - 1);
  puts(ans % 2 ? "YES" : "NO");
  return 0;
}