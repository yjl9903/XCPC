#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20 + 5;

int G[maxn][maxn], vis[maxn], path[maxn], n, cnt = 0;
int pre[maxn];

int find(int x){return x == pre[x] ? x : pre[x] = find(pre[x]);}
void join(int x, int y){
    x = find(x); y = find(y);
    pre[y] = x;
}
void dfs2(int p){
    for (int i = 0; i <= 20; i++) if (G[p][i] && !vis[i]){
        vis[i] = 1;
        join(p, i);
        dfs2(i);
    }
}

void dfs(int p, int d){
    if (p == n){
        cout << 1;
        for (int i = 1; i < d; i++)
            cout << " " << path[i];
        cout << endl;
        cnt++;
        return;
    }
    for (int i = 1; i <= 20; i++) if (G[p][i] && !vis[i]){
        vis[i] = 1;
        path[d] = i;
        dfs(i, d + 1);
        vis[i] = 0;
    }
}

int main(){
    int kase = 0;
    while (cin >> n){
        ms(G, 0); ms(vis, 0); cnt = 0;
        for (int i = 0; i < maxn; pre[i] = i, i++);
        int x, y;
        while (cin >> x >> y && x && y){
            G[x][y] = G[y][x] = 1;
        }
        dfs2(1);
        cout << "CASE " << ++kase << ":\n";
        if (find(1) != find(n)){
            cout << "There are "<< 0 << " routes from the firestation to streetcorner " << n << ".\n";
            continue;
        }
        path[0] = 1; ms(vis, 0); vis[1] = 1; 
        dfs(1, 1);
        cout << "There are "<< cnt << " routes from the firestation to streetcorner " << n << ".\n";
    }
    return 0;
}