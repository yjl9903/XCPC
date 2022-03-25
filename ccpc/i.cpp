#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const int mod = 1000000000 + 7;

struct edge{int to, nxt, d;}f[maxn * 2];
int head[maxn], tot;
void add(int x, int y, int d){
    f[++tot] = {y, head[x], d}; head[x] = tot;
}

ll fv[maxn];
int n, vis[maxn];

ll dep[maxn];
int dfs(int x){
    vis[x] = 1;
    int cnt = 1;
    for (int i = head[x]; i; i = f[i].nxt){
        int v = f[i].to;
        if (vis[v]) continue;
        int t = dfs(v);
        dep[x] += (dep[v] + 1ll * t * (n - t) % mod * f[i].d % mod) % mod;
        dep[x] %= mod;
        cnt += t;
    }
    return cnt;
}

int main(){
    fv[0] = 1;
    for (int i = 1; i < maxn; i++) fv[i] = fv[i - 1] * i % mod;
    while (~scanf("%d", &n)){
        ms(vis, 0); ms(dep, 0); ms(head, 0); tot = 0;
        for (int x, y, l, i = 2; i <= n; i++){
            scanf("%d%d%d", &x, &y, &l); 
            add(x, y, l); add(y, x, l);
        }
        dfs(1); ll x = dep[1] % mod;
        printf("%lld\n", x * fv[n - 1] % mod * 2 % mod);
    }
    return 0;
}