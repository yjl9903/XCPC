#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <unordered_map>
#include <set>
#include <map>
#include <cassert>
#include <functional>
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
typedef unsigned long long ull;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;
const int base = 233;

int C = 0, T = 51618;

ull xp[maxn];
int ping[maxn], pingv[maxn];

struct fastIO {
    char s[100000]; int it,len;
    fastIO() { it = len = 0; }
    inline char get() {
        if (it < len) return s[it++];
        it = 0; len = fread(s, 1, 100000, stdin);
        if (len == 0) return EOF;
        else return s[it++];
    }
    bool notend() {
        char c = get();
        while(c == ' ' || c == '\n') c = get();
        if (it > 0) it--;
        return c != EOF;
    }
} buff;
inline int gi() {
    int r = 0; bool ng = 0; 
    char c = buff.get();
    while (c != '-' && (c < '0' || c > '9')) c = buff.get();
    if (c == '-') ng = 1, c = buff.get();
    while (c >= '0' && c <= '9') r = r * 10 + c - '0', c = buff.get();
    return ng ? -r : r;
}

namespace {
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
}

int n, ans, rt, siz[maxn];

int dp[maxn], rdp[maxn];
ull hashval[maxn], hashsrc[maxn], rthash[maxn], rthashsrc[maxn];

vector<ull> hashson[maxn], offhash[maxn], sufhash[maxn];

map<ull,int> uqc[maxn];
map<ull,int>::iterator it;

ull pack(ull x, int siz) {
    return 3ull + x * xp[1] + 37ull * xp[siz + 1];
}

struct E {
    int to, nxt;
} g[maxn * 2];
int ecnt, head[maxn], deg[maxn];
void init() {
    ecnt = 0;
    for (int i = 0; i <= n; i++) head[i] = deg[i] = 0;
}
void adde(int u, int v) {
    g[++ecnt] = { v, head[u] }; head[u] = ecnt;
}

void predfs(int u, int ff) {
    siz[u] = dp[u] = 1;
    int sz = 0;
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to;
        if (v == ff) continue;
        predfs(v, u);
        sz++;
        dp[u] = mul(dp[u], dp[v]);
        siz[u] += siz[v];
        hashson[u].push_back(hashval[v]);
        uqc[u][hashval[v]] += 1;
    }
    if (sz == 0) {
        hashval[u] = hashsrc[u] = 1; 
        return ;
    }

    dp[u] = mul(dp[u], ping[sz]);
    for (it = (uqc[u]).begin(); it != (uqc[u]).end(); it++) {
        dp[u] = mul(dp[u], pingv[it->second]);
    }
    // for (pair<ull,int> x: uqc[u]) {
    //     // dp[u] = mul(dp[u], pingv[x.second]);
    // }

    sort(hashson[u].begin(), hashson[u].end());
    ull res = 0;
    for (int i = 0; i < sz; i++) {
        res += xp[i] * hashson[u][i];
    }
    hashsrc[u] = res;
    hashval[u] = pack(res * siz[u], siz[u]);

    if (u == rt) {
        offhash[u].resize(sz + 2);
        sufhash[u].resize(sz + 2);
        for (int i = 0; i < sz + 2; i++) {
            offhash[u][i] = sufhash[u][i] = 0ull;
        }
        for (int i = sz - 1; i >= 1; i--) {
            offhash[u][i - 1] = offhash[u][i] + xp[i - 1] * hashson[u][i];
        }
        for (int i = sz - 1; i >= 0; i--) {
            sufhash[u][i] = sufhash[u][i + 1] + xp[i] * hashson[u][i];
        }
        // assert(0);
    }
}
set<ull> qc;
void dfs(int u, int f) {
    if (!qc.count(rthash[u])) {
        // dbg(u, rdp[u], rthash[u]);
        qc.insert(rthash[u]);
        ans = add(ans, rdp[u]);
    }
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to;
        if (v == f) continue;

        ull tmp = rthashsrc[u];
        int pos = lower_bound(hashson[u].begin(), hashson[u].end(), hashval[v]) - hashson[u].begin();
        tmp -= sufhash[u][pos]; 
        tmp += offhash[u][pos];
        tmp = tmp ? pack(tmp * (n - siz[v]), n - siz[v]) : 1;

        hashson[v].push_back(tmp);
        uqc[v][tmp]++;
        sort(hashson[v].begin(), hashson[v].end());
        ull res = 0; int sz = (int)hashson[v].size();
        for (int i = 0; i < sz; i++) {
            res += xp[i] * hashson[v][i];
        }
        rthashsrc[v] = res;
        rthash[v] = pack(res * n, n);

        offhash[v].resize(sz + 2);
        sufhash[v].resize(sz + 2);
        for (int i = 0; i < sz + 2; i++) {
            offhash[v][i] = sufhash[v][i] = 0ull;
        }

        for (int i = sz - 1; i >= 1; i--) {
            offhash[v][i - 1] = offhash[v][i] + xp[i - 1] * hashson[v][i];
        }
        for (int i = sz - 1; i >= 0; i--) {
            sufhash[v][i] = sufhash[v][i + 1] + xp[i] * hashson[v][i];
        }

        int tdp = mul(rdp[u], inv(dp[v]));
        // tdp = mul(tdp, inv((int)edge[u].size()));
        tdp = mul(tdp, inv(deg[u]));
        tdp = mul(tdp, uqc[u][hashval[v]]);
        rdp[v] = mul(dp[v], tdp);
        // rdp[v] = mul(rdp[v], (int)edge[v].size());
        rdp[v] = mul(rdp[v], deg[v]);
        rdp[v] = mul(rdp[v], inv(uqc[v][tmp]));

        dfs(v, u);
    }
}

int main() {
    // freopen("./input/test.txt", "r", stdin);
    // freopen("./out", "w", stdout);

    xp[0] = 1; ping[0] = pingv[0] = 1;
    for (int i = 1; i < maxn; i++) xp[i] = xp[i - 1] * base;
    for (int i = 1; i < maxn; i++) {
        ping[i] = mul(ping[i - 1], i);
        pingv[i] = mul(pingv[i - 1], inv(i));
    }
    int T = gi();
    while (T--) {
        C++;
        n = gi(); init();
        for (int i = 2, u, v; i <= n; i++) {
            u = gi(); v = gi();
            adde(u, v); adde(v, u);
            deg[u]++; deg[v]++;
        }

        qc.clear(); ans = 0;
		rt = 1;
        predfs(rt, 0);
        rthash[rt] = hashval[rt]; 
        rthashsrc[rt] = hashsrc[rt];
        rdp[rt] = dp[rt];
        dfs(rt, 0);

        printf("%d\n", ans);
        
        for (int i = 1; i <= n; i++) {
            hashson[i].clear();
            sufhash[i].clear();
            offhash[i].clear();
            uqc[i].clear();
        }
    }
    return 0;
}