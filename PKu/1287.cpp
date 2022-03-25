#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

struct edge{
    int to, nxt, d;
    bool operator<(const edge& b)const {
        return d > b.d;
    }
}f[20 * maxn];
int head[maxn], tot = 0;
void add(int x, int y, int d){
    f[++tot].to = y; f[tot].d = d; f[tot].nxt = head[x]; head[x] = tot;
}

int p, r, vis[maxn];
int prim(){
    ms(vis, 0); vis[1] = 1;
    priority_queue<edge> q;
    int ans = 0;
    for (int i = head[1]; i; i = f[i].nxt){
        q.push(f[i]);
    }
    while (!q.empty()){
        edge t = q.top(); q.pop();
        if (vis[t.to]) continue;
        vis[t.to] = 1;
        ans += t.d;
        for (int i = head[t.to]; i; i = f[i].nxt){
            q.push(f[i]);
        }
    }
    return ans;
}

int main(){
    while (scanf("%d%d", &p, &r) == 2 && p){
        ms(head, 0); tot = 0;
        while (r--){
            int x, y, d; scanf("%d%d%d", &x, &y, &d);
            add(x, y, d); add(y, x, d);
        }
        printf("%d\n", prim());
    }
    return 0;
}