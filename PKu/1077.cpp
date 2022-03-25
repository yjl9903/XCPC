#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <sstream>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 362880 + 5;

int st[maxn][9], f[10], vis[2][maxn], shash[2][maxn], pre[2][maxn];
int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};

void show(int x[9])
{
    for (int i = 0; i < 9; i++)
    {
        if (i && i % 3 == 0)
            cout << endl;
        cout << x[i] << ' ';
    }
    cout << endl << endl;
}

void init(){
    f[0] = f[1] = 1;
    for (int i = 2; i < 10; i++)
        f[i] = f[i - 1] * i;
}
int cantor(int x[]){
    int s = 0;
    for (int i = 0;i < 9; i++){
        int t = 0;
        for (int j =  i + 1; j < 9; j++)
            if (x[i] > x[j]) t++;
        s += t * f[8 - i];
    }
    return s;
}

int bfs(){
    ms(vis, 0); ms(pre, 0);
    queue<int> q[2]; int len[2] = {1, 1}, cnt = 2;
    q[0].push(1); q[1].push(2);
    vis[0][cantor(st[1])] = vis[1][cantor(st[2])] = 1;
    while (!q[0].empty() && !q[1].empty()){
        int p;
        if (len[0] < len[1]) p = 0;
        else p = 1;
        int t = q[p].front(), tx, ty, x, y; q[p].pop(); len[p]--;
        // show(st[t]);
        for (int i = 0; i < 9; i++)
            if (!st[t][i]) tx = i / 3, ty = i % 3;
        for (int i = 0; i < 4; i++){
            x = tx + dir[i][0]; y = ty + dir[i][1];
            if (x < 0 || y < 0 || x >= 3 || y >= 3) continue;
            memcpy(st[++cnt], st[t], sizeof st[t]);
            swap(st[cnt][3 * tx + ty], st[cnt][3 * x + y]);
            int c = cantor(st[cnt]);
            if (!vis[p][c]){
                vis[p][c] = 1;
                shash[p][c] = cnt;
                pre[p][cnt] = t;
                q[p].push(cnt); len[p]++;
                if (vis[p ^ 1][c]) return c;
            }
            else{
                cnt--;
            }
        }
    }
    while (!q[0].empty()){
        int p = 0;
        int t = q[p].front(), tx, ty, x, y;
        q[p].pop();
        for (int i = 0; i < 9; i++)
            if (!st[t][i])
                tx = i / 3, ty = i % 3;
        for (int i = 0; i < 4; i++)
        {
            x = tx + dir[i][0];
            y = ty + dir[i][1];
            if (x < 0 || y < 0 || x >= 3 || y >= 3)
                continue;
            memcpy(st[++cnt], st[t], sizeof st[t]);
            swap(st[cnt][3 * tx + ty], st[cnt][3 * x + y]);
            int c = cantor(st[cnt]);
            if (!vis[p][c])
            {
                vis[p][c] = 1;
                shash[p][c] = cnt;
                pre[p][cnt] = t;
                q[p].push(cnt);
                if (vis[p ^ 1][c])
                    return c;
            }
            else
            {
                cnt--;
            }
        }
    }
    while (!q[1].empty()){
        int p = 1;
        int t = q[p].front(), tx, ty, x, y;
        q[p].pop();
        for (int i = 0; i < 9; i++)
            if (!st[t][i])
                tx = i / 3, ty = i % 3;
        for (int i = 0; i < 4; i++)
        {
            x = tx + dir[i][0];
            y = ty + dir[i][1];
            if (x < 0 || y < 0 || x >= 3 || y >= 3)
                continue;
            memcpy(st[++cnt], st[t], sizeof st[t]);
            swap(st[cnt][3 * tx + ty], st[cnt][3 * x + y]);
            int c = cantor(st[cnt]);
            if (!vis[p][c])
            {
                vis[p][c] = 1;
                shash[p][c] = cnt;
                pre[p][cnt] = t;
                q[p].push(cnt);
                if (vis[p ^ 1][c])
                    return c;
            }
            else
            {
                cnt--;
            }
        }
    }
    return -1;
}

int main(){
    init();
    char s[30]; cin.getline(s, 30);
    stringstream ss(s);
    for (int i = 0; i < 9; i++){
        char x;
        ss >> x;
        if (x == 'x')
            st[1][i] = 0;
        else
            st[1][i] = x - '0';
        st[2][i] = i + 1;
    }
    st[2][8] = 0;
    int flag = bfs();
    if (flag == -1){
        cout << "unsolvable\n";
        return 0;
    } 
    int f = pre[0][shash[0][flag]], u = shash[0][flag];
    vector<char> path;
    while (f){
        // show(st[f]);
        int t1, t2;
        for (int i = 0; i < 9; i++)
            if (st[u][i] == 0)
                t1 = i;
        for (int i = 0; i < 9; i++)
            if (st[f][i] == 0)
                t2 = i;
        if (t1 - t2 == 1)
            path.push_back('r');
        if (t1 - t2 == -1)
            path.push_back('l');
        if (t1 - t2 == 3)
            path.push_back('d');
        if (t1 - t2 == -3)
            path.push_back('u');
        u = f;
        f = pre[0][f];
    }
    reverse(path.begin(), path.end());
    f = shash[1][flag], u = pre[1][shash[1][flag]];
    while (u)
    {
        // show(st[u]);
        int t1, t2;
        for (int i = 0; i < 9; i++)
            if (st[u][i] == 0)
                t1 = i;
        for (int i = 0; i < 9; i++)
            if (st[f][i] == 0)
                t2 = i;
        if (t1 - t2 == 1)
            path.push_back('r');
        if (t1 - t2 == -1)
            path.push_back('l');
        if (t1 - t2 == 3)
            path.push_back('d');
        if (t1 - t2 == -3)
            path.push_back('u');
        f = u;
        u = pre[1][u];
    }
    reverse(path.begin(), path.end());
    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i];
    cout << endl;
    return 0;
}