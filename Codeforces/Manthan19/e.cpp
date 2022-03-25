#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>
#include <functional>
#include <cassert>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, w;
ll ans[maxn];

int dp[21][maxn];
void solve(const vector<int>& a) {
    int n = (int)a.size();
    if (n == w) {
        for (int i = 0; i < w; i++) {
            ans[i] += a[i];
            ans[i + 1] -= a[i];
        }
        return ;
    }
    for (int i = 0; i < n; i++) dp[0][i] = i;
    for (int j = 1; j <= 20; j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
            int l = dp[j - 1][i];
            int r = dp[j - 1][i + (1 << (j - 1))];
            if (a[l] > a[r]) dp[j][i] = l;
            else dp[j][i] = r;
        }
    }
    auto qmax = [&](int l, int r) -> int {
        int k = __lg(r - l + 1);
        int x = dp[k][l], y = dp[k][r - (1 << k) + 1];
        if (a[x] > a[y]) return x;
        else return y;
    };
    for (int i = 0; i < w; i++) {
        int l = max(i - w + n, 0);
        int r = min(i, n - 1);
        assert(l <= r);
        int mx = a[qmax(l, r)];
        if (mx < 0 && (i >= n || i < w - n)) {
            mx = 0;
        }
        ans[i] += mx;
        if (l == 0 && r == n - 1 && i >= n && w >= 2 * n + 1) {
            i = max(i, w - 1 - n);
        }
        ans[i + 1] -= mx;
    }
}

int main() {
    scanf("%d%d", &n, &w);
    for (int i = 1, x, m; i <= n; i++) {
        scanf("%d", &m);
        vector<int> line;
        for (int j = 1; j <= m; j++) {
            scanf("%d", &x);
            line.push_back(x);
        }
        solve(line);
    }
    for (int i = 0; i < w; i++) printf("%I64d ", ans[i] += ans[i - 1]);
    return 0;
}