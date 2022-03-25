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

int n, a[maxn], pos[maxn], vis[maxn];

struct Bit {
  int a[maxn];
  void update(int i) {
    for (; i <= n + 1; i += i & -i) a[i]++;
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
  int query(int l, int r) {
    if (l > r) return 0;
    return query(r) - query(l - 1);
  }
} f;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    pos[a[i]] = i;
    // if (a[i] == i) {
    //   puts("-1");
    //   return 0;
    // }
  }
  vector<int> ans;
  for (int i = 1; i <= n; i++) {
    int rpos = pos[i] + f.query(pos[i] + 1, n);
    assert(rpos >= i);
    if (rpos > i) {
      while (rpos > i) {
        if (vis[rpos - 1]) {
          puts("-1");
          return 0;
        }
        ans.push_back(rpos - 1);
        vis[rpos - 1] = 1;
        rpos--;
      }
    }
    f.update(pos[i]);
  }
  if (ans.size() != n - 1) {
    puts("-1");
  } else {
    for (int i = 0; i < n - 1; i++) {
      printf("%d\n", ans[i]);
    }
  }
  return 0;
}