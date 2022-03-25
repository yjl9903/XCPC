#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const int maxm = 100000 + 5;
const int inf = 1 << 30;

int to[maxm], nxt[maxm], flow[maxm], head[maxn], tot = 1;
void add(int x, int y, int d){
    to[++tot] = y; nxt[tot] = head[x]; flow[tot] = d;
    head[x] = tot;
    to[++tot] = x; nxt[tot] = head[y]; flow[tot] = 0;
    head[y] = tot; 
}
int n, f, d, tag;

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
    if (!f) dep[u] = -2;
    return f;
}
int dinic(int s, int t){
    int ans = 0;
    while (bfs(s, t)){
        ans += dfs(s, inf);
    }
    return ans;
}

int main(){
    scanf("%d%d%d", &n, &f, &d); tag = f + d + 2 * n + 2;
    dbg(tag);
    for (int i = 1; i <= f; i++) add(1, i + 1, 1);
    for (int i = 1; i <= d; i++) add(f + 1 + i, tag, 1);
    for (int i = 1; i <= n; i++){
        int a, b, x; scanf("%d%d", &a, &b);
        add(f + 1 + d + 2 * i - 1, f + 1 + d + 2 * i, 1);
        // dbg(f + 1 + d + 2 * i, f + 2 + d + 2 * i, 1);
        while (a--){
            scanf("%d", &x); 
            add(x + 1, f + 1 + d + 2 * i - 1, 1);
            dbg(x + 1, f + 1 + d + 2 * i - 1);
        }
        while (b--){
            scanf("%d", &x);
            add(f + 1 + d + 2 * i, f + 1 + x, 1);
            dbg(f + 1 + d + 2 * i, f + 1 + x);
        }
    }
    printf("%d\n", dinic(1, tag));
    return 0;
}