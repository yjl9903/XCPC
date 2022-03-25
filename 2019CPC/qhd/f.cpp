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
const int maxn = 500000 + 5;

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
int two[maxn];
inline int qpow(int x, ll n) {
    assert(n >= 0);
    if (x == 2 && n < maxn) return two[n];
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

int cnt, ans, sum;
namespace cactus {
    struct E { 
        int to, nxt; 
    } e[maxn * 2];
    int head[maxn], ecnt;
    void adde(int u, int v) {
        e[++ecnt] = {v, head[u]};
        head[u] = ecnt;
    }
    int tot, dfn[maxn], fa[maxn];
    bool ring[maxn];
    void clear(int n) { 
        cnt = ecnt = tot = sum = 0; ans = 1;
        for (int i = 1; i <= n; i++) {
            head[i] = dfn[i] = 0;
            ring[i] = false;
        }
    }
    void dfs(int u, int f) {
        dfn[u] = ++tot;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (v == f) continue;
            if (!dfn[v]) {
                fa[v] = u; ring[u] = false;
                dfs(v, u);
            } else if (dfn[v] < dfn[u]) {
                cnt++; 
                int c = 1;
                for (int x = u; x != v; x = fa[x]) {
                    ring[x] = true; c++;
                }
                ans = mul(ans, sub(qpow(2, c), 1));
                sum += c;
                ring[v] = true;
            }
        }
    }
    void build(int n) {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                dfs(i, 0);
            }
        }
    }
}

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

int n, m;

int main() {
    two[0] = 1;
    for (int i = 1; i < maxn; i++) two[i] = mul(2, two[i - 1]);
    // int T; scanf("%d", &T);
    // int T = gi();
    while (scanf("%d%d", &n, &m) == 2) {
        // scanf("%d%d", &n, &m);
        // n = gi(); m = gi();
        cactus::clear(n);
        for (int i = 1, u, v; i <= m; i++) {
            // scanf("%d%d", &u, &v);
            u = gi(); v = gi();
            cactus::adde(u, v);
            cactus::adde(v, u);
        }
        cactus::build(n);
        ans = mul(ans, qpow(2, m - sum));
        printf("%d\n", ans);
    }
    return 0;
}