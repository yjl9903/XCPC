#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 40000 + 5;

struct edege{
    int to, nxt;
}line[2 * maxn];
int n, m, head[maxn], cnt, vis[maxn];
int maxd, point;

void add(int x, int y){
    line[++cnt].to = y; line[cnt].nxt = head[x]; head[x] = cnt; 
}

void dfs1(int p, int d){
    if (d >= maxd){
        point = p;
    }
    for (int i = head[p]; i; i = line[i].nxt){
        // printf("%d %d\n", p, line[i].to);
        int v = line[i].to;
        if (!vis[v]){
            vis[v] = 1;
            dfs1(v, d + 1);
        }
    }
}
void dfs2(int p, int d){
    maxd = max(maxd, d);
    for (int i = head[p]; i; i = line[i].nxt){
        int v = line[i].to;
        if (!vis[v]){
            vis[v] = 1;
            dfs2(v, d + 1);
        }
    }
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &m);
        cnt = 0; ms(head, 0); maxd = 0;
        while (m--){
            int u, v; scanf("%d%d", &u, &v); add(u, v);  add(v, u);
        }

        ms(vis, 0); vis[1] = 1; dfs1(1, 0);
        printf("%d\n", point);
        
        ms(vis, 0); vis[point] = 1; dfs2(point, 0);
        printf("%d\n", maxd);
    }
    return 0;
}