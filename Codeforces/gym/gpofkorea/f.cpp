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
const int maxn = 300000 + 5;

int n, a[maxn];

int main() {
  scanf("%d", &n);
  vector<int> stk;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    while (!stk.empty() && a[i] < a[stk.back()]) {
      ans = max(ans, min(a[stk.back()], i - stk.back()));
      ans = max(ans, min(a[i], i + 1 - stk.back()));
      stk.pop_back();
    }
    stk.push_back(i);
  }
  while (!stk.empty()) {
    ans = max(ans, min(a[stk.back()], n + 1 - stk.back()));
    stk.pop_back();
  }
  printf("%d\n", ans);
  return 0;
}