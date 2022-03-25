#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 5000 + 5;
const int maxm = 300000 + 10;
 
struct HK {
    int n, ans;
    int dx[maxn], dy[maxn];
    int linkx[maxn], linky[maxn];
    int head[maxn], to[maxm], nxt[maxm], ecnt;
 
    void clear(int N) {
        n = N; ecnt = ans = 0;
        ms(linkx, 0xff); ms(linky, 0xff);
    }
    void add(int u, int v) {
        to[++ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt;
        if(linkx[u] == -1 && linky[v] == -1) {
            linkx[u] = v;
            linky[v] = u;
            ans++;
        }
    }
    bool bfs() {
        bool res = 0;
        static int q[maxn], l, r;
 
        ms(dx, 0); ms(dy, 0);
        l = r = 0;
        for (int i = 0; i < n; i++) 
            if(linkx[i] == -1) q[r++] = i;
 
        while(l < r) {
            int x = q[l++];
            for (int i = head[x]; i; i = nxt[i]) {
                if(!dy[to[i]]) {
                    dy[to[i]] = dx[x] + 1;
                    if(linky[to[i]] == -1) res = 1;
                    else dx[q[r++] = linky[to[i]]] = dy[to[i]] + 1;
                }
            }
        }
        return res;
    }
    bool dfs(int u) {
        for (int i = head[u]; i; i = nxt[i]) {
            if(dx[u] + 1 == dy[to[i]]) {
                dy[to[i]] = 0;
                if(linky[to[i]] == -1 || dfs(linky[to[i]])) {
                    linky[to[i]] = u;
                    linkx[u] = to[i];
                    return true;
                }
            }
        }
        return false;
    }
    int match() {
        while(bfs()) {
            for (int i = 0; i < n; i++) {
                if(linkx[i] == -1) ans += dfs(i);
            }
        }
        return ans;
    }

    bool visx[maxn], visy[maxn];
    void mark(int u) {
        if (visx[u]) return ;
        visx[u] = true;
        for (int i = head[u]; i; i = nxt[i]) {
            if (to[i] == linkx[u]) continue;
            visy[to[i]] = true;
            assert(linky[to[i]] != -1);
            mark(linky[to[i]]);
        }
    }
} f;

int n;

int main() {
    scanf("%d", &n);
    vector<int> bag[2];
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        bag[__builtin_parity(x)].push_back(x);
    }
    f.clear((int)bag[0].size());
    for (int i = 0; i < (int)bag[0].size(); i++) {
        for (int j = 0; j < (int)bag[1].size(); j++) {
            int x = bag[0][i], y = bag[1][j];
            if (__builtin_popcount(x ^ y) <= 1) {
                f.add(i, j);
            }
        }
    }
    int ans = n - f.match();
    printf("%d\n", ans);
    for (int i = 0; i < (int)bag[0].size(); i++) {
        if (f.linkx[i] == -1) {
            f.mark(i);
        }
    }
    vector<int> plan;
    for (int i = 0; i < (int)bag[0].size(); i++) if (f.visx[i]) plan.push_back(bag[0][i]);
    for (int i = 0; i < (int)bag[1].size(); i++) if (!f.visy[i]) plan.push_back(bag[1][i]);
    for (int x: plan) printf("%d ", x);
    return 0;
}