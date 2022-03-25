#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, m, a[maxn], p[maxn], s[maxn], mxd[maxn];

int dp[20][maxn], f[maxn];
void build(int n, int a[]) {
  for (int i = 1; i <= n; i++) dp[0][i] = a[i];
  for (int j = 1; j < 20; j++)
    for (int i = 1; i + (1 << j) <= n + 1; i++)
      dp[j][i] = max(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
}
int qmax(int l, int r){
  int k = __lg(r - l + 1);
  return max(dp[k][l], dp[k][r - (1 << k) + 1]);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    vector<int> lsh;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      lsh.push_back(a[i]);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
      scanf("%d%d", p + i, s + i);
      lsh.push_back(p[i]);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    int nn = (int)lsh.size();
    for (int i = 1; i <= n; i++) {
      a[i] = lower_bound(lsh.begin(), lsh.end(), a[i]) - lsh.begin() + 1;
    }
    build(n, a);
    for (int i = 1; i <= m; i++) {
      p[i] = lower_bound(lsh.begin(), lsh.end(), p[i]) - lsh.begin() + 1;
    }
    for (int i = 1; i <= nn; i++) mxd[i] = 0;
    for (int i = 1; i <= m; i++) mxd[p[i]] = max(mxd[p[i]], s[i]);
    for (int i = nn - 1; i >= 1; i--) mxd[i] = max(mxd[i + 1], mxd[i]);
    bool flag = false;
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
      int l = 1, r = i, from = -1;
      auto check = [&](int x) -> bool {
        int p = qmax(x, i);
        if (mxd[p] >= i - x + 1) return true;
        return false;
      };
      while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) from = m, r = m - 1;
        else l = m + 1;
      }
      if (from == -1) {
        flag = true; break;
      }
      f[i] = f[from - 1] + 1;
    }
    if (flag) puts("-1");
    else printf("%d\n", f[n]);
  }
  return 0;
}