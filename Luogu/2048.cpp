#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, k, L, R, a[maxn];

int dp[maxn][21];
void init() {
    for (int i = 1; i <= n; i++) dp[i][0] = i;
    for (int j = 1; j < 21; j++) {
        for (int i = 1; i + (1 << j) <= n + 1; i++) {
            int x = dp[i][j - 1], y = dp[i + (1 << (j - 1))][j - 1];
            dp[i][j] = a[x] > a[y] ? x : y;
        }
    }
}
int query(int l, int r) {
    int k = log2(r - l + 1);
    int x = dp[l][k], y = dp[r - (1 << k) + 1][k];
    return a[x] > a[y] ? x : y;
}

struct node {
    int o, l, r, t;
    node(int oo, int ll, int rr) {
        o = oo; l = ll; r = rr;
        t = query(l, r);
    }
    bool operator < (const node& b) const {
        return a[t] - a[o - 1] < a[b.t] - a[b.o - 1];
    }
};

int main() {
    scanf("%d%d%d%d", &n, &k, &L, &R);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), a[i] += a[i - 1];
    init();
    priority_queue<node> pq;
    for (int i = 1; i + L - 1 <= n; i++) {
        pq.push(node(i, i + L - 1, min(n, i + R - 1)));
    }
    ll ans = 0;
    while (k--) {
        node tp = pq.top(); pq.pop();
        ans += a[tp.t] - a[tp.o - 1];
        if (tp.l < tp.t) pq.push(node(tp.o, tp.l, tp.t - 1));
        if (tp.t < tp.r) pq.push(node(tp.o, tp.t + 1, tp.r));
    }
    cout << ans << endl;
    return 0;
}