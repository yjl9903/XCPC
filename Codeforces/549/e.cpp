#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, m, q, p[maxn], a[maxn];
int dp[maxn][25], ed[maxn], pos[maxn], mp[maxn], rt[maxn];

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) scanf("%d", p + i), pos[p[i]] = i;
    for (int i = 1; i <= m; i++) scanf("%d", a + i);
    for (int i = m; i >= 1; i--) {
        int v = pos[a[i]] + 1; if (v == n + 1) v = 1;
        if (mp[p[v]]) {
            dp[i][0] = mp[p[v]];
        }
        // dbg(i, dp[i][0]);
        mp[a[i]] = i;
    }
    for (int l = 1; l <= 20; l++) {
        for (int i = 1; i <= m; i++) {
            dp[i][l] = dp[dp[i][l - 1]][l - 1];
        }
    }
    for (int i = 1; i <= m; i++) {
        int x = i;
        for (int j = 0; j <= 20; j++) {
            if ((n - 1) & (1 << j)) x = dp[x][j];
        }
        ed[i] = x;
    }
    for (int i = m; i >= 1; i--) {
        if (!ed[i]) {
            rt[i] = rt[i + 1];
        } else {
            if (rt[i + 1]) rt[i] = min(rt[i + 1], ed[i]);
            else rt[i] = ed[i];
        }
        dbg(i, ed[i], rt[i]);
    }
    int l, r;
    while (q--) {
        scanf("%d%d", &l, &r);
        if (r - l + 1 < n || !rt[l]) {
            putchar('0'); continue;
        }
        if (rt[l] <= r) putchar('1');
        else putchar('0');
    }
    return 0;
} 