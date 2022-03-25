#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 362880 + 5;

int f[10], st[maxn][9], pre[maxn], vis[maxn], shash[maxn];
int dir[4][2] = {1, 0, 0, -1, 0, 1, -1, 0};
void init(){
    f[0] = f[1] = 1;
    for (int i = 2; i < 9; i++)
        f[i] = f[i - 1] * i;
}
int cantor(int x[]){
    int s = 0;
    for (int i = 0; i < 9; i++){
        int t = 0;
        for (int j = i + 1; j < 9; j++)
            if (x[i] > x[j]) t++;
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
    cout << endl << endl;
}

int bfs(){
    ms(pre, 0); ms(vis, 0);
    queue<int> q; q.push(1); vis[cantor(st[1])] = 1;
    int cnt = 2;
    while (!q.empty()){
        int t = q.front(), tx, ty, x, y; q.pop();
        if (cantor(st[t]) == cantor(st[2])) return t;
        // show(st[t]);
        for (int i = 0; i < 9; i++)
            if (!st[t][i])
                tx = i / 3, ty = i % 3;
        for (int i = 0; i < 4; i++){
            x = tx + dir[i][0], y = ty + dir[i][1];
            if (x < 0 || y < 0 || x > 2 || y > 2) continue;
            memcpy(st[++cnt], st[t], sizeof(st[t]));
            swap(st[cnt][3 * x + y], st[cnt][3 * tx + ty]);
            int c = cantor(st[cnt]);
            if (!vis[c]){
                vis[c] = 1;
                shash[c] = cnt;
                pre[cnt] = t;
                q.push(cnt);
            }
            else{
                cnt--;
            }
        }
    }
    return 0;
}

int main(){
    init(); char s[20], ss[20]; int kase = 0;
    int T; cin >> T;
    while (T--){
        cin >> s >> ss;
        for (int i = 0; i < 9; i++){
            if (s[i] == 'X') st[1][i] = 0;
            else st[1][i] = s[i] - '0';
        }
        for (int i = 0; i < 9; i++){
            if (ss[i] == 'X')
                st[2][i] = 0;
            else
                st[2][i] = ss[i] - '0';
        }
        int c = cantor(st[bfs()]);
        int u = pre[shash[c]], f = shash[c]; vector<char> path;
        while (u){
            // show(st[u]);
            int t1, t2;
            for (int i = 0; i < 9; i++)
                if (st[u][i] == 0)
                    t1 = i;
            for (int i = 0; i < 9; i++)
                if (st[f][i] == 0)
                    t2 = i;
            if (t2 - t1 == 1)
                path.push_back('r');
            if (t2 - t1 == -1)
                path.push_back('l');
            if (t2 - t1 == 3)
                path.push_back('d');
            if (t2 - t1 == -3)
                path.push_back('u');
            f = u;
            u = pre[u];
        }
        // cout << path.size();
        cout << "Case " << ++kase << ": " << path.size() << endl;
        for (int i = path.size() - 1; i >= 0; i--)
            cout << path[i];
        cout << endl;
    }
    return 0;
}