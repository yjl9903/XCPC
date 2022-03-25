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

int n;

bool check(int x) {
  vector<int> v;
  while (x) {
    v.push_back(x % 10);
    x /= 10;
  }
  reverse(begin(v), end(v));
  return is_sorted(begin(v), end(v));
}

int main() {
  scanf("%d", &n);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (check(i)) {
      ans++;
    }
  }
  printf("%d\n", ans);
  return 0;
}