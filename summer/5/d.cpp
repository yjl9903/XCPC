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
const int mod = 105225319;
const int inf = 1 << 30;
const int maxn = 2000 + 5;

void add(int& x, int y) {
    x += y; if (x >= mod) x -= mod;
}

int n, l[maxn], r[maxn], dp[maxn][maxn];
vector<int> bag[maxn];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) bag[i].clear();
        for (int i = 1; i <= n; i++) scanf("%d", l + i);
        for (int i = 1; i <= n; i++) scanf("%d", r + i);
        int good = n;
        for (int i = 1; i <= n; i++) {
            if (r[i] - l[i] + 1 == n) continue;
            good--;
            for (int j = l[i]; j <= r[i]; j++) {
                bag[j].push_back(i);
            }
        }
        printf("Case #%d: ", ++kase);
        int flag = 0;
        for (int i = 1; i <= n; i++) if ((int)bag[i].size() > 10) flag = 1;
        if (flag) {
            puts("0"); continue;
        }
        ms(dp, 0); dp[0][0] = 1;
        for (int i = 0; i < n; i++) {
            int ss = 1 << (int)bag[i].size();
            vector<int> f(15, -1), g(15, -1);
            for (int j = 0; j < (int)bag[i].size(); j++) {
                for (int k = 0; k < (int)bag[i + 1].size(); k++) {
                    if (bag[i][j] == bag[i + 1][k]) {
                        f[j] = k;
                    }
                }
            }
            for (int j = 0; j < (int)bag[i + 1].size(); j++) {
                for (int k = 0; k < (int)bag[i].size(); k++) {
                    if (bag[i + 1][j] == bag[i][k]) {
                        g[j] = k;
                    }
                }
            }
            auto get = [&](int x, int s) -> int {
                int ans = 0;
                for (int i = 0; i < (int)bag[x].size(); i++) {
                    if (f[i] == -1) {
                        if (s & (1 << i)) ;
                        else return -1;
                    } else if (s & (1 << i)) {
                        ans |= 1 << f[i];
                    }
                }
                return ans;
            };
            for (int s = 0; s < ss; s++) {
                int nx = get(i, s);
                if (nx == -1) continue;
                if (good) add(dp[i + 1][nx], dp[i][s]);
                for (int j = 0; j < (int)bag[i + 1].size(); j++) {
                    if (g[j] == -1) add(dp[i + 1][nx | (1 << j)], dp[i][s]);
                    else if ((s >> g[j] & 1) == 0) add(dp[i + 1][nx | (1 << j)], dp[i][s]);
                }
            }
        }
        int ans = dp[n][(1 << (int)bag[n].size()) - 1];
        for (int i = 1; i <= good; i++) ans = 1ll * ans * i % mod;
        printf("%d\n", ans);
    }
    return 0;
}