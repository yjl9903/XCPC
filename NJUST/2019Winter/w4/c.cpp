#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
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
const int mod = 998244353;
const int maxn = 300000 + 5;

vector<int> edge[maxn];
int n, m, deg[maxn], wa = 0, tot = 0;
char s[maxn];
int cnt[maxn][30], vis[maxn], ring[maxn], ans = 0;

void dfs(int u) {
    dbg(u);
    vis[u] = tot;
    cnt[u][s[u] - 'a']++;
    vector<int> tmp(26, 0);
    for (int& v: edge[u]) {
        if (vis[v]) {
            // dbg(u, v);
            for (int i = 0; i < 26; i++) tmp[i] = max(cnt[v][i], tmp[i]);
            continue;
        }
        dfs(v);
        for (int i = 0; i < 26; i++) tmp[i] = max(cnt[v][i], tmp[i]);
    }
    for (int i = 0; i < 26; i++) cnt[u][i] += tmp[i], ans = max(ans, cnt[u][i]);
}

int dfs2(int u) {
    for (int& v: edge[u]) {
        if (ring[v] || v == u) {
            wa = 1; return 0;
        }
        ring[v] = 1;
        if (dfs2(v) == 0) return 0;
        ring[v] = 0;
    }
    return 1;
}

int main(){
    scanf("%d%d%s", &n, &m, s + 1);
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        if (u == v) return puts("-1"), 0;
        edge[u].push_back(v);
        deg[v]++;
    }
    int flag = 1;
    for (int i = 1; i <= n; i++) {
        if (deg[i]) continue;
        ring[i] = 1;
        dfs2(i);
        ring[i] = 0;
        if (wa) return puts("-1"), 0;
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i]) continue;
        flag = 0;
        tot = i;
        dfs(i);
    }
    // for (int i = 1; i <= n; i++) {
    //     cout << i << ": ";
    //     for (int j = 0; j < 26; j++) cout << cnt[i][j] << ' ';
    //     cout << endl;
    // }
    if (flag) puts("-1");
    else {
        cout << ans << endl;
    }
    return 0;
}