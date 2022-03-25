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
const ll inf = 1ll << 60;
const int maxn = 300 + 5;
const int maxm = 100000 + 5;

struct Que {
    int u, v, w, id;
    bool operator<(const Que& b) const {
        return w < b.w;
    }
};

int n, m, r[maxn], G[maxn][maxn];
ll dis[maxn][maxn], ans[maxm];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        vector<PII> vec;
        for (int i = 1; i <= n; i++) scanf("%d", r + i), vec.push_back({r[i], i});
        sort(vec.begin(), vec.end());
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%d", &G[i][j]);
                dis[i][j] = G[i][j];
            }
            dis[i][i] = 0;
        }
        vector<Que> que;
        for (int i = 1, u, v, w; i <= m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            que.push_back({u, v, w, i});
        }
        sort(que.begin(), que.end());
        int j = 0;
        for (auto q: que) {
            while (j < n && vec[j].first <= q.w) {
                int k = vec[j].second; j++;
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n; j++) {
                        if (dis[i][j] > dis[i][k] + dis[k][j]) {
                            dis[i][j] = dis[i][k] + dis[k][j];
                        }
                    }
                }
            }
            ans[q.id] = dis[q.u][q.v];
        }
        printf("Case #%d:\n", ++kase);
        for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
    }
    return 0;
}