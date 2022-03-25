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
const int maxn = 4000 + 5;

struct node {
    int x, y, w;
    bool operator<(const node& b) const {
        return x < b.x;
    }
} a[maxn];

int n, nn;
bool vis[maxn][maxn];
vector<int> line[maxn];

ll b[maxn];
void clear() {
    for (int i = 0; i <= nn; i++) b[i] = 0;
}
void update(int i, ll x) {
    for (; i <= nn; i += i & -i) b[i] += x;
}
ll query(int i) {
    ll r = 0;
    for (; i; i -= i & -i) r += b[i];
    return r;
}
ll query(int a, int b) {
    if (a < b) swap(a, b);
    return query(a) - query(b - 1);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        // ms(vis, 0);
        scanf("%d", &n);
        vector<int> lsh, lsh2;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].w);
            lsh2.push_back(a[i].x);
            lsh.push_back(a[i].y);
        }
        sort(lsh.begin(), lsh.end());
        lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
        nn = (int)lsh.size();
        sort(lsh2.begin(), lsh2.end());
        lsh2.resize(unique(lsh2.begin(), lsh2.end()) - lsh2.begin());
        int mm = (int)lsh2.size();
        for (int i = 0; i <= mm; i++) line[i].clear();
        for (int i = 1; i <= n; i++) {
            a[i].y = lower_bound(lsh.begin(), lsh.end(), a[i].y) - lsh.begin() + 1;
            a[i].x = lower_bound(lsh2.begin(), lsh2.end(), a[i].x) - lsh2.begin() + 1;
            line[a[i].x].push_back(i);
        }
        ll ans = 0;
        for (int i = 1; i <= mm; i++) {
            clear();
            for (int x: line[i]) update(a[x].y, a[x].w);
            int sz = (int)line[i].size();
            for (int p = 0; p < sz; p++) {
                for (int q = 0; q < sz; q++) {
                    int u = line[i][p], v = line[i][q];
                    // vis[u][v] = vis[v][u] = 1;
                    ans = max(ans, query(a[u].y, a[v].y));
                }
            }
            for (int j = i + 1; j <= mm; j++) {
                for (int x: line[j]) update(a[x].y, a[x].w);
                for (int x: line[i]) for (int y: line[j]) {
                    // vis[x][y] = vis[y][x] = 1;
                    ans = max(ans, query(a[x].y, a[y].y));
                }
            }
        }
        // for (int i = 1; i <= n; i++) {
        //     for (int j = 1; j <= n; j++) {
        //         printf("%d ", vis[i][j]);
        //     }
        //     puts("");
        // }
        printf("%lld\n", ans);
    }
    return 0;
}