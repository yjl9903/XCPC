#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, m, id, head[maxn];
struct edge{
    int to, nxt, c;
}f[4 * maxn];
void add(int x, int y, int c){
    f[++id].to = y; f[id].nxt = head[x]; head[x] = id;
    f[id].c = c;
}

int dis[maxn];
struct node{
    int p, d, c;
    bool operator <(const node &b)const{
        return d > b.d;
    }
};
int bfs(){
    priority_queue<node> q;
    ms(dis, -1); dis[1] = 0;
    q.push({1, 0, 0});
    while (!q.empty()){
        node x = q.top(); q.pop();
        if (x.p == n) return x.d;
        for (int i = head[x.p]; i; i = f[i].nxt){
            int v = f[i].to;
            node tmp = {v, x.d, f[i].c};
            if (x.c != tmp.c) tmp.d++;
            if (dis[v] == -1 || tmp.d < dis[v])
                q.push(tmp), dis[v] = tmp.d;
        }
    }
    return -1;
}

int main(){
    while (scanf("%d%d", &n, &m) == 2){
        id = 0; ms(head, 0);
        while (m--){
            int x, y, c; scanf("%d%d%d", &x, &y, &c);
            add(x, y, c); add(y, x, c);
        }
        printf("%d\n", bfs());
    }
    return 0;
}