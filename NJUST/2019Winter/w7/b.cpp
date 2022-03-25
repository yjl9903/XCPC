#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100 + 5;

int n, m, a[maxn], b[maxn];

int vis[maxn], nxt[maxn];
int dfs(int u) {
    for (int i = 1; i <= m; i++) {
        if (vis[i]) continue;
        if (abs(a[u] - b[i]) > 1) continue;
        vis[i] = 1;
        if (!nxt[i] || dfs(nxt[i])) {
            nxt[i] = u; return 1;
        }
    }
    return 0;
}
int match() {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        ms(vis, 0);
        if (dfs(i)) sum++;
    }
    return sum;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) scanf("%d", b + i);
    cout << match() << endl;
    return 0;
}