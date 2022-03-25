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
const int maxn = 50 + 5;

int n, m, c[maxn][maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        int ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                scanf("%d", &c[i][j]); 
                if (c[i][j]) ans++;
            }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
            if (c[i][j] >= c[i - 1][j]) ans += c[i][j] - c[i - 1][j];
            if (c[i][j] >= c[i][j - 1]) ans += c[i][j] - c[i][j - 1];
            if (c[i][j] >= c[i + 1][j]) ans += c[i][j] - c[i + 1][j];
            if (c[i][j] >= c[i][j + 1]) ans += c[i][j] - c[i][j + 1];
        }
        printf("%d\n", ans);
        ms(c, 0);
    }
    return 0;
}