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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 2000 + 5;

int n, m, r, ans, vis[maxn];
int planA[maxn], planB[maxn][maxn];
int x[maxn], y[maxn], val[maxn], cnt[maxn];

vector<int> stk;
void dfs(int i) {
  if (stk.size() == m) {
    int sum = 0;
    ms(vis, 0);
    for (int j: stk) {
      for (int i = 1; i <= n; i++) {
        if (max(abs(x[i] - x[j]), abs(y[i] - y[j])) <= r) {
          vis[i] = true;
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      if (vis[i]) {
        planA[i]++;
        sum += val[i];
      }
    }
    for (int i = 1; i <= n; i++) {
      if (vis[i]) {
        for (int j = 1; j <= n; j++) {
          if (vis[j]) {
            planB[i][j]++;
          }
        }
      }
    }
    ans = (ans + 1ll * sum * sum % mod) % mod;
    return ;
  }
  if (i == n + 1) return ;
  stk.push_back(i);
  dfs(i + 1);
  stk.pop_back();
  dfs(i + 1);
}

int main() {
  scanf("%d%d%d", &n, &m, &r);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d", x + i, y + i, val + i);
  }
  dfs(1);
  cout << ans << endl;
  for (int i = 1; i <= n; i++) {
    // cout << planA[i] << ' ';
    for (int j = i + 1; j <= n; j++) {
      cout << planB[i][j] << ' ';
    }
    cout << endl;
  }
  return 0;
}