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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

vector<int> G[maxn], bcc[maxn];
int nn, n, m;

namespace cactus {
    struct E { 
        int to, nxt; 
    } e[maxn * 2];
    int head[maxn], ecnt;
    void add(int u, int v) {
        e[++ecnt] = {v, head[u]};
        head[u] = ecnt;
    }
    int tot, dfn[maxn], fa[maxn];
    bool ring[maxn];
    void clear() { 
        ms(head, 0);
        nn = ecnt = tot = 0;
    }
    void dfs(int u, int f) {
        dbg(u, fa[u]);
        dfn[u] = ++tot;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (v == f) continue;
            if (!dfn[v]) {
                fa[v] = u; ring[u] = false;
                dfs(v, u);
                if (!ring[u]) { 
                    G[u].push_back(v); G[v].push_back(u); 
                }
            } else if (dfn[v] < dfn[u]) {
                dbg(u, v);
                nn++; int rt = nn + n;
                G[rt].push_back(v); 
                G[v].push_back(rt);
                bcc[nn].push_back(v);
                for (int x = u; x != v; x = fa[x]) {
                    ring[x] = true;
                    bcc[nn].push_back(x);
                    G[rt].push_back(x); 
                    G[x].push_back(rt);
                }
                ring[v] = true;
            }
        }
    }
    void build() {
        for (int i = 1; i <= nn; i++) {
            dbg(i);
            for (int x: bcc[i]) {
                dbg(x);
            }
        }
    }
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        cactus::clear();
        scanf("%d%d", &n, &m);
        for (int i = 1, u, v, a, b; i <= m; i++) {
            scanf("%d%d%d%d", &u, &v, &a, &b);
            cactus::add(u, v);
            cactus::add(v, u);
        }
        cactus::dfs(1, 0);
        cactus::build();
    }
    return 0;
}