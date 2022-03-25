#include <cstdio>
#include <cstring>
#include <functional>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const int mod = 1e9 + 7;

int n, a[maxn], s[maxn];
ll qpow(ll a, ll b){
    ll res = 1; a = a % mod;
    while (b){
        if (b & 1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}

int ans = 0, cnt = 0;
int dfs(int p, int m){
    if (p == n){
        ans += m;
        cnt++;
        return 0;
    }
    for (int i = 1; i <= a[p]; i++){
        dfs(p + 1, i > m ? i : m);
    }
    return 0;
}

int main(){
    s[0] = 0;
    for (int i = 1; i < maxn; i++) s[i] = s[i - 1] + i;
    while (~scanf("%d", &n)){
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        sort(a, a + n);
        int d = 1;
        ll res = 0, k = 1;
        // for (int i = 0; i < n; i++){
        //     // if (a[i] == a[i + 1] && i + 1 < n) k = 1ll * a[i++] * k % mod;
        //     ll q = d;
        //     while (d <= a[i]){
        //         ll c = 1ll * qpow(d, n - 1 - i) * k % mod;
        //         if (c == 0) c = k;
        //         res += 1ll * (c * d % mod) * q % mod ;
        //         d++;
        //     }
        //     k = a[i] * k % mod;
        // }
        ans = cnt = 0;
        dfs(0, 1);
        printf("%d\n", ans);
        // printf("%lld\n", res);
    }
    return 0;
}