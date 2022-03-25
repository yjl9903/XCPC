#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
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
const int maxn = 5000 + 5;

inline int add(int x, int y) {
    x += y;
    return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
    x -= y;
    return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
    return 1ll * x * y % mod;
}

int n, m, a[maxn], b[maxn];
int dp[maxn][maxn], cnta[maxn], cntb[maxn];
int pre[maxn][maxn], suf[maxn][maxn];

void solve(int n, int a[], int cnt[]) {
    vector<int> last(101, 0);
    dp[1][1] = 1; last[a[1]] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i][1] = dp[i - 1][1];
        if (!last[a[i]]) dp[i][1] = add(dp[i][1], 1);
        for (int j = 2; j <= i; j++) {
            dp[i][j] = add(dp[i - 1][j], dp[i - 1][j - 1]);
            if (last[a[i]]) {
                dp[i][j] = sub(dp[i][j], dp[last[a[i]] - 1][j - 1]);
            }
        }
        last[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) cnt[i] = dp[n][i];
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= m; i++) scanf("%d", b + i);

    solve(n, a, cnta); solve(m, b, cntb);
    int ans = 0;
    for (int i = 2; i <= n; i++) cntb[i] = add(cntb[i], cntb[i - 1]);
    for (int i = 1; i <= n; i++) ans = add(ans, mul(cnta[i], cntb[i - 1]));
    
    dp[0][0] = pre[0][0] = 1;
    for (int i = 1; i <= n; i++) pre[i][0] = 1;
    for (int j = 1; j <= m; j++) pre[0][j] = 1;
    vector<int> lasta(101, 0);
    for (int i = 1; i <= n; i++) {
        vector<int> lastb(101, 0);
        for (int j = 1; j <= m; j++) {
            pre[i][j] = sub(add(pre[i][j - 1], pre[i - 1][j]), pre[i - 1][j - 1]);
            if (a[i] != b[j]) {
                dp[i][j] = 0;
            } else {
                int posa = lasta[a[i]], posb = lastb[b[j]];
                dp[i][j] = pre[i - 1][j - 1];
                if (posa) dp[i][j] = sub(dp[i][j], pre[posa - 1][j - 1]);
                if (posb) dp[i][j] = sub(dp[i][j], pre[i - 1][posb - 1]);
                if (posa && posb) dp[i][j] = add(dp[i][j], pre[posa - 1][posb - 1]);
            }
            pre[i][j] = add(pre[i][j], dp[i][j]);
            lastb[b[j]] = j;
        }
        lasta[a[i]] = i;
    }

    dp[n + 1][m + 1] = suf[n + 1][m + 1] = 1;
    for (int i = 1; i <= n; i++) suf[i][m + 1] = 1;
    for (int j = 1; j <= m; j++) suf[n + 1][j] = 1;
    lasta.assign(101, n + 1);
    for (int i = n; i >= 1; i--) {
        vector<int> lastb(101, m + 1);
        for (int j = m; j >= 1; j--) {
            suf[i][j] = sub(add(suf[i][j + 1], suf[i + 1][j]), suf[i + 1][j + 1]);
            int posa = lasta[a[i]] + 1, posb = lastb[b[j]] + 1;
            dp[i][j] = sub(add(suf[i + 1][j + 1], suf[posa][posb]), add(suf[i + 1][posb], suf[posa][j + 1]));
            suf[i][j] = add(suf[i][j], dp[i][j]);
            lastb[b[j]] = j;
        }
        lasta[a[i]] = i;
    }

    lasta.assign(101, 0);
    for (int i = 1; i <= n; i++) {
        vector<int> lastb(101, 0);
        for (int j = 1; j <= m; j++) {
            if (a[i] <= b[j]) continue;
            int posa = lasta[a[i]], posb = lastb[b[j]];
            int tot = pre[i - 1][j - 1];
            if (posa) tot = sub(tot, pre[posa - 1][j - 1]);
            if (posb) tot = sub(tot, pre[i - 1][posb - 1]);
            if (posa && posb) tot = add(tot, pre[posa - 1][posb - 1]);
            ans = add(ans, mul(tot, suf[i + 1][j + 1]));
            lastb[b[j]] = j;
        }
        lasta[a[i]] = i;
    }
    cout << ans << '\n';
    }
    return 0;
}