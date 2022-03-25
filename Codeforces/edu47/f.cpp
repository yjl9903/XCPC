#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 1e9 + 7;
const int maxn = 1000000 + 5;

vector<int> edge[maxn];
int n, ans[maxn], siz[maxn], son[maxn], dep[maxn];

void dfs(int u, int f) {
    dep[u] = dep[f] + 1; siz[u] = 1;
    int m = -1;
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs(v, u); 
        siz[u] += siz[v];
        if (siz[v] > m) m = siz[v], son[u] = v;
    }
}

int cnt[maxn]; set<PII> st; int sk;
void update(int u, int f, int x) {
    st.erase({-cnt[dep[u]], dep[u]});
    cnt[dep[u]] += x;
    st.insert({-cnt[dep[u]], dep[u]});
    for (int& v: edge[u]) {
        if (v == f || v == sk) continue;
        update(v, u, x);
    }
}
void dfs(int u, int f, int kp) {
    for (int& v: edge[u]) {
        if (v == f || v == son[u]) continue;
        dfs(v, u, 0);
    }
    if (son[u]) dfs(son[u], u, 1), sk = son[u];
    update(u, f, 1); sk = 0;
    ans[u] = st.begin()->second - dep[u];
    if (!kp) update(u, f, -1);
}

int main(){
    scanf("%d", &n);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1, 0); dfs(1, 0, 1);
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}