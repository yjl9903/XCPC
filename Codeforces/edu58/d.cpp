#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;

int gcd(int a, int b){return b ? gcd(b, a % b) : a;}

vector<int> edge[maxn], fac[maxn];
int n, ans, a[maxn], dep[maxn];

int vis[maxn], siz[maxn], sum, mn, rt;
void getrt(int u, int f) {
    siz[u] = 1; int t = 0;
    for (int& v: edge[u]) {
        if (v == f || vis[v]) continue;
        getrt(v, u); siz[u] += siz[v];
        t = max(t, siz[v]);
    }
    t = max(t, sum - siz[u]);
    if (t < mn) mn = t, rt = u;
}
int getrt(int u) {
    sum = siz[u]; mn = 1e9; rt = 0;
    getrt(u, 0); return rt;
}

int g[maxn], mp[maxn]; vector<int> vec;
void dfs(int u, int f) {
    g[u] = gcd(a[u], g[f]);
    if (g[u] == 1) return ;
    dep[u] = dep[f] + 1;
    vec.push_back(u);
    for (int& v: edge[u]) {
        if (v == f || vis[v]) continue;
        dfs(v, u);
    }
}
void solve(int u) {
    dbg(u);
    vis[u] = 1; g[u] = a[u]; dep[u] = 0;
    for (int& x: fac[a[u]]) mp[x] = 0, ans = max(ans, 1);
    vector<int> al; al.push_back(a[u]);
    for (int& v: edge[u]) {
        if (vis[v]) continue;
        vec.clear(); dfs(v, u);
        for (int& x: vec) {
            dbg(x, g[x]);
            for (int& y: fac[g[x]]) ans = max(ans, mp[y] + dep[x] + 1);
        }
        for (int& x: vec) {
            al.push_back(g[x]);
            for (int& y: fac[g[x]]) mp[y] = max(mp[y], dep[x]);
        }
    }
    for (int& x: al) {
        for (int& y: fac[x]) mp[y] = -1e9;
    }
    for (int& v: edge[u]) {
        if (vis[v]) continue;
        solve(getrt(v));
    }
}

int main() {
    for (int i = 2; i < maxn; i++) {
        vector<int> v; int x = i;
        for (int j = 2; j * j <= x; j++) {
            if (x % j) continue;
            while (x % j == 0) x /= j;
            v.push_back(j);
        }
        if (x > 1) v.push_back(x);
        fac[i] = v; mp[i] = -1e9;
    }
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    siz[1] = n; solve(getrt(1));
    cout << ans << endl;
    return 0;
}