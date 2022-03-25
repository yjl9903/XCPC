#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 200000 + 5;

vector<int> edge[maxn];
int n, a[maxn];

ll sum[maxn], tot = 0, ans = 0;
void dfs1(int u, int f, int d) {
    tot += 1ll * d * a[u];
    sum[u] = a[u];
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs1(v, u, d + 1);
        sum[u] += sum[v];
    }
}
void dfs2(int u, int f, ll r) {
    ans = max(ans, r);
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs2(v, u, r + sum[1] - 2ll * sum[v]);
    }
}

int main(){
    scanf("%d", &n); 
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs1(1, 0, 0); dfs2(1, 0, tot);
    cout << ans;
    return 0;
}