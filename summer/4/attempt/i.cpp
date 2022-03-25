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

int vis[maxn], fa[maxn], hcol;
vector<PII> stk;
vector<int> onring;
map<int,int> ringc;
bool dfs(int u, int f) {
    vis[u] = 1;
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        if (vis[v]) {
            onring.push_back(u);
            hcol = v;
            return true;
        }
        if (dfs(v, u)) {
            if (hcol > 0) onring.push_back(u);
            if (hcol == u) hcol = 0;
            return true;
        }
    }
    return false;
}
// void dfs(int u, int f) {
//     vis[u] = 1; fa[u] = f;
//     for (auto& x: edge[u]) {
//         int v = x.first;
//         if (v == f) continue;
//         if (vis[v]) {
//             if (!onring.empty()) continue;
//             int x = u;
//             onring.push_back(v);
//             while (x != v) {
//                 onring.push_back(x);
//                 x = fa[x];
//             }
//             // for (int i = (int)stk.size() - 1; i >= 0; i--) {
//             //     if (stk[i].first == v) break;
//             //     onring.push_back(stk[i].first);
//             //     ringc[stk[i].second]++;
//             // }
//             // onring.push_back(v);
//             // ringc[x.second]++;
//             continue;
//         }
//         stk.push_back({ x.first, x.second });
//         dfs(v, u);
//         stk.pop_back();
//     }
//     vis[u] = 0;
// }

void clear() {
    hcol = 0;
    for (int i = 1; i <= n; i++) {
        vis[i] = ring[i] = fa[i] = 0;
        edge[i].clear(); cnt[i].clear();
    }
    col.clear(); ringc.clear();
    stk.clear(); onring.clear();
}

void update(int u, int v, int c) {
    // dbg(cnt[u].size(), cnt[v].size());
    ans -= (int)cnt[u].size() + (int)cnt[v].size();
    int sc = col[{u, v}];
    cnt[u][sc]--; if (cnt[u][sc] == 0) cnt[u].erase(cnt[u].find(sc));
    cnt[v][sc]--; if (cnt[v][sc] == 0) cnt[v].erase(cnt[v].find(sc));
    cnt[u][c]++; cnt[v][c]++;
    ans += (int)cnt[u].size() + (int)cnt[v].size();
    // dbg(cnt[u].size(), cnt[v].size());
    if (ring[u] && ring[c]) {
        ringc[sc]--; if (ringc[sc] == 0) ringc.erase(ringc.find(sc));
        ringc[c]++; 
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
            cnt[u][w]++; cnt[v][w]++;
            edge[u].push_back({v, w});
            edge[v].push_back({u, w});
        }
        dfs(1, 0);
        // dbg(ringc.size());
        // for (auto& x: ringc) {
        //     dbg(x.first, x.second);
        // }
        for (auto& x: onring) {
            ring[x] = 1;
            // dbg(x);
        }
        ans = -n; 
        for (int i = 1; i <= n; i++) {
            ans += (int)cnt[i].size();
        }
        printf("Case #%d:\n", ++kase);
        while (q--) {
            int u, v, c; scanf("%d%d%d", &u, &v, &c);
            if (u > v) swap(u, v);
            // dbg(u, v, c);
            if (col[{u, v}] != c) update(u, v, c);
            col[{u, v}] = c;
            printf("%d\n", ans + int((int)ringc.size() == 1));
        }
        clear();
    }
    return 0;
}