#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <cassert>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 3000 + 5;

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
inline int Inv(int x) {
    return qpow(x, mod - 2);
}

int n, m, u[maxn], v[maxn], deg[maxn], inv[maxn];
int dp[maxn], tmp[maxn];

namespace LinearSeq {
    #define rep(i,a,n) for (int i=a;i<n;i++)
    #define per(i,a,n) for (int i=n-1;i>=a;i--)
    #define pb push_back
    #define mp make_pair
    #define all(x) (x).begin(),(x).end()
    #define fi first
    #define se second
    #define SZ(x) ((int)(x).size())
    typedef vector<int> VI;
    const ll mod = 998244353;
    ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
    const int N = 10010;
    ll res[N], base[N], _md[N];

    vector<int> Md;
    void mul(ll* a, ll* b, int k) {
        static ll _c[N];
        for (int i = 0; i < k + k; i++) _c[i] = 0;
        for (int i = 0; i < k; i++) {
            if (!a[i]) continue;
            for (int j = 0; j < k; j++) {
                _c[i + j] = (_c[i + j] + a[i] * b[j]) % mod;
            }
        }
        for (int i = k + k - 1; i >= k; i--) {
            if (!_c[i]) continue;
            for (int j = 0; j < (int)Md.size(); j++) {
                _c[i - k + Md[j]] = (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % mod;
            }
        }
        for (int i = 0; i < k; i++) a[i] = _c[i];
    }
    int solve(ll n, VI a, VI b) { 
        // a 系数 b 初值 b[n+1]=a[0]*b[n]+...
        ll ans = 0, pnt = 0;
        int k = (int)a.size();
        assert((int)a.size() == (int)b.size());
        rep(i,0,k) _md[k-1-i]=-a[i];_md[k]=1;
        Md.clear();
        rep(i,0,k) if (_md[i]!=0) Md.push_back(i);
        rep(i,0,k) res[i]=base[i]=0;
        res[0]=1;
        while ((1ll<<pnt)<=n) pnt++;
        for (int p=pnt;p>=0;p--) {
            mul(res,res,k);
            if ((n>>p)&1) {
                for (int i=k-1;i>=0;i--) res[i+1]=res[i];res[0]=0;
                rep(j,0,SZ(Md)) res[Md[j]]=(res[Md[j]]-res[k]*_md[Md[j]])%mod;
            }
        }
        rep(i,0,k) ans=(ans+res[i]*b[i])%mod;
        if (ans<0) ans+=mod;
        return ans;
    }
    vector<int> BM(vector<int> s) {
        vector<int> C(1, 1), B(1, 1);
        int L = 0, m = 1, b = 1;
        rep(n,0,SZ(s)) {
            ll d=0;
            rep(i,0,L+1) d=(d+(ll)C[i]*s[n-i])%mod;
            if (d==0) ++m;
            else if (2*L<=n) {
                VI T=C;
                ll c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                L=n+1-L; B=T; b=d; m=1;
            } else {
                ll c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                ++m;
            }
        }
        return C;
    }
    int calc(vector<int> a, ll n) {
        vector<int> c = BM(a); c.erase(c.begin());
        for (int i = 0; i < (int)c.size(); i++) c[i] = (mod - c[i]) % mod;
        return solve(n, c, vector<int>(a.begin(), a.begin() + (int)c.size()));
    }
    vector<int> xs(vector<int> a) {
        vector<int> c = BM(a);
        c.erase(c.begin());
        for (int i = 0; i < (int)c.size(); i++) c[i] = (mod - c[i]) % mod;
        return c;
    }
};

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) inv[i] = Inv(i);
    for (int i = 1; i <= n; i++) scanf("%*d%*d");
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", u + i, v + i);
        deg[u[i]]++; deg[v[i]]++;
    }
    vector<int> v;
    dp[1] = 1; v.push_back(1);
    for (int t = 1; t <= 3 * n; t++) {
        memcpy(tmp, dp, (n + 1) * (sizeof dp[0]));
        memset(dp, 0, (n + 1) * (sizeof dp[0]));
        for (int i = 1; i <= m; i++) {
            int u = ::u[i], v = ::v[i];
            if (u != n) {
                dp[v] = add(dp[v], mul(tmp[u], inv[deg[u]]));
            }
            if (v != n) {
                dp[u] = add(dp[u], mul(tmp[v], inv[deg[v]]));
            }
        }
        int tot = 0;
        for (int i = 1; i < n; i++) tot = add(tot, dp[i]);
        v.push_back(tot);
    }
    vector<int> xs = LinearSeq::xs(v);
    int k = (int)xs.size();
    vector<int> a0(k + 1, 0);

    for (int i = 1; i <= k; i++) {
        for (int j = 0; j + 1 <= i; j++) {
            a0[i] = add(a0[i], mul(v[i - j - 1], xs[j]));
        }
    }
    for (auto& x: xs) dbg(x);
    for (int i = 1; i <= k; i++) {
        dbg(i, a0[i], v[i]);
    }
    for (int i = 1; i <= k; i++) a0[i] = sub(v[i], a0[i]);

    int fz = 0, fm = 0;
    
    // for (int i = 0; i < (int)xs.size(); i++) fz = add(fz, v[i]);
    for (int i = 1; i <= k; i++) fz = add(fz, a0[i]);
    for (auto& x: xs) fm = add(fm, x);
    
    dbg(fz, fm);
    fm = sub(1, fm);
    cout << mul(fz, Inv(fm));
    return 0;
}