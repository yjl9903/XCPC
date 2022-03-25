#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
const ll inf = 1ll << 40;
const int maxn = 100000 + 5;

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

int n, k, siz[maxn];
vector<PII> edge[maxn];

ll f[maxn][105], tmp[105];
void dfs(int u, int ff) {
    if ((int)edge[u].size() == 1) {
        f[u][1] = f[u][0] = 0;
        siz[u] = 1;
    }
    for (PII x: edge[u]) {
        int v = x.first, w = x.second;
        if (v == ff) continue;
        dfs(v, u);
        for (int i = 0; i <= k && i <= siz[u] + siz[v]; i++) tmp[i] = inf;
        for (int i = 0; i <= siz[u] && i <= k; i++) {
            for (int j = 0; i + j <= k && j <= siz[v]; j++) {
                ll tot = f[u][i] + f[v][j] + 1ll * j * (k - j) * w;
                tmp[i + j] = min(tmp[i + j], tot);
            }
        }
        siz[u] += siz[v];
        for (int i = 1; i <= k && i <= siz[u]; i++) f[u][i] = tmp[i];
    }
}

int main() {
    int T = gi(), kase = 0;
    while (T--) {
        n = gi(); k = gi();
        for (int i = 1; i <= n; i++) {
            edge[i].clear(); siz[i] = 0;
            for (int j = 1; j <= k; j++) {
                f[i][j] = inf;
            }
        }
        for (int i = 2, u, v, w; i <= n; i++) {
            u = gi(); v = gi(); w = gi();
            edge[u].push_back({v, w});
            edge[v].push_back({u, w});
        }
        printf("Case #%d: ", ++kase);
        if (k == 1) {
            puts("0"); continue;
        }
        if (n == 2) {
            printf("%d\n", edge[1][0].second); continue;
        }
        int rt = 1;
        for (int i = 1; i <= n; i++) {
            if ((int)edge[i].size() > 1) {
                rt = i; break;
            }
        }
        dfs(rt, 0);
        printf("%lld\n", f[rt][k]);
    }
    return 0;
}