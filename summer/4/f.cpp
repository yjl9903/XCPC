#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
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
const int maxn = 10 + 5;

int n, m, a[maxn];
vector<int> sta;

int sz, cnt[maxn], k, tot;
int dfs(int now, int use) {
    int ok = 0;
    for (int i = 0; i < n; i++) {
        if (cnt[i] == k) ok++;
    }
    if (ok == n) {
        tot = min(use, tot);
        return 1;
    }
    if (now == sz) {
        return 0;
    }
    if (use >= tot) return 0;
    // dfs(now + 1, use);
    int s = sta[now], turn = 0;
    while (true) {
        int flag = 1;
        for (int i = 0; i < n; i++) if (s & (1 << i)) {
            cnt[i]++; if (cnt[i] > k) flag = 0;
        }
        turn++;
        if (flag) dfs(now + 1, use + turn);
        else break;
    }
    // dbg(s, now, use);
    // if (flag && dfs(now + 1, use + 1)) return 1;
    for (int i = 0; i < n; i++) if (s & (1 << i)) cnt[i] -= turn;
    // if (dfs(now + 1, use)) return 1;
    dfs(now + 1, use);
    return 0;
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        int mx = 0, sum = 0;
        for (int i = 0; i < n; i++) scanf("%d", a + i), mx = max(mx, a[i]), sum += a[i];
        printf("Case #%d: ", ++kase);
        if (sum <= m) {
            puts("1.0000000000"); continue;
        } else if (mx > m) {
            puts("0.0000000000"); continue;
        }
        int ss = 1 << n; sta.clear();
        for (int s = 1; s < ss; s++) {
            int sum = 0;
            for (int i = 0; i < n; i++) if (s & (1 << i)) sum += a[i];
            if (sum <= m) sta.push_back(s);
        }
        // for (int s: sta) dbg(s);
        sz = (int)sta.size();
        double ans = 0;
        for (k = 1; k <= n; k++) {
            tot = 10000000; ms(cnt, 0);
            dfs(0, 0);
            // dbg(k, tot);
            ans = max(ans, 1.0 * k / tot);
        }
        printf("%.8lf\n", ans);
    }
    return 0;
}