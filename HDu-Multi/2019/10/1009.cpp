#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 3000 + 5;

int n, m, q, ans = 0;
int st[maxn][maxn];

void dfs(int x, int y) {
    if (!st[x][y]) return ;
    int r = st[x + 1][y] + st[x - 1][y];
    int c = st[x][y + 1] + st[x][y - 1];

    if (x == 1) r++;
    if (x == n) r++;
    if (y == 1) c++;
    if (y == m) c++;

    if (r >= 2 || c >= 2) return ;
    ans++; st[x][y] = 0;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        ms(st, 0);
        scanf("%d%d%d", &n, &m, &q);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                st[i][j] = 1;
            }
        }
        int x, y;
        while (q--) {
            scanf("%d%d", &x, &y);
            if (st[x][y]) {
                ans = 1; st[x][y] = 0;
                dfs(x + 1, y);
                dfs(x - 1, y);
                dfs(x, y + 1);
                dfs(x, y - 1);
                printf("%d\n", ans);
            } else puts("0");
        }
    }
    return 0;
}