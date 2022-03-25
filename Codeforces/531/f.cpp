#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 200000 + 5;

int n, m, a[20][10000 + 10], vis[30], lk[30][30], ck[30][30];
vector<int> edge[20];

int s, tag, mask[maxn][20];
int dfs(int u, int cnt, int mk) {
    if (cnt == n) {
        if (ck[s][u] < tag) return 0;
        return 1;
    }
    mk |= (1 << u);
    if (mask[mk][u] == s) return 0;
    for (int& v: edge[u]) {
        if (vis[v]) continue;
        vis[v] = 1;
        if (dfs(v, cnt + 1, mk)) return 1;
        vis[v] = 0;
    }
    mask[mk][u] = s;
    return 0;
}
int check(int x) {
    tag = x;
    for (int i = 1; i <= n; i++) edge[i].clear();
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (lk[i][j] >= x) {
                edge[i].push_back(j);
                edge[j].push_back(i);
            }
        }
    }
    ms(vis, 0); ms(mask, 0);
    for (int i = 1; i <= n; i++) {
        s = i; vis[s] = 1;
        if (dfs(s, 1, 0)) return 1;
        vis[s] = 0;
    }
    return 0;
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
        int mn = 1e9;
        for (int k = 1; k <= m ; k++) {
            mn = min(mn, abs(a[i][k] - a[j][k]));
        }
        lk[i][j] = mn;
    }
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
        int mn = 1e9;
        for (int k = 2; k <= m; k++) {
            mn = min(mn, abs(a[i][k] - a[j][k - 1]));
        }
        ck[i][j] = mn;
    }
    int l = 0, r = 1e9, ans = 0;
    while (l <= r) {
        int m = l + r >> 1;
        if (check(m)) l = m + 1, ans = m;
        else r = m - 1;
    }
    cout << ans;
    return 0;
}