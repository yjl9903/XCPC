#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

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

int n, m, a[maxn], dep[maxn], fa[maxn];
vector<PII> cam[maxn];
map<int,ll> g[maxn];

int main() {
    int T = gi();
    while (T--) {
        n = gi(); m = gi();
        for (int i = 1; i <= n; i++) {
            cam[i].clear(); g[i].clear();
        }
        for (int i = 2; i <= n; i++) {
            dep[i] = dep[fa[i] = gi()] + 1;
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            a[i] = gi(); ans += a[i];
        }
        for (int i = 1, x, k, c; i <= m; i++) {
            x = gi(); k = gi(); c = gi();
            cam[x].push_back({k, c});
        }
        for (int i = n; i >= 1; i--) {
            g[i][dep[i]] += a[i];
            for (auto& x: cam[i]) {
                int flow = x.second;
                int mxd = dep[i] + x.first;
                while (flow) {
                    auto it = g[i].upper_bound(mxd);
                    if (it == g[i].begin()) break;
                    it--;
                    ll tot = min(1ll * flow, it->second);
                    flow -= tot; ans -= tot;
                    it->second -= tot;
                    if (it->second == 0) g[i].erase(it->first);
                }
            }
            if (i > 1) {
                int f = fa[i];
                if ((int)g[i].size() > (int)g[f].size()) swap(g[i], g[f]);
                for (auto& x: g[i]) {
                    if (x.second) g[f][x.first] += x.second;
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}