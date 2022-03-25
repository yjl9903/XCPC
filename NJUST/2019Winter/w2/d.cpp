#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 200000 + 5;
const int maxm = 200000 + 5;

char ss[maxn], tmp[maxn]; 
int n, len, a[maxn], cnt[maxn][26], sum[26];

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

int s, t;
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
    scanf("%s%d", ss, &n); len = strlen(ss);
    for (int i = 0; i < len; i++) sum[ss[i] - 'a']++;
    for (int i = 0; i < 26; i++) {
        add(1, i + 2, sum[i], 0);
    }
    for (int i = 0; i < n; i++) {
        scanf("%s%d", tmp, a + i);
        int l = strlen(tmp);
        for (int j = 0; j < l; j++) cnt[i][tmp[j] - 'a']++;
        for (int j = 0; j < 26; j++) {
            add(j + 2, 28 + i, cnt[i][j], i + 1);
        }
        add(28 + i, 3000, a[i], 0);
    }
    s = 1; t = 3000;
    mcmf();
    if (mf == len) cout << mc << endl;
    else puts("-1");
    // cout << mc << ' ' << mf << endl;
    return 0;
}