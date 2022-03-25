#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 200000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        x = x * x % mod; n >>= 1;
    }
    return r;
}
ll inv(ll x) { return qpow(x, mod - 2); }
ll rev[maxn << 2];
int init(int m) {
    int step = 0, n = 1;
    for (; n < m; n <<= 1) ++step;
    for (int i = 1; i < n; i++) 
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (step - 1));
    return n;  
}
void ntt(vector<ll>& a, int n, int op) {
    for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int h = 2; h <= n; h <<= 1) {
        ll wn = qpow(3, (mod - 1) / h);
        if (op == -1) wn = inv(wn);
        for (int i = 0; i < n; i += h) {
            ll w = 1;
            for (int j = i; j < i + h / 2; j++) {
                ll u = a[j], t = a[j + h / 2] * w % mod;
                a[j] = (u + t) % mod;
                a[j + h / 2] = (u - t + mod) % mod;
                w = w * wn % mod;
            }
        }
    }
    if (op == -1) {
        ll rn = inv(n);
        for (int i = 0; i < n; i++) a[i] = a[i] * rn % mod;
    }
}

map<int,vector<int> > mpa, mpb;
map<int,int> mp;
int n, m, a[maxn], b[maxn];
ll ans[maxn];

int main(){
    const int T = 10000;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++) scanf("%d", a + i), mpa[a[i]].push_back(i), mp[a[i]]++;
    for (int i = 0; i <= m; i++) scanf("%d", b + i), mpb[b[i]].push_back(i), mp[b[i]]++;
    int lim = init(n + m + 1);
    for (auto& x: mp) {
        if (x.second <= T) { // O(T^2) -> N / T
            vector<int> va = mpa[x.first], vb = mpb[x.first];
            for (int& x: va) for (int& y: vb) ans[x + y] = (ans[x + y] + 1ll * x * y % mod) % mod;
        } else { // O(n \log n) -> N / T
            vector<ll> a(lim, 0), b(lim, 0);
            vector<int> va = mpa[x.first], vb = mpb[x.first];
            for (int& x: va) a[x] = x; for (int& y: vb) b[y] = y;
            ntt(a, lim, 1); ntt(b, lim, 1);
            for (int i = 0; i < lim; i++) a[i] = a[i] * b[i] % mod;
            ntt(a, lim, -1);
            for (int i = 0; i <= n + m; i++) ans[i] = (ans[i] + a[i]) % mod;
        }
    }
    for (int i = 0; i <= n + m; i++) {
        if (i) putchar(' ');
        printf("%lld", ans[i]);
    }
    return 0;
}