#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <unordered_map>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int mod = 998244353;

ll n;
int x0, a, b, p, q, v;

inline int add(int x, int y) {
    x += y;
    return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
    x -= y;
    return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
    return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
    int r = 1;
    while (n > 0) {
        if (n & 1) r = 1ll * r * x % mod;
        n >>= 1; x = 1ll * x * x % mod;
    }
    return r;
}
inline int inv(int x) {
    return qpow(x, mod - 2);
}

namespace exBSGS {
    int flag = 1;
    int fpow(int a,int b,int MOD) {
        int s=1;
        while(b){if(b&1)s=1ll*s*a%MOD;a=1ll*a*a%MOD;b>>=1;}
        return s;
    }
    void NoAnswer() {
        // puts("No Solution");
        flag = 0;
    }
    int ex_BSGS(int y,int z,int p) {
        flag = 1;
        if(z==1) return 0;
        int k=0,a=1;
        while(233) {
            int d=__gcd(y,p);if(d==1)break;
            if(z%d){
                NoAnswer();
                return -1;
            }
            z/=d;p/=d;++k;a=1ll*a*y/d%p;
            if(z==a) return k;
        }
        unordered_map<int,int> mp;
        // Hash.clear();
        int m=sqrt(p)+1;
        // for(int i=0,t=z;i<m;++i,t=1ll*t*y%p) Hash.Insert(t,i);
        for(int i=0,t=z;i<m;++i,t=1ll*t*y%p) mp[t] = i;
        for(int i=1,tt=fpow(y,m,p),t=1ll*a*tt%p;i<=m;++i,t=1ll*t*tt%p)
        {
            if (!mp.count(t)) continue;
            int B = mp[t];
            return i * m - B + k;
        }
        NoAnswer();
        return -1;
    }
}
using exBSGS::ex_BSGS;
using exBSGS::flag;

ll BSGS(ll a, ll b, ll p) { // a^x = b (mod p)
    a %= p;
    if (!a && !b) return 1;
    if (!a) return -1;
    static map<ll, ll> mp; mp.clear();
    ll m = sqrt(p + 1.5);
    ll v = 1;
    for (int i = 1; i <= m; i++) {
        v = v * a % p;
        mp[v * b % p] = i;
    }
    ll vv = v;
    for (int i = 1; i <= m; i++) {
        auto it = mp.find(vv);
        if (it != mp.end()) return i * m - it->second;
        vv = vv * v % p;
    }
    return -1;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%lld%d%d%d%d", &n, &x0, &a, &b, &p);
        mod = p;
        
        int ivb = 0, ivab = 0, y0 = 0, ivy0 = 0;
        if (b) ivb = qpow(b, p - 2);
        if (a > 1) {
            ivab = mul(b, qpow(a - 1, p - 2));
            y0 = add(x0, ivab);
            if (y0) ivy0 = qpow(y0, p - 2);
        }

        scanf("%d", &q);
        while (q--) {
            scanf("%d", &v);
            if (a == 0) {
                if (v == x0) puts("0");
                else if (v == b && n > 1) puts("1");
                else puts("-1");
            } else if (a == 1) {
                v = sub(v, x0);
                int ans = mul(v, ivb);
                if (ans >= n) puts("-1");
                else printf("%d\n", ans);
            } else {
                v = add(v, ivab);
                if (y0 == 0) {
                    if (v == 0) puts("0");
                    else puts("-1");
                    continue;
                }
                v = mul(v, ivy0);
                // int ans = ex_BSGS(a, v, p);
                // if (!flag) puts("-1");
                // else if (ans >= n) puts("-1");
                // else printf("%d\n", ans);
                ll ans = BSGS(a, v, p);
                if (ans == -1) puts("-1");
                else if (ans >= n) puts("-1");
                else printf("%lld\n", ans);
            }
        }
    }
    return 0;
}