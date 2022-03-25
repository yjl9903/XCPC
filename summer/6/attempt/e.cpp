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

int n;
vector<int> edge[maxn];

int fa[maxn], vis[maxn], ring[maxn];
vector<int> onring;
void getring(int u, int f) {
    fa[u] = f;
    vis[u] = 1;
    for (int& v: edge[u]) {
        if (v == f) continue;
        if (vis[v]) {
            if (!onring.empty()) continue;
            onring.push_back(v);
            int x = u;
            while (x != v) {
                onring.push_back(x); x = fa[x];
            }
            continue;
        }
        getring(v, u);
    }
    vis[u] = 0;
}
int mxd = 0, p = 0;
int dfs(int u, int f, int d) {
    if (d > mxd) {
        mxd = d; p = u;
    } else if (d == mxd) {
        p = min(p, u);
    }
    int s = 1;
    for (int& v: edge[u]) {
        if (v == f) continue;
        if (ring[u] && ring[v]) continue;
        s += dfs(v, u, d + 1);
    }   
    return s;
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v); edge[v].push_back(u);
        }
        getring(1, 0);
        for (int x: onring) {
            dbg(x); ring[x] = 1;
        }
        vector<int> siz;
        vector<PII> ed;
        int allsz = 0;
        for (int x: onring) {
            mxd = -1; p = 0;
            int s = dfs(x, 0, 0);
            allsz += 2 * (s - 1);
            siz.push_back(s);
            ed.push_back({mxd, p});
            dbg(s, mxd, p);
        }
        int dis = inf, s = inf, t = inf;
        for (int i = 0; i < (int)onring.size(); i++) {
            int j = i + 1; if (j == (int)onring.size()) j = 0;
            int tot = (int)onring.size() - 1;
            tot += allsz; tot -= ed[i].first; tot -= ed[j].first;
            if (tot < dis) {
                dis = tot;
                s = min(ed[i].second, ed[j].second);
                t = max(ed[i].second, ed[j].second);
            } else if (tot == dis) {
                if (ed[i].second < s) {
                    s = ed[i].second;
                    t = ed[j].second;
                } else if (ed[i].second == s) {
                    t = min(t, ed[j].second);
                }
                if (ed[j].second < s) {
                    s = ed[j].second;
                    t = ed[i].second;
                } else if (ed[j].second == s) {
                    t = min(t, ed[i].second);
                }
            }
        }
        printf("Case #%d: %d %d %d\n", ++kase, dis, s, t);
        onring.clear();
        for (int i = 1; i <= n; i++) {
            edge[i].clear();
            ring[i] = vis[i] = fa[i] = 0;
        }
    }
    return 0;
}