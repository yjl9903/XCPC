#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <random>
#include <ctime>
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
const int maxn = 200000 + 5;

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
inline int qpow(int x, ll n, int mod = mod) {
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
int ping[maxn], pingv[maxn];

int seed = 233233;
int p = 1e9 + 9;
ll xp[maxn], ixp[maxn];

int n, siz[maxn];
vector<int> edge[maxn];
map<ll,int> uqc[maxn];
vector<ll> vecs[maxn], pres[maxn];

int dp[maxn], dp2[maxn], deg[maxn], ans;
ll hashval[maxn], rthash[maxn];
void dfs1(int u, int f) {
    dp[u] = siz[u] = 1; 
    hashval[u] = 1;

    int& sum = deg[u]; sum = 0;
    map<ll,int>& mp = uqc[u]; mp.clear();
    vector<ll>& vec = vecs[u]; vec.clear();
    vector<ll>& pre = pres[u]; pre.clear();

    for (int v: edge[u]) {
        if (v == f) continue;
        sum++;
        dfs1(v, u);
        vec.push_back(hashval[v]);
        siz[u] += siz[v];
        dp[u] = mul(dp[u], dp[v]);
        mp[hashval[v]]++;
    }
    if (sum == 0) return ;

    dp[u] = mul(dp[u], ping[sum]);
    for (auto& x: mp) dp[u] = mul(dp[u], pingv[x.second]);

    ll res = 0;
    sort(vec.begin(), vec.end());
    for (int i = 0; i < (int)vec.size(); i++) {
        res = (res + xp[i] * vec[i] % p) % p;
        if (u == 1) pre.push_back(res);
    }
    hashval[u] = res * siz[u] % p;
    // dbg(u, dp[u], res);
}

set<ll> qc;
void dfs2(int u, int f) {
    if (!qc.count(rthash[u])) {
        // dbg(u, rthash[u], dp2[u]);
        qc.insert(rthash[u]);
        ans = add(ans, dp2[u]);
    }

    map<ll,int>& mp = uqc[u];
    vector<ll>& vec = vecs[u];
    
    for (int v: edge[u]) {
        if (v == f) continue;

        ll tmp = rthash[u] * qpow(n, p - 2, p) % p;
        int rk = lower_bound(vec.begin(), vec.end(), hashval[v]) - vec.begin();
        tmp = (tmp + p - xp[rk] * hashval[v] % p) % p;
        ll suf = (pres[u].back() - pres[u][rk] + p) % p;
        tmp = (tmp + p - suf) % p;
        suf = suf * ixp[1] % p;
        tmp = (tmp + suf) % p;
        tmp = tmp ? tmp * (n - siz[v]) % p : 1;

        vecs[v].push_back(tmp);
        uqc[v][tmp]++;
        pres[v].clear();
        sort(vecs[v].begin(), vecs[v].end());
        ll res = 0;
        for (int i = 0; i < (int)vecs[v].size(); i++) {
            res = (res + xp[i] * vecs[v][i]) % p;
            pres[v].push_back(res);
        }
        rthash[v] = res ? res * n % p : 1;

        // dbg(u, v, tmp, uqc[v][tmp]);
        // tmp ^= hashval[v] * seed + siz[v];
        // rthash[v] = hashval[v] ^ (tmp * seed + n - siz[v]);

        int tdp = mul(dp2[u], inv(dp[v]));
        tdp = mul(tdp, inv((int)edge[u].size()));
        tdp = mul(tdp, mp[hashval[v]]);
        dp2[v] = mul(dp[v], tdp);
        dp2[v] = mul(dp2[v], (int)edge[v].size());
        dp2[v] = mul(dp2[v], inv(uqc[v][tmp]));

        dfs2(v, u);
    }
}

int main() {
    mt19937 rnd(time(0));
    int prime[] = {
        (int)1e9 + 7, (int)1e9 + 9, 
        998244353, 687840301,
        122420729, 917120411,
        687840301, 515880193,
    };
    p = prime[rnd() % 8];
    ping[0] = pingv[0] = 1; xp[0] = 1;
    for (int i = 1; i < maxn; i++) ping[i] = mul(ping[i - 1], i);
    for (int i = 1; i < maxn; i++) pingv[i] = mul(pingv[i - 1], inv(i));
    for (int i = 1; i < maxn; i++) xp[i] = xp[i - 1] * seed % p;
    for (int i = 1; i < maxn; i++) ixp[i] = qpow((int)xp[i], p - 2, p);

    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) edge[i].clear();
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        ans = 0; qc.clear();
        dfs1(1, 0);
        // for (int i = 1; i <= n; i++) {
        //     dbg(i);
        //     for (auto& x: uqc[i]) {
        //         dbg(x.first, x.second);
        //     }
        // }
        dp2[1] = dp[1]; rthash[1] = hashval[1];
        dfs2(1, 0);
        printf("%d\n", ans);
    }
    return 0;
}