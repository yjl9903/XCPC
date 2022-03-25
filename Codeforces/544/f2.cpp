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
const int maxn = 200000 + 5;

vector<int> edge[maxn];
vector<PII> ans;
int n, m, d, deg[maxn];

int pre[maxn], link[maxn], vis[maxn];
int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }

void dfs(int u) {
    vis[u] = 1;
    for (int& v: edge[u]) {
        if (vis[v]) continue;
        ans.push_back({u, v});
        dfs(v);
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &d);
    for (int i = 1; i <= n; i++) pre[i] = i;
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
        deg[u]++; deg[v]++;
        if (u != 1 && v != 1) {
            u = find(u); v = find(v);
            if (u != v) pre[u] = v;
        } else {
            if (v == 1) swap(u, v);
            link[v] = 1;
        }
    }
    if (deg[1] < d) return puts("NO"), 0;
    vector<int> g; set<int> st, st2;
    for (int i = 2; i <= n; i++) {
        if (link[i] == 0) continue;
        if (st.count(find(i))) continue;
        st.insert(find(i));
        st2.insert(i);
        g.push_back(i);
    }
    if ((int)g.size() > d) return puts("NO"), 0;
    for (int i = 2; i <= n; i++) {
        if ((int)g.size() == d) break;
        if (link[i] == 0) continue;
        if (st2.count(i)) continue;
        g.push_back(i);
    }

    if ((int)g.size() < d) return puts("NO"), 0;
    puts("YES");

    vis[1] = 1;
    for (int v: g) {
        // cout << v << ' ';
        vis[v] = 1;
        ans.push_back({1, v});
    }
    // cout << endl;
    for (int& v: g) {
        dfs(v);
    }
    for (auto& x: ans) printf("%d %d\n", x.first, x.second);

    return 0;
}