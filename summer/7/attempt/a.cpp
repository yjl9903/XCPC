#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int p, c[20], w[] = { 0, 1, 5, 10, 20, 50, 100, 200, 500, 1000, 2000 };
ll suf[20];

int ans;
void dfs(int now, int cnt, int val) {
    if (val > p) return ;
    if (val == p) {
        ans = max(ans, cnt);
        return ;
    }
    if (val + suf[now] < p) return ;
    if (now == 11) {
        return ;
    }
    for (int i = c[now]; i >= 0; i--) {
        if (val + 1ll * i * w[now] > p) continue;
        dfs(now + 1, cnt + i, val + i * w[now]);
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &p);
        ll sum = 0;
        for (int i = 1; i <= 10; i++) scanf("%d", c + i), sum += 1ll * c[i] * w[i];
        suf[11] = 0;
        for (int i = 10; i >= 1; i--) suf[i] = suf[i + 1] + 1ll * c[i] * w[i];
        if (sum < p) {
            puts("-1"); continue;
        }
        if (p % 10 > c[1]) {
            puts("-1"); continue;
        }
        ans = 0;
        dfs(1, 0, 0);
        printf("%d\n", ans);
    }
    return 0;
}