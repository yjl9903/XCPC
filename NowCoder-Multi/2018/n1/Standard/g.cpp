#include<bits/stdc++.h>
using namespace std;

#define I inline
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef pair<int, int> PII;

const int N = 60;
const int MOD = 1e9+7;
const int INF = 0x3f3f3f3f;

int n;
bool done[N];
PII f[1<<12][N], g[1<<12][N];
vector<int> G[N];

PII operator*(const PII &A, const PII &B) { return {A.fi+B.fi, 1LL*A.se*B.se%MOD}; }

I void upd(PII &A, const PII &B) {
    if(A.fi > B.fi) A = B;
    else if(A.fi == B.fi) A.se = (A.se+B.se)%MOD;
}

priority_queue<PII, vector<PII>, greater<PII>> Q;

void dij(PII *g, PII *f) {
    for(int i = 0; i < n; i++) {
        if(g[i].fi != INF) Q.push({g[i].fi, i});
        done[i] = 0;
    }
    while(!Q.empty()) {
        PII t = Q.top(); Q.pop();
        int u = t.se;
        if(done[u]) continue;
        done[u] = 1;
        for(int v:G[u]) if(g[v].fi >= g[u].fi+1) {
            bool flag = g[v].fi>g[u].fi+1;
            upd(g[v], g[u]*mp(1, 1));
            upd(f[v], g[u]*mp(1, 1));
            if(flag) Q.push({g[v].fi, v});
        }
    }
}

I void work() {
    int m, k;
    if(scanf("%d%d%d", &n, &m, &k) == -1) exit(0);
    int all = (1<<k)-1;
    for(int u = 0; u < n; u++) {
        G[u].clear();
        for(int S = 0; S <= all; S++) f[S][u] = g[S][u] = {INF, 0};
        if(u < k) f[1<<u][u] = g[1<<u][u] = {0, 1};
    }

    while(m--) {
        int u, v; scanf("%d%d", &u, &v);
        G[u-1].pb(v-1), G[v-1].pb(u-1);
    }

    for(int S = 0; S <= all; S++) {
        for(int u = 0; u < n; u++) for(int S0 = (S-1)&S; S0; S0 = (S0-1)&S)
            if((S0&-S0) == (S&-S)) upd(g[S][u], f[S0][u]*g[S^S0][u]);
        dij(g[S], f[S]);
    }
    printf("%d\n", g[all][0].se);
}

int main() {
    for(;;) work();
    return 0;
}