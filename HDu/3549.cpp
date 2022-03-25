#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const int inf = 1 << 30;

int to[maxn * 2], nxt[maxn * 2], flow[maxn * 2], head[maxn], tot;
void add(int x, int y, int w){
    to[++tot] = y; nxt[tot] = head[x]; flow[tot] = w;
    head[x] = tot;
    to[++tot] = x; nxt[tot] = head[y]; flow[tot] = 0;
    head[y] = tot;
}

int n, m, tag;

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

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        ms(head, 0); tot = 1;
        scanf("%d%d", &n, &m);
        while (m--){
            int x, y, c; scanf("%d%d%d", &x, &y, &c);
            add(x, y, c);
        }
        printf("Case %d: %d\n", ++kase, dinic(1, n));
    }
    return 0;
}