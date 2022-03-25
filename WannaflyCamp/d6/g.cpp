#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100 + 5;

vector<int> edge[maxn];
int n, m, a[maxn], cnt, vis[maxn];

void dfs(int u) {
    cnt++; vis[u] = 1;
    for (int& v: edge[u]) {
        if (vis[v]) continue;
        dfs(v);
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int k = 0, x, y; scanf("%d%d", &k, &x);
        for (int i = 1; i < k; i++) {
            scanf("%d", &y);
            edge[y].push_back(x);
            x = y;
        }
    }
    int ans = n;
    for (int i = 1; i <= n; i++) {
        ms(vis, 0); cnt = 0;
        dfs(i);
        ans = min(ans, cnt);
    }
    cout << ans << endl;
    return 0;
}