#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
const int maxn = 100000 + 5;

int n;
vector<int> edge[maxn];

int dep[maxn], lp[maxn], dia[maxn], tag[maxn];
int predfs(int u, int f) {
    int r = 0; dep[u] = lp[u] = 0;
    for (int v: edge[u]) {
        if (v == f) continue;
        r = max(r, predfs(v, u));
        lp[u] = max(lp[u], dep[u] + dep[v] + 1);
        dep[u] = max(dep[u], dep[v] + 1);
    }
    return dia[u] = max(r, lp[u]);
}

int fad[maxn];
void dfs(int u, int f) {
    multiset<int> st;
    if (u != 1) st.insert(fad[u]);
    for (int v: edge[u]) {
        if (v == f) continue;
        st.insert(dep[v] + 1);
    }

    for (int v: edge[u]) {
        if (v == f) continue;

        st.erase(st.find(dep[v] + 1));
        auto it = st.end();
        int out = 1, mx = 1;
        if (it != st.begin()) {
            it--; out += *it; mx += *it;
            if (it != st.begin()) {
                it--; out += *it;
            }
        }

        fad[v] = mx;
        tag[dia[v] + 1] = max(tag[dia[v] + 1], out);
        tag[out] = max(tag[out], dia[v] + 1);
        // dbg(u, v);
        // dbg(dia[v] + 1, mx);

        st.insert(dep[v] + 1);

        dfs(v, u);
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            edge[i].clear(); tag[i] = 0;
        }
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        int mxdia = predfs(1, 0) + 1;
        dbg(mxdia);
        dfs(1, 0);

        ll ans = 0;
        for (int i = mxdia; i >= 1; i--) {
            if (i < mxdia) tag[i] = max(tag[i + 1], tag[i]);
            ans += tag[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}