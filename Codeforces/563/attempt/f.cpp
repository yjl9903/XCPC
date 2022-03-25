#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <random>
#include <ctime>
#include <cassert>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n;
int siz[maxn], fa[maxn], vis[maxn];
vector<int> edge[maxn];

int query(int u) {
    cout << "d " << u << endl;
    cin >> u; return u;
}
void answer(int u) {
    cout << "! " << u << endl;
}

void getfa(int u, int f) {
    fa[u] = f;
    for (int& v: edge[u]) {
        if (v == f) continue;
        getfa(v, u);
    }
}

int rt, mn, sum;
void dfs(int u, int f) {
    int mx = 0;
    for (int& v: edge[u]) {
        if (v == f || vis[v]) continue;
        dfs(v, u);
        siz[u] += siz[v];
        mx = max(siz[v], mx);
    }
    mx = max(mx, sum - siz[u]);
    if (mx < mn) mn = mx, rt = u;
}
int getrt(int u) {
    sum = siz[u]; mn = 1e9; rt = 0;
    dfs(u, 0); return rt;
}

int p[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    getfa(1, 0);
    siz[1] = n; int tot = 1;
    for (int t = 1; t <= 18; t++) {
        int rt = getrt(tot);
        // cout << "root: " << rt << endl;
        if (rt == 1) {
            vis[1] = 1;
            cout << "s 1" << endl;
            cin >> tot; continue; 
        }
        int d1 = query(rt);
        if (d1 == 0) {
            answer(rt); return 0;
        }
        int d2 = query(fa[rt]);
        if (d2 == 0) {
            answer(fa[rt]); return 0;
        }
        if (d2 > d1) {
            tot = rt; vis[fa[rt]] = 1;
        } else {
            vis[rt] = 1; tot = fa[rt];
        }
    }
    assert(0);
    return 0;
}