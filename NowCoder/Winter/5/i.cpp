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

int n, m, a[maxn];

int main() {
  scanf("%d%d", &n, &m);
  vector<PII> v;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    v.push_back({a[i], i});
  }
  sort(begin(v), end(v), greater<PII>());
  if (a[9] * 5 >= 4 * m) {
    puts("Yes");
  } else if (v[0].second == 9 || v[1].second == 9 || v[2].second == 9) {
    puts("Yes");
  } else {
    puts("No");
  }
  return 0;
}