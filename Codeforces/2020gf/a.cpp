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

int n, a[maxn], b[maxn], c[maxn];

bool ok = false;
vector<int> ans, res;
void dfs(int i) {
  if (ok) return ;
  if (i == n + 1) {
    if (ans.back() != ans.front()) {
      ok = true;
      res = ans;
    }
    return ;
  }
  if (ans.empty() || a[i] != ans.back()) {
    ans.push_back(a[i]);
    dfs(i + 1);
    ans.pop_back();
  }
  if (ans.empty() || b[i] != ans.back()) {
    ans.push_back(b[i]);
    dfs(i + 1);
    ans.pop_back();
  }
  if (ans.empty() || c[i] != ans.back()) {
    ans.push_back(c[i]);
    dfs(i + 1);
    ans.pop_back();
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", b + i);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", c + i);
    }
    ans.clear();
    res.clear();
    ok = false;
    dfs(1);
    assert(ok);
    for (int x: res) printf("%d ", x);
    puts("");
  }
  return 0;
}