#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 362880 + 5;

int fac[10], st[maxn][9], pre[9][maxn], vis[maxn];
int dir[4][2] = {1, 0, 0, -1, 0, 1, -1, 0};

int cantor(int x[]){
    int s = 0;
    for (int i = 0; i < 9; i++)
    {
        int t = 0;
        for (int j = i + 1; j < 9; j++)
            if (x[i] > x[j])
                t++;
        s += fac[8 - i] * t;
    }
    return s;
}
int cantor(int t, int x[]){
    int v[11] = {0};
    ms(v, 0);
    for (int i = 8; i >= 0; i--){
        int k = t / fac[i];
        t = t % fac[i];
        int j = 0, s = 0;
        while (s < k || v[j])
        {
            if (!v[j])
                s++;
            j++;
        }
        v[j] = 1;
        x[8 - i] = j;
    }
    return 0;
}
void show(int x[9]){
    for (int i = 0; i < 9; i++){
        if (i && i % 3 == 0)
            cout << endl;
        cout << x[i] << ' ';
    }
    cout << endl << endl;
}

int bfs(int p){
    ms(vis, 0);
    queue<int> q;
    q.push(1);
    vis[cantor(st[1])] = 1;
    int cnt = 1;
    while (!q.empty()){
        int t = q.front(), tx, ty, x, y;
        q.pop();
        // show(st[t]);
        for (int i = 0; i < 9; i++)
            if (!st[t][i])
                tx = i / 3, ty = i % 3;
        for (int i = 0; i < 4; i++){
            x = tx + dir[i][0], y = ty + dir[i][1];
            if (x < 0 || y < 0 || x > 2 || y > 2)
                continue;
            memcpy(st[++cnt], st[t], sizeof(st[t]));
            swap(st[cnt][3 * x + y], st[cnt][3 * tx + ty]);
            int c = cantor(st[cnt]);
            if (!vis[c]){
                vis[c] = 1;
                pre[p][c] = cantor(st[t]);
                // pre[p][cnt] = t;
                // shash[p][c] = cnt;
                q.push(cnt);
            }
            else{
                cnt--;
            }
        }
    }
    return 0;
}

void init(){
    ms(pre, -1);
    fac[0] = fac[1] = 1;
    for (int i = 2; i < 9; i++)
        fac[i] = fac[i - 1] * i;
    for (int i = 0; i < 9; i++){
        int s = 1;
        for (int j = 0; j < 9; j++){
            if (i == j) st[1][j] = 0;
            else st[1][j] = s++;
        }
        bfs(i);
    }
}

int main()
{
    init();
    char s[20], ss[20];
    int kase = 0; int T;
    cin >> T;
    while (T--){
        cin >> s >> ss;
        int sta[9], dst[9], fo[9], p;
        for (int i = 0, x = 1; i < 9; i++){
            if (s[i] == 'X')
                sta[i] = 0, p = i, fo[0] = 0;
            else
                sta[i] = s[i] - '0', fo[sta[i]] = x++;
        }
        for (int i = 0; i < 9; i++){
            if (ss[i] == 'X') ss[i] = '0';
            dst[i] = fo[ss[i] - '0'];
        }
        // show(sta); show(dst);
        
        int tt[9] = {0};
        for (int i = 0, s = 1; i < 9; i++)
            if (i != p)
                tt[i] = s++;

        int c = cantor(dst), t = cantor(tt);
        int u = pre[p][c], f = c;
        vector<char> path;
        while (u != -1)
        {
            int t1, t2, x1[9], x2[9];
            cantor(u, x1); cantor(f, x2);
            // show(x1);
            for (int i = 0; i < 9; i++)
                if (x1[i] == 0)
                    t1 = i;
            for (int i = 0; i < 9; i++)
                if (x2[i] == 0)
                    t2 = i;
            if (t1 - t2 == 1)
                path.push_back('l');
            if (t1 - t2 == -1)
                path.push_back('r');
            if (t1 - t2 == 3)
                path.push_back('u');
            if (t1 - t2 == -3)
                path.push_back('d');
            f = u;
            u = pre[p][u];
        }
        // int x1[9];
        // cantor(u, x1);
        // show(x1);
        // cout << path.size();
        cout << "Case " << ++kase << ": " << path.size() << endl;
        for (int i = path.size() - 1; i >= 0; i--)
            cout << path[i];
        cout << endl;
    }
    return 0;
}