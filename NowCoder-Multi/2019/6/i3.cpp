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
const int N = 100000 + 5;

vector<int> G[maxn], bcc[maxn];
int nn, n, m;

namespace cactus {
    struct E { 
        int to, nxt; 
    } e[maxn * 2];
    int hd[N], ecnt;
    void add(int u, int v) {
        e[ecnt] = {v, hd[u]};
        hd[u] = ecnt++;
    }
    int idx[N], clk, fa[N];
    bool ring[N];
    void init() { ecnt = 0; memset(hd, -1, sizeof hd); clk = 0; }
    void dfs(int u, int feid) {
        idx[u] = ++clk;
        for (int i = hd[u]; ~i; i = e[i].nxt) {
            if ((i ^ feid) == 1) continue;
            int v = e[i].to;
            if (!idx[v]) {
                fa[v] = u; ring[u] = false;
                dfs(v, i);
                if (!ring[u]) { G[u].push_back(v); G[v].push_back(u); }
            } else if (idx[v] < idx[u]) {
                ++nn;
                dbg(u, v, nn);
                G[nn].push_back(v); G[v].push_back(nn); // 强行把环的根放在最前面
                for (int x = u; x != v; x = fa[x]) {
                    ring[x] = true;
                    G[nn].push_back(x); G[x].push_back(nn);
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
        cactus::init();
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