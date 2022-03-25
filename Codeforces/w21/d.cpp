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
const int maxn = 100000 + 5;

vector<int> edge[maxn];
int n, m, a[maxn], deg[maxn], fa[maxn], ans[maxn];
vector<int> v; set<int> st;

void dfs(int u, int f) {
    fa[u] = f;
    for (int& v: edge[u]) {
        dfs(v, u);
    }
}

void dfs1(int u, int f) {
    for (int& v: edge[u]) dfs1(v, u);
    if (ans[u] == u) v.push_back(ans[u]);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0, u, v; i < m; i++) {
        scanf("%d%d", &u, &v);
        deg[v]++; edge[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) if (deg[i] == 0) dfs(i, 0);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        int x = i;
        while (x) {
            if (ans[x]) {
                if (ans[x] != a[i]) return puts("-1"), 0;
                break;
            }
            ans[x] = a[i];
            if (x == a[i]) break;
            x = fa[x];
        }
    }
    for (int i = 1; i <= n; i++) if (deg[i] == 0) dfs1(i, 0);
    cout << (int)v.size() << endl;
    for (int& x: v) printf("%d\n", x);
    return 0;
}