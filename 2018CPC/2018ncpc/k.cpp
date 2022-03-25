#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 2500 + 5;
const ll mod = 1e9 + 7;

int head[maxn], nxt[maxn << 1], to[maxn << 2], tot;
void add(int x, int y){
    to[++tot] = y; nxt[tot] = head[x]; head[x] = tot;
}

ll f[maxn], inv[maxn], finv[maxn];
void init(){
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    f[0] = finv[0] = 1; 
    for (int i = 1; i < maxn; i++) {
        f[i] = f[i - 1] * 1ll * i % mod;
        finv[i] = finv[i - 1] * 1ll * inv[i] % mod;
    }
}
int C(int n, int m){
    if (m < 0 || m > n || n < 0) return 0;
    return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
}

int n, k;

ll dfs(int u){
    ll ans = k - 1; if (u == 1) ans++;
    for (int i = head[u]; i; i = nxt[i]){
        int v = to[i];
        ans = 1ll * ans * dfs(v) % mod;
    }
    return ans % mod;
}

int main(){
    init();
    scanf("%d%d", &n, &k);
    for (int i = 2, x; i <= n; i++){
        scanf("%d", &x); add(x + 1, i);
    }
    ll ans = 0, sk = k, i = 0, f = 1;
    do {
        ans += f * C(sk, i++) * dfs(1) % mod; ans = (ans + mod) % mod;
        // cout << C(sk, i) << endl;
        f *= -1; k--;
        // cout << k << ' ' << ans << endl;
    } while(k > 1);
    cout << ans << endl;
    return 0;
}