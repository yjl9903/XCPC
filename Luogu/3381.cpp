#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 5000 + 5;
const int maxm = 100000 + 5;

int head[maxn], tot = 1;
struct edge{
    int to, nxt, flow, cost;
}g[maxm];
void add(int x, int y, int f, int c){
    g[++tot] = edge{y, head[x], f, c};
    head[x] = tot;
    g[++tot] = edge{x, head[y], 0, -c};
    head[y] = tot;
}

int vis[maxn], cost[maxn], pre[maxn], flow[maxn], last[maxn], mf, mc;
bool spfa(int s, int t){
    ms(cost, 0x7f); ms(flow, 0x7f); ms(vis, 0);
    queue<int> q; q.push(s); vis[s] = 1; cost[s] = 0; pre[t] = -1;
    while (!q.empty()){
        int now = q.front(); q.pop(); vis[now] = 0;
        for (int i = head[now]; i; i = g[i].nxt){
            int v = g[i].to;
            if (g[i].flow > 0 && cost[v] > cost[now] + g[i].cost){
                cost[v] = cost[now] + g[i].cost;
                pre[v] = now; last[v] = i;
                flow[v] = min(flow[now], g[i].flow);
                if (!vis[v]){
                    vis[v] = 1; q.push(v);
                }
            }
        }
    }
    return pre[t] != -1;
}

int n, m, s, t;
void mcmf(){
    mc = mf = 0;
    while (spfa(s, t)){
        int now = t;
        mf += flow[t]; mc += flow[t] * cost[t];
        while (now != s){
            g[last[now]].flow -= flow[t];
            g[last[now] ^ 1].flow += flow[t];
            now = pre[now];
        }
    }
}

int main(){
    scanf("%d%d%d%d", &n, &m, &s, &t);
    while (m--){
        int x, y, f, c; scanf("%d%d%d%d", &x, &y, &f, &c);
        add(x, y, f, c);
    }
    mcmf();
    printf("%d %d", mf, mc);
    return 0;
}