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
const int maxn = 1000 + 5;

int n, m, q, vis[maxn][maxn];

int check(int x, int y) {
    if (vis[x][y] || vis[x + 1][y] || vis[x][y + 1] || vis[x + 1][y + 1]) return 0;
    return 1;
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    int ans = (n - 1) * (m - 1);
    for (int i = 1, x, y; i <= q; i++) {
        scanf("%d%d", &x, &y);
        if (x > 1 && y > 1) {
            if (check(x - 1, y - 1)) ans--;
        }
        if (x > 1 && y < m) {
            if (check(x - 1, y)) ans--;
        }
        if (x < n && y > 1) {
            if (check(x, y - 1)) ans--;
        }
        if (x < n && y < m) {
            if (check(x, y)) ans--;
        }
        vis[x][y] = 1;
        printf("%d\n", ans);
    }
    return 0;
}