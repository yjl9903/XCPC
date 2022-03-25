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
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    vector<int> v;
    for (int i = 1; i <= n; i++) {
      if (a[i] != -1) {
        if (i > 1 && a[i - 1] == -1) {
          v.push_back(a[i]);
        } else if (i < n && a[i + 1] == -1) {
          v.push_back(a[i]);
        }
      }
    }
    sort(begin(v), end(v));
    int k = 0, mx = 0;
    if (!v.empty()) {
      if ((int)v.size() == 1) {
        k = v.front();
      } else {
        k = (v.front() + v.back()) / 2;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (a[i] == -1) {
        a[i] = k;
      }
      if (i > 1) {
        mx = max(mx, abs(a[i] - a[i - 1]));
      }
    }
    printf("%d %d\n", mx, k);
  }
  return 0;
}