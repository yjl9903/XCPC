#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 250000 + 5;

struct Heap {
    multiset<ll> st; ll sum;
    void insert(ll v) {
        st.insert(v); sum += v;
    }
    void del(ll v) {
        st.erase(st.find(v)); sum -= v;
    }
    void resize(int sz) {
        while (!st.empty() && (int)st.size() > sz) {
            sum -= *st.rbegin();
            st.erase(--st.end());
        }
    }
    void resize(int sz, vector<ll>& v) {
        while (!st.empty() && (int)st.size() > sz) {
            sum -= *st.rbegin();
            v.push_back(*st.rbegin());
            st.erase(--st.end());
        }
    }
} h[maxn];

int n, lim, deg[maxn], ptr[maxn], vis[maxn];
vector<PII> edge[maxn];
vector<int> bag[maxn], key[maxn];

ll dp[maxn][2]; // lim/lim+1
void dfs(int u, int ff) {
    vis[u] = lim;
    int sz = deg[u] - lim;
    h[u].resize(sz);
    vector<ll> add, sub;
    ll tot = 0; int& p = ptr[u];
    while (p < deg[u] && deg[edge[u][p].first] <= lim) p++;
    for (int i = p; i < deg[u]; i++) {
        int v = edge[u][i].first, w = edge[u][i].second;
        if (v == ff) continue;
        dfs(v, u);
        if (dp[v][1] + w < dp[v][0]) {
            tot += dp[v][1] + w; sz--;
        } else {
            tot += dp[v][0];
            add.push_back(dp[v][1] + w - dp[v][0]);
            h[u].insert(dp[v][1] + w - dp[v][0]);
        }
    }
    h[u].resize(sz, sub); dp[u][0] = tot + h[u].sum;
    h[u].resize(sz - 1, sub); dp[u][1] = tot + h[u].sum;
    for (auto& x: sub) h[u].insert(x);
    for (auto& x: add) h[u].del(x);
}

int main() {
    scanf("%d", &n);
    ll total = 0;
    for (int i = 2, u, v, w; i <= n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        edge[u].push_back({v, w});
        edge[v].push_back({u, w});
        deg[u]++; deg[v]++;
        total += w;
    }
    for (int i = 1; i <= n; i++) {
        bag[deg[i]].push_back(i);
        sort(edge[i].begin(), edge[i].end(), [&](PII a, PII b) {
            return deg[a.first] < deg[b.first];
        });
        for (int j = 1; j < deg[i]; j++) key[j].push_back(i);
    }
    printf("%I64d", total);
    for (lim = 1; lim < n; lim++) {
        for (auto u: bag[lim]) {
            for (auto x: edge[u]) {
                int v = x.first, w = x.second;
                h[v].insert(w);
            }
        }
        ll ans = 0;
        for (auto& u: key[lim]) {
            if (vis[u] == lim) continue;
            dfs(u, 0); ans += dp[u][0];
        }
        printf(" %I64d", ans);
    }
    return 0;
}