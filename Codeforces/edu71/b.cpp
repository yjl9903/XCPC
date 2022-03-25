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
const int maxn = 100 + 5;

int n, m, mp[maxn][maxn], vis[maxn][maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &mp[i][j]);
        }
    }
    vector<PII> ans;
    for (int i = 1; i + 1 <= n; i++) {
        for (int j = 1; j + 1 <= m; j++) {
            if (mp[i][j] && mp[i + 1][j] && mp[i][j + 1] && mp[i + 1][j + 1]) {
                ans.push_back({i, j});
                vis[i][j] = vis[i + 1][j] = vis[i][j + 1] = vis[i + 1][j + 1] = 1;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j]) {
                if (!vis[i][j]) return puts("-1"), 0;
            }
        }
    }
    printf("%d\n", (int)ans.size());
    for (auto x: ans) printf("%d %d\n", x.first, x.second);
    return 0;
}