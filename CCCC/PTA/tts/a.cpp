#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500 + 5;

struct node{
    int to, d;
    bool operator< (const node& b)const{
        return d > b.d;
    }
};

vector<PII> g[2][maxn];
int n, m;

int vis[maxn], dis[3][maxn], pre[2][maxn];
void dijkstra(int s, int* dis, int* pre, vector<PII>* edge, vector<PII>* eg2, int k, int* dis2) {
    for (int i = 0; i <= n; i++) dis[i] = inf, vis[i] = 0;
    if (k) for (int i = 0; i <= n; i++) dis2[i] = 1;
    priority_queue<node> q; q.push({s, 0}); dis[s] = 0;
    while (!q.empty()) {
        node t = q.top(); q.pop();
        if (vis[t.to]) continue;
        vis[t.to] = 1;
        // for (auto& x: edge[t.to]) {
        for (int i = 0; i < (int)edge[t.to].size(); i++) {
            int v = edge[t.to][i].first, d = edge[t.to][i].second;
            if (vis[v]) continue;
            if (dis[v] > dis[t.to] + d) {
                dis[v] = dis[t.to] + d;
                if (k) dis2[v] = dis2[t.to] + 1;
                pre[v] = t.to;
                q.push({v, dis[v]});
            } else if (dis[v] == dis[t.to] + d) {
                if (k) {
                    if (dis2[v] > dis2[t.to] + 1) {
                        dis2[v] = dis2[t.to] + 1;
                        pre[v] = t.to;
                        q.push({v, dis[v]});
                    }
                } else {
                    if (dis2[v] > dis2[t.to] + eg2[t.to][i].second) {
                        dis2[v] = dis2[t.to] + eg2[t.to][i].second;
                        pre[v] = t.to;
                        q.push({v, dis[v]});
                    }
                }
            }
        }
    }
}

vector<int> get(int s, int t, int* pre) {
    vector<int> v;
    int tot = t;
    while (true) {
        v.push_back(tot);
        if (tot == s) break;
        tot = pre[tot];
    }
    reverse(v.begin(), v.end());
    return v;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, k, l, t; i <= m; i++) {
        scanf("%d%d%d%d%d", &u, &v, &k, &l, &t);
        g[0][u].push_back({v, l});
        g[1][u].push_back({v, t});
        if (k == 0) {
            g[0][v].push_back({u, l});
            g[1][v].push_back({u, t});
        }
    }
    int s, t; scanf("%d%d", &s, &t);
    dijkstra(s, dis[1], pre[1], g[0], g[1], 1, dis[2]);
    vector<int> v2 = get(s, t, pre[1]);
    dijkstra(s, dis[0], pre[0], g[1], g[0], 0, dis[1]);
    vector<int> v1 = get(s, t, pre[0]);
    
    if (v1 == v2) {
        printf("Time = %d; ", dis[0][t]);
        printf("Distance = %d:", dis[1][t]);
        for (int i = 0; i < (int)v1.size(); i++) {
            printf(" %d", v1[i]);
            if (i + 1 < (int)v1.size()) {
                printf(" =>");
            }
        }
    } else {
        printf("Time = %d:", dis[0][t]);
        for (int i = 0; i < (int)v1.size(); i++) {
            printf(" %d", v1[i]);
            if (i + 1 < (int)v1.size()) {
                printf(" =>");
            }
        } puts("");
        printf("Distance = %d:", dis[1][t]);
        for (int i = 0; i < (int)v2.size(); i++) {
            printf(" %d", v2[i]);
            if (i + 1 < (int)v2.size()) {
                printf(" =>");
            }
        }
    }
    return 0;
}