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
const int maxn = 300000 + 5;

vector<int> edge[maxn];
int n, ans, a[maxn], cnt[3], siz[maxn][3];

void dfs(int u, int f) {
    siz[u][a[u]]++;
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
        if (siz[v][1] == 0 || siz[v][2] == 0) {
            if (cnt[1] - siz[v][1] == 0 || cnt[2] - siz[v][2] == 0) {
                ans++;
            }
        }
        siz[u][0] += siz[v][0];
        siz[u][1] += siz[v][1];
        siz[u][2] += siz[v][2];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), cnt[a[i]]++;
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1, 0);
    cout << ans << endl;
    return 0;
}