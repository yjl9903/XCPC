#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int inf = 1e9 + 7;
const int maxn = 2000 + 5;

int n, m, a[maxn];
map<int,int> mp;

int to[maxn * 2], nxt[maxn * 2], flow[maxn * 2], head[maxn], tot;
void add(int x, int y, int w){
    to[++tot] = y; nxt[tot] = head[x]; flow[tot] = w;
    head[x] = tot;
    to[++tot] = x; nxt[tot] = head[y]; flow[tot] = 0;
    head[y] = tot;
}

int tag, u[maxn], v[maxn];

int dep[maxn];
int bfs(int s, int t){
    queue<int> q;
    ms(dep, 0);
    dep[s] = 1; q.push(s);
    while (!q.empty()){
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = nxt[i]){
            int v = to[i];
            if (flow[i] && dep[v] == 0){
                dep[v] = dep[u] + 1;
                q.push(v);
            }
        }
    }
    return dep[t];
}
int dfs(int u, int fl){
    if (u == tag) return fl;
    int f = 0;
    for (int i = head[u]; i && fl; i = nxt[i]){
        int v = to[i];
        if (dep[v] == dep[u] + 1 && flow[i]){
            int x = dfs(v, min(fl, flow[i]));
            flow[i] -= x; flow[i ^ 1] += x;
            fl -= x; f += x;
        }
    }
    if (!f) dep[u] = -1;
    return f;
}
int dinic(int s, int t){
    int ans = 0; tag = t;
    while (bfs(s, t)){
        ans += dfs(s, inf);
    }
    return ans;
}
int cal(int x) {
    ms(head, 0); tot = 1;
    for (int i = 1; i <= n; i++) {
        int c = 0;
        while (a[i] % x == 0) a[i] /= x, c++;
        if (!c) continue;
        if (i % 2 == 1) add(0, i, c);
        else add(i, n + 1, c);
    }
    for (int i = 1; i <= m; i++) add(u[i], v[i], inf);
    return dinic(0, n + 1);
}

void get(int x) {
    for (int j = 2; j * j <= x; j++) {
        if (x % j) continue;
        int c = 0;
        while (x % j == 0) x /= j, c++;
        mp[j] += c;
    }
    if (x > 1) mp[x]++;
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), get(a[i]);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", u + i, v + i);
        if (u[i] % 2 == 0) swap(u[i], v[i]);
    }
    ll ans = 0;
    for (auto& x: mp) {
        ans += cal(x.first);
        // cout << ans << endl;
    }
    cout << ans << endl;
    return 0;
}