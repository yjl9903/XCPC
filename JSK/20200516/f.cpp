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

int n, k, a[maxn];

int main() {
  scanf("%d%d", &n, &k);
  vector<int> vec;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    vec.push_back(a[i]);
  }
  int ans = 0;
  for (int j = 30; j >= 0; j--) {
    vector<int> nx;
    for (auto& x: vec) {
      if (x & (1 << j)) {
        nx.push_back(x);
      }
    }
    if ((int)nx.size() >= k) {
      ans |= 1 << j;
      vec = nx;
    }
  }
  printf("%d\n", ans);
  return 0;
}