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
const int maxn = 100000 + 5;

int n, mx, w[maxn];
vector<int> edge[maxn];

struct DS {
    int bag[maxn], ans;
    void init() {
        ans = 0;
        for (int i = 1; i <= n; i++) bag[w[i]] = 0;
    }
    void update(int w, int x) {
        if (x == 1) {
            bag[w]++;
            if (bag[w] == 1) ans++;
        } else {
            bag[w]--;
            if (bag[w] == 0) ans--;
        }
    }
} f, g;

int siz[maxn], son[maxn];
void getsz(int u) {
    g.update(w[u], 1);
    siz[u] = 1; son[u] = 0;
    int m = -1;
    for (int& v: edge[u]) {
        getsz(v);
        siz[u] += siz[v];
        if (siz[v] > m) son[u] = v, m = siz[v];
    }
}
bool sk[maxn];
void add(int u, int x) {
    f.update(w[u], x); g.update(w[u], -x);
    for (int& v: edge[u]) {
        if (sk[v]) continue;
        add(v, x);
    }
}
void dfs(int u, int kp) {
    for (int& v: edge[u]) {
        if (v == son[u]) continue;
        dfs(v, 0);
    }
    if (son[u]) dfs(son[u], 1), sk[son[u]] = 1;
    add(u, 1); mx = max(mx, f.ans + g.ans);
    if (son[u]) sk[son[u]] = 0;
    if (!kp) add(u, -1);
}

int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i++) edge[i].clear();
        for (int i = 2, p; i <= n; i++) {
            scanf("%d", &p); edge[p].push_back(i);
        }
        for (int i = 1; i <= n; i++) scanf("%d", w + i);
        mx = 0; getsz(1); dfs(1, 0);
        printf("%d\n", mx);
        f.init(); g.init();
    }
    return 0;
}