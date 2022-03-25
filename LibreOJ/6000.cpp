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

int n, m, map[maxn][maxn];

int vis[maxn], nxt[maxn];
int dfs(int x) {
    for (int i = m + 1; i <= n; i++) {
        if (map[x][i] && !vis[i]) {
            vis[i] = 1;
            if (!nxt[i] || dfs(nxt[i])) {
                nxt[i] = x; return 1;
            }
        }
    }
    return 0;
}
int match() {
    int sum = 0;
    for (int i = 1; i <= m; i++) {
        ms(vis, 0);
        if (dfs(i)) sum++;
    }
    return sum;
}

int main(){
    scanf("%d%d", &n, &m);
    int u, v;
    while (scanf("%d%d", &u, &v) == 2) {
        map[u][v] = 1;
    }
    cout << match() << endl;
    return 0;
}