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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int sz = 450;
const int maxn = 200000 + 5;

int qpow(ll x, ll n) {
    int r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}
int f[maxn], inv[maxn], finv[maxn];
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
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
}
void add(int& x, int y) {
    x += y; if (x >= mod) x -= mod;
}
void sub(int& x, int y) {
    x -= y; if (x < 0) x += mod;
}
void mul(int& x, int y) {
    x = 1ll * x * y % mod;
}
const int inv2 = qpow(2, mod - 2);

struct Que {
    int n, m;
    bool operator<(const Que& b) const {
        if (n / sz == b.n / sz) {
            if (n / sz % 2) return m > b.m;
            return m < b.m;
        }
        return n < b.n;
    }
};
vector<Que> q;

int n, t[maxn]; ll T;

int main() {
    init();
    ll pre = 0; int ans = 0;
    scanf("%d%I64d", &n, &T);
    for (int i = 1; i <= n; i++) {
        scanf("%d", t + i);
        pre += t[i];
        if (pre > T) continue;
        if (pre + i <= T) ans++;
        else q.push_back({ i, int(T - pre) });
    }
    sort(q.begin(), q.end());
    int nn = 1, mm = 0, tot = 1;
    for (auto x: q) {
        while (nn < x.n) {
            add(tot, tot); sub(tot, C(nn, mm)); nn++;
        }
        while (nn > x.n) {
            nn--; add(tot, C(nn, mm)); mul(tot, inv2);
        }
        while (mm < x.m) {
            mm++; add(tot, C(nn, mm));
        }
        while (mm > x.m) {
            sub(tot, C(nn, mm)); mm--;
        }
        add(ans, 1ll * tot * qpow(inv2, x.n) % mod);
    }
    cout << ans;
    return 0;
}