#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <sstream>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 1000 + 5;
const int inf = 1 << 30;

int to[maxn * 2], nxt[maxn * 2], flow[maxn * 2], head[maxn], tot = 1;
void add(int x, int y, int w){
    to[++tot] = y; nxt[tot] = head[x]; flow[tot] = w;
    head[x] = tot;
    to[++tot] = x; nxt[tot] = head[y]; flow[tot] = 0;
    head[y] = tot;
}
void init() {
    ms(head, 0); tot = 1;
}

int dep[maxn], tag;
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

int n, m;
char tmp[2005];

int main() {
    scanf("%d%d", &m, &n);
    int sum = 0;
    for (int i = 1, x; i <= m; i++) {
        scanf("%d", &x);
        sum += x;
        add(n + m + 1, i, x);
        cin.getline(tmp, 2000);
        stringstream ss(tmp);
        while (ss >> x)  {
            add(i, m + x, inf);
        }
    }
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        add(m + i, n + m + 2, x);
    }
    int ans = sum - dinic(n + m + 1, n + m + 2);
    for (int i = 1, flag = 0; i <= m; i++) if (dep[i]) {
        if (flag) putchar(' ');
        printf("%d", i); flag = 1;
    }
    puts("");
    for (int i = m + 1, flag = 0; i <= n + m; i++) if (dep[i]) {
        if (flag) putchar(' ');
        printf("%d", i - m);
        flag = 1;
    }
    printf("\n%d", ans);
    return 0;
}