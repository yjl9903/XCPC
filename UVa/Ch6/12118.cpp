#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int G[maxn][maxn], pre[maxn], vis[maxn], V, E, T, res, cnt;
vector<int> s;

void init(){
    for (int i = 1; i <= V; i++)
        pre[i] = i;
}
int find(int x){return x == pre[x] ? x : pre[x] = find(pre[x]);}
void join(int x, int y){
    x = find(x);    y = find(y);
    pre[x] = y;
}

void dfs(int p, int v){
    // cout << p << endl;
    if (p > V){
        if (!s.empty()){
            int sum = 0, sum2 = 0;
            for (int i = 0; i < s.size(); i++){
                int t = 0;
                for (int j = 0; j < s.size(); j++){
                    if (G[s[i]][s[j]])
                        t++;
                }
                sum2 += t;
                if (t % 2)  sum++;
            }
            sum2 /= 2;
            res += sum2;
            if (sum > 2)
                res += sum / 2 - 1;
            // cout << res << endl;
            // for (int i = 0; i < s.size(); cout << s[i++] << ' ');
            // cout << endl;
            if (sum2)
                cnt++;
            s.clear();
        }
    }
    else if (!vis[p]){
        if (pre[p] == v)
            vis[p] = 1, s.push_back(p);
        dfs(p + 1, v);
        if (!vis[p] && pre[p] != v) 
            vis[p] = 1, s.push_back(p), dfs(1, pre[p]);
    }
    else    dfs(p + 1, v);
}

int main(){
    int kase = 0;
    while (cin >> V >> E >> T){
        if (V == 0 && E == 0 && T == 0) return 0;
        memset(G, 0, sizeof G); memset(vis, 0, sizeof vis);
        for (int i = 0; i < E; i++){
            int x, y;
            cin >> x >> y;
            G[x][y] = G[y][x] = 1;
        }
        init(); res = 0;    cnt = 0;
        for (int i = 1; i <= V; i++){
            for (int j = 1; j <= V; j++){
                if (G[i][j])
                    join(i, j);
            }
        }
        for (int i = 1; i <= V; find(i++));
        dfs(1, pre[1]);
        if (cnt > 1)
            res += cnt - 1;
        cout << "Case " << ++kase << ": " << res * T << endl;
    }
    return 0;
}