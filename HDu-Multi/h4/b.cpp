#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const int mod = 1000000000 + 7;

int F[maxn], Finv[maxn], inv[maxn];//F是阶乘，Finv是逆元的阶乘 
void init(){
    inv[1] = 1;
    for(int i = 2; i < maxn; i ++){
        inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    }
    F[0] = Finv[0] = 1;
    for(int i = 1; i < maxn; i ++){
        F[i] = F[i-1] * 1ll * i % mod;
        Finv[i] = Finv[i-1] * 1ll * inv[i] % mod;
    }
}
int C(int n, int m){
    if(m < 0 || m > n) return 0;
    return F[n] * 1ll * Finv[n - m] % mod * Finv[m] % mod;
}

int sz = sqrt(maxn);
ll ans[maxn] = {0};
struct que{
    int n, m, id;
    bool operator < (const que& b) const {
        if (n / sz != b.n / sz) return n < b.n;
        return m < b.m;
    }
};
vector<que> v;

int main(){
    init();
    int T, cnt = 0; scanf("%d", &T);
    while (T--){
        int x, y; scanf("%d%d", &x, &y);
        v.push_back({x, y, ++cnt});
    }
    sort(v.begin(), v.end());
    int n = 1, m = 1;
    ll tmp = 2;
    for (int i = 0; i < v.size(); i++){
        while (n < v[i].n) tmp = (2ll * tmp % mod + mod - C(n++, m)) % mod;
        while (n > v[i].n) tmp = (1ll * tmp + C(--n, m)) * 1ll * Finv[2] % mod;
        while (m < v[i].m) tmp = (1ll * tmp + C(n, ++m)) % mod;
        while (m > v[i].m) tmp = (1ll * tmp + mod - C(n, m--)) % mod;
        ans[v[i].id] = tmp;
    }
    for (int i = 1; i <= cnt; i++){
        printf("%lld\n", ans[i]);
    }
    return 0;
}