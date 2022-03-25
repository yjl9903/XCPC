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
    vector<int> pos;
    pos.push_back(1);
    for (int i = 1, j = 1; i <= n; i = j) {
      bool up = a[i + 1] > a[i];
      while (j <= n && up == (a[j + 1] > a[j])) j++;
      if (j <= n && i < j) {
        pos.push_back(j);
      }
    }
    if (pos.back() != n) pos.push_back(n);
    printf("%d\n", pos.size());
    for (int p: pos) {
      printf("%d ", a[p]);
    }
    puts("");
  }
  return 0;
}