#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10000 + 5;
const int maxm = 2000000 + 5;

struct edge{
    int to, nxt;
}f[maxm];
int head[maxn], cnt;
void add(int x, int y){
    f[++cnt].to = y; f[cnt].nxt = head[x]; head[x] = cnt;
}

int n, m, vis[maxn], pre[maxn];

int bfs(){
    ms(vis, 0); ms(pre, 0); vis[1] = 1;
    queue<int> q; q.push(1);
    int ans = 0;
    while (!q.empty()){
        int t = q.front(); q.pop();
        for (int i = head[t]; i; i = f[i].nxt) pre[f[i].to] = t;
        for (int i = 1; i <= n; i++){
            if (vis[i] || pre[i] == t) continue;
            vis[i] = 1; ans++; q.push(i);
        }
    }
    return ans;
}

int main(){
    int kase = 0;
    while (~scanf("%d%d", &n, &m)){
        if (!n && !m) break;
        cnt = 0; ms(head, 0);
        while (m--){
            int x, y; scanf("%d%d", &x, &y);
            add(x, y); add(y, x);
        }
        printf("Case %d: %d\n", ++kase, bfs());
    }
    return 0;
}