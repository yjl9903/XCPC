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

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  vector<PII> vec;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (a[i] > a[j]) {
        vec.push_back({ i, j });
      }
    }
  }
  sort(begin(vec), end(vec), [&](PII lhs, PII rhs) {
    if (lhs.second != rhs.second) {
      return lhs.second > rhs.second;
    }
    if (a[lhs.first] != a[rhs.first]) {
      return a[lhs.first] < a[rhs.first];
    }
    return lhs.first < rhs.first;
  });
  printf("%d\n", vec.size());
  for (auto& x: vec) {
    printf("%d %d\n", x.first, x.second);
  }
  return 0;
}