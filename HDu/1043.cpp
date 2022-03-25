#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <queue>
#include <vector>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 362880 + 5;
const int HashSize = 5000003;

int st[maxn][9], shash[maxn], pre[maxn], vis[maxn];
int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1}, f[10];

void init(){
    f[0] = f[1] = 1;
    for (int i = 2; i < 9; i++)
        f[i] = f[i - 1] * i;
    ms(vis, 0);
    ms(pre, 0);
    for (int i = 0; i < 8; i++)
        st[1][i] = i + 1;
    st[1][8] = 0;
}
int cantor(int x[]){
    int s = 0;
    for (int i = 0; i < 9; i++){
        int t = 0;
        for (int j = i + 1; j < 9; j++)
            if (x[i] > x[j])
                t++;
        s += f[8 - i] * t;
    }
    return s;
}
void show(int x[9])
{
    for (int i = 0; i < 9; i++)
    {
        if (i && i % 3 == 0)
            cout << endl;
        cout << x[i] << ' ';
    }
    cout << endl
         << cantor(x) << endl;
}

int bfs(){
    queue<int> q;
    q.push(1); vis[cantor(st[1])] = 1; shash[cantor(st[1])] = 1;
    int cnt = 1;
    while (!q.empty()){
        int t = q.front(), tx, ty, x, y; q.pop();
        // show(st[t]);
        for (int i = 0; i < 9; i++)
            if (!st[t][i])
                tx = i / 3, ty = i % 3;
        for (int i = 0; i < 4; i++){
            x = tx + dir[i][0]; y = ty + dir[i][1];
            if (x < 0 || y < 0 || x > 2 || y > 2) continue;
            memcpy(st[++cnt], st[t], sizeof st[t]);
            swap(st[cnt][tx * 3 + ty], st[cnt][x * 3 + y]);
            int v = cantor(st[cnt]);
            if (!vis[v]){
                vis[v] = 1;
                q.push(cnt);
                pre[cnt] = t;
                shash[v] = cnt;
            }
            else{
                cnt--;
            }
        }
    }
    return 0;
}

int main()
{
    init();
    bfs();
    char s[25];
    while (cin.getline(s, 30))
    {
        stringstream ss(s);
        int x[10]; char t;
        for (int i = 0; i < 9; i++){
            ss >> t;
            if (t == 'x')
                x[i] = 0;
            else 
                x[i] = t - '0';
        }
        int c = cantor(x);
        if (!vis[c]){
            cout << "unsolvable\n";
            continue;
        }
        // cout << shash[c] << endl << pre[shash[c]] << endl;
        int u = pre[shash[c]], f = shash[c]; vector<char> path;
        while (u){
            int t1, t2;
            // show(st[u]);
            for (int i = 0; i < 9; i++)
                if (st[u][i] == 0) t1 = i;
            for (int i = 0; i < 9; i++)
                if (st[f][i] == 0) t2 = i;
            if (t1 - t2 == 1)
                path.push_back('r');
            if (t1 - t2 == -1)
                path.push_back('l');
            if (t1 - t2 == 3)
                path.push_back('d');
            if (t1 - t2 == -3)
                path.push_back('u');
            f = u;
            u = pre[u];          
        }
        for (int i = 0; i < path.size(); i++)
            cout << path[i];
        cout << endl;
        // if (path.size()) cout << endl;
        // else cout << "r\n";
    }
    return 0;
}