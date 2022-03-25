#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <set>
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

vector<PII> edge[maxn];
int n, q, ans, ring[maxn];
map<PII,int> col;
map<int,int> cnt[maxn];

int vis[maxn], fa[maxn];
vector<PII> stk;
vector<int> onring;
map<int,int> ringc;
void dfs(int u, int f) {
    vis[u] = 1; fa[u] = f;
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        if (vis[v]) {
            if (!onring.empty()) continue;
            int x = u;
            onring.push_back(v);
            while (x != v) {
                onring.push_back(x);
                x = fa[x];
            }
            // for (int i = (int)stk.size() - 1; i >= 0; i--) {
            //     if (stk[i].first == v) break;
            //     onring.push_back(stk[i].first);
            //     // ringc[stk[i].second]++;
            // }
            // onring.push_back(v);
            // ringc[x.second]++;
            continue;
        }
        stk.push_back({ x.first, x.second });
        dfs(v, u);
        stk.pop_back();
    }
    vis[u] = 0;
}

void clear() {
    for (int i = 1; i <= n; i++) {
        vis[i] = ring[i] = fa[i] = 0;
        edge[i].clear(); cnt[i].clear();
    }
    col.clear(); ringc.clear();
    stk.clear(); onring.clear();
}

void del(int u, int v, int c) {
    if (ring[u] && ring[v]) {
        if (ringc[c] == (int)onring.size()) ans--;
        ringc[c]--; 
        // if (ringc[c] == 0) ringc.erase(ringc.find(c));
    }
    cnt[u][c]--; 
    // if (cnt[u][c] == 0) cnt[u].erase(cnt[u].find(c));
    cnt[v][c]--; 
    // if (cnt[v][c] == 0) cnt[v].erase(cnt[v].find(c));

    int mode = 0;
    if (cnt[u][c] > 0) mode++;
    if (cnt[v][c] > 0) mode++;

    if (mode == 2) ans++;
    else if (mode == 0) ans--;
} 
void add(int u, int v, int c) {
    int mode = 0;
    if (cnt[u][c] > 0) mode++;
    if (cnt[v][c] > 0) mode++;
    if (mode == 2) ans--;
    else if (mode == 0) ans++;
    // dbg(u, v, c, mode);
    cnt[u][c]++; cnt[v][c]++;

    if (ring[u] && ring[v]) {
        ringc[c]++;
        // if ((int)ringc.size() == 1) ans++;
        if (ringc[c] == (int)onring.size()) ans++;
    }
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &q);
        for (int i = 1, u, v, w; i <= n; i++) {
            scanf("%d%d%d", &u, &v, &w);
            if (u > v) swap(u, v);
            col[{u, v}] = w;
            // cnt[u][w]++; cnt[v][w]++;
            edge[u].push_back({v, w});
            edge[v].push_back({u, w});
        }
        dfs(1, 0);
        for (auto& x: onring) ring[x] = 1;
        // for (auto& x: onring) dbg(x);
        ans = 0;
        for (int i = 1; i <= n; i++) {
            for (auto& x: edge[i]) {
                int v = x.first;
                if (i >= v) continue;
                // dbg(i, v, x.second, ans);
                add(i, v, x.second);
                // dbg(i, v, ans);
            }
        }
        // dbg(ans, onring.size());
        printf("Case #%d:\n", ++kase);
        while (q--) {
            int u, v, c; scanf("%d%d%d", &u, &v, &c);
            if (u > v) swap(u, v);
            // dbg(u, v, c);
            if (col[{u, v}] != c) {
                del(u, v, col[{u, v}]);
                add(u, v, c);
                col[{u, v}] = c;
            }
            printf("%d\n", ans);
        }
        clear();
    }
    return 0;
}