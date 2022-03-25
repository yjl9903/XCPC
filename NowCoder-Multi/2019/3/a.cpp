#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <utility>
#include <random>
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
const ll inf = (ll)1e18;
const int blocksz = 500;
const int maxn = 500000 + 5;

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

mt19937_64 rnd(time(0));

int n, m, q, f[maxn], big;
ll val[maxn];
PII eg[maxn];
vector<int> g[maxn];

int check(int u) {
    return (int)g[u].size() < blocksz;
}

int vis[maxn], block[maxn], L[maxn], R[maxn], bel[maxn];
ll bb[blocksz * 2][blocksz * 2], cc[blocksz * 2][blocksz * 2];
void force(int l, int r) {
    int k = bel[l];
    for (int i = l; i <= r; i++) {
        vis[i] ^= 1;
        int u = eg[i].first, v = eg[i].second;
        if (!check(u)) {
            bb[k][f[u]] ^= val[v];
            cc[k][f[u]] ^= val[v];
        }
        if (!check(v)) {
            bb[k][f[v]] ^= val[u];
            cc[k][f[v]] ^= val[u];
        }
    }
}
void update(int l, int r) {
    if (bel[l] == bel[r]) return force(l, r);
    for (int i = bel[l] + 1; i < bel[r]; i++) block[i] ^= 1;
    force(l, R[bel[l]]); force(L[bel[r]], r);
}
ll query(int u) {
    ll ans = 0;
    if (check(u)) {
        for (int id: g[u]) {
            if (vis[id] ^ block[bel[id]]) {
                int v = u ^ eg[id].first ^ eg[id].second;
                ans ^= val[v];
            }
        }
    } else {
        for (int i = 1; i <= bel[m]; i++) {
            if (block[i]) ans ^= cc[i][f[u]];
            else ans ^= bb[i][f[u]];
        }
    }
    return ans;
}

int main() {
    int T = gi(); 
    while (T--) {
        n = gi(); m = gi();
        for (int i = 1, tot = 1; i <= m; i += blocksz, tot++) {
            block[tot] = 0;
            L[tot] = i; R[tot] = min(m, i + blocksz - 1);
            for (int j = L[tot]; j <= R[tot]; j++) bel[j] = tot;
		}
        for (int i = 1; i <= n; i++) val[i] = rnd(), g[i].clear(), f[i] = 0;
        for (int i = 1; i <= m; i++) {
            eg[i].first = gi();
            eg[i].second = gi();
            g[eg[i].first].push_back(i);
            g[eg[i].second].push_back(i);
            vis[i] = 1;
        }
        big = 0;
        for (int i = 1; i <= n; i++) {
            if (check(i)) continue;
            f[i] = ++big;
        }
        for (int i = 1; i <= bel[m]; i++) {
            for (int j = 1; j <= big; j++) bb[i][j] = cc[i][j] = 0;
            for (int j = L[i]; j <= R[i]; j++) {
                int u = eg[j].first, v = eg[j].second;
                if (!check(u)) {
                    bb[i][f[u]] ^= val[v];
                }
                if (!check(v)) {
                    bb[i][f[v]] ^= val[u];
                }
            }
        }
        q = gi();
        int op;
        while (q--) {
            op = gi();
            if (op == 1) {
                int l, r; 
                l = gi(); r = gi();
                update(l, r);
            } else {
                int u, v; 
                u = gi(); v = gi();
                if (query(u) == query(v)) putchar('1');
                else putchar('0');
            }
        }
        puts("");
    }
    return 0;
}