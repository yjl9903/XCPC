#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <cassert>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<ll,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;
const int maxm = 1e6 + 5;

int n, m, q, qk[maxn];
vector<PII> edge[maxn];
ll ans[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &q);
        for (int i = 1; i <= n; i++) edge[i].clear();
        ll maxd = 0;
        priority_queue<PII,vector<PII>,greater<PII> > pq;
        auto push = [&](int u, ll d) {
            if ((int)pq.size() > maxm) return ;
            pq.push({d, u});
        };
        for (int i = 1, u, v, w; i <= m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            edge[u].push_back({v, w});
            push(v, w);
        }
        int maxk = 0;
        for (int i = 1; i <= q; i++) {
            scanf("%d", qk + i);
            maxk = max(maxk, qk[i]);
        }
        for (int i = 1; i <= maxk; i++) {
            PII tp = pq.top(); pq.pop();
            int u = tp.second, d = tp.first;
            ans[i] = d;
            for (PII x: edge[u]) {
                int v = x.first, w = x.second;
                push(v, d + w);
            }
        }
        for (int i = 1; i <= q; i++) {
            printf("%lld\n", ans[qk[i]]);
        }
    }    
    return 0;
}