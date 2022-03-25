#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200 + 5;

int G[maxn][maxn], d[maxn], nxt[maxn], vis[maxn], n, m;

bool check(){
    ms(vis, 0); 
    for (int i = 1; i <= n; i++) if (!vis[i]){
        queue<int> q; q.push(i); vis[i] = 1; d[i] = 0;
        while (!q.empty()){
            int x = q.front(); q.pop();
            for (int i = 1; i <= n; i++) 
                if (G[x][i] && !vis[i]){
                    vis[i] = 1; d[i] = (d[x] + 1) % 2;
                    q.push(i);
                }
                else if (G[x][i] && vis[i]){
                    if (d[x] == d[i]) return false;
                }
        }
    }
    return true;
}

int find(int p){
    for (int i = 1; i <= n; i++) if (d[i] == 1 && G[p][i] && !vis[i]){
        vis[i] = 1;
        if (!nxt[i] || find(nxt[i])){
            nxt[i] = p;
            return true;
        }
    }
    return false;
}
int match(){
    int sum = 0;
    for (int i = 1; i <= n; i++) if (d[i] == 0){
        ms(vis, 0);
        if (find(i)) sum++;
    }
    return sum;
}

int main(){
    while (cin >> n >> m){
        ms(G, 0); ms(nxt, 0);
        for (int i = 0; i < m; i++){
            int u, v; cin >> u >> v;
            G[u][v] = G[v][u] = 1;
        }
        if (!check()) {
            cout << "No" << endl;
            continue;
        }
        cout << match() << endl;
    }
    return 0;
}