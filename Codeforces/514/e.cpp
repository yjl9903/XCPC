#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

vector<int> edge[maxn];
int n, l, w[maxn], ans, dep[maxn], tot, top[maxn], id[maxn], path[maxn];
ll s, pre[maxn];

int get(int u, int d) {
    int l = max(1, d - ::l + 1), r = d, ans = u;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (pre[d] - pre[m - 1] <= s) r = m - 1, ans = id[m];
        else l = m + 1;
    }
    return ans;
}
void dfs(int u, int f) {
    dep[u] = dep[f] + 1;
    tot++; pre[tot] = pre[tot - 1] + w[u]; id[tot] = u;
    top[u] = get(u, tot);
    for (int& v: edge[u]) {
        dfs(v, u);
    }
    tot--;
}
int dfs(int u) {
    int r = -1;
    for (int& v: edge[u]) {
        int t = dfs(v);
        if (t == v) continue;
        if (r == -1 || dep[t] < dep[r]) r = t;
    }
    if (r != -1) return r;
    ans++;
    return top[u];
}

int main() {
    scanf("%d%d%I64d", &n, &l, &s); 
    for (int i = 1; i <= n; i++) {
        scanf("%d", w + i);
        if (w[i] > s) return puts("-1"), 0;
    }
    for (int i = 2, x; i <= n; i++) scanf("%d", &x), edge[x].push_back(i);
    dfs(1, 0); dfs(1);
    cout << ans << endl;
    return 0;
}