#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20 + 5;

int G[maxn][3], m, vis[maxn], cnt = 0, res[maxn];
vector<vector<vector<int> > > path;

void dfs(int p, int s){
    if (s == 21 && p == m){
        // cout << ++cnt << ":";
        // for (int i = 0; i < 21; i++){
        //     cout << " " << res[i];
        // }
        // cout << endl;
        vector<int> t;
        for (int i = 0; i < 21; i++)
            t.push_back(res[i]);
        path[m].push_back(t);
        return;
    }
    else if (s ==  21 || (p == m && s > 1)){
        return;
    }

    for (int i = 0; i < 3; i++){
        int v = G[p][i];
        // cout << p << ' ' << v << endl;
        if (!vis[v] && v != p){
            vis[v] = 1; res[s] = v;
            dfs(v, s + 1);
            vis[v] = 0;
        }
    }
}

int main(){
    ms(G, 0);
    for (int i = 1, x, y, z; i <= 20; i++){
        cin >> x >> y >> z;
        G[i][0] = x;
        G[i][1] = y;
        G[i][2] = z;
        sort(G[i], G[i] + 3);
    }
    path.resize(21);
    for (int i = 1; i <= 20; i++){
        m = i; res[0] = m;
        dfs(i, 1);
    }
    while (cin >> m && m){
        // res[0] = m;
        // dfs(m, 1);
        for (int i = 0; i < path[m].size(); i++){
            cout << i + 1 << ": ";
            for (int j = 0; j < 21; j++){
                cout << ' ' << path[m][i][j];
            }
            cout << endl;
        }
    }
    return 0;
}