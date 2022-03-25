#include <iostream>
#include <cstring>
#include <algorithm>
#include <utility>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn = 16 + 2;

int w, h, n, ghost[3], map[maxn][maxn], G[maxn * maxn][5], vis[maxn * maxn][maxn * maxn][maxn * maxn], cnt;
int dir[5][2] = {1, 0, 0, 1, -1, 0, 0, -1, 0, 0};
PII sta[30], des[30];

struct node{
    int a[3] = {0, 0, 0};
    int d = 0;
};

void bfs(){
    queue<node> q;
    node t;
    for (int i = 0 ; i < n; i++){
        t.a[i] = sta[ghost[i]].first * w + sta[ghost[i]].second;
    }
    // t.a[0] = sta[ghost[0]].first * w + sta[ghost[0]].second;
    // t.a[1] = sta[ghost[1]].first * w + sta[ghost[1]].second;
    // t.a[2] = sta[ghost[2]].first * w + sta[ghost[2]].second;
    t.d = 0;
    vis[t.a[0]][t.a[1]][t.a[2]] = 1;
    q.push(t);
    while (!q.empty()){
        node x = q.front(); q.pop();
        node t;
        int m = 0;
        for (int i = 0; i < n; i++)
            if (x.a[i] == 0)
                m = 1;
        if (m) continue;
        // cout << x.a[0] / w << '-' << x.a[0] % w << ' ' << x.a[1] / w << '-' << x.a[1] % w << ' ' << x.a[2] / w << '-' << x.a[2] % w << ' ' << x.d << endl;
        int flag = 1;
        for (int i = 0; i < n; i++){
            
            if (x.a[i] != des[ghost[i]].first * w + des[ghost[i]].second){
                flag = 0; break;
            }
        }
        if (flag){
            // cout << x.a[0] << ' ' << x.a[1] << ' ' << x.a[2] << endl;
            cout << x.d << endl;
            return;
        }

        for (int i = 0; i < 5; i++){
            for (int j = 0 ; j < 5; j++){
                for (int k = 0; k < 5; k++){
                    t.a[0] = G[x.a[0]][i];
                    t.a[1] = G[x.a[1]][j];
                    t.a[2] = G[x.a[2]][k];
                    if (t.a[0] && t.a[1] && (t.a[0] == t.a[1] || (t.a[0] == x.a[1] && t.a[1] == x.a[0])))
                        continue;
                    if (t.a[0] && t.a[2] && (t.a[0] == t.a[2] || (t.a[0] == x.a[2] && t.a[2] == x.a[0])))
                        continue;
                    if (t.a[1] && t.a[2] && (t.a[1] == t.a[2] || (t.a[1] == x.a[2] && t.a[2] == x.a[1])))
                        continue;
                    
                    if (!vis[t.a[0]][t.a[1]][t.a[2]]){
                        // cout << t.a[0] / w << '-' << t.a[0] % w << ' ' << t.a[1] / w << '-' << t.a[1] % w << ' ' << t.a[2] / w << '-' << t.a[2] % w << ' '<< endl;
                        // cout << x.a[0] / w << '-' << x.a[0] % w << ' ' << x.a[1] / w << '-' << x.a[1] % w << ' ' << x.a[2] / w << '-' << x.a[2] % w << ' ' << x.d << endl << endl;
                        vis[t.a[0]][t.a[1]][t.a[2]] = 1;
                        t.d = x.d + 1;
                        q.push(t);
                    }
                }
            }
        }
    }
}

int main(){
    while (cin >> w >> h >> n && w && h && n){
        ms(sta, 0); ms(des, 0); ms(ghost, 0);
        char s[20]; cnt = 0;
        cin.ignore();
        for (int i = 0; i < h; i++){
            cin.getline(s, 20);
            for (int j = 0; j < w; j++){
                if (s[j] == '#')
                    map[i][j] = 0;
                else if (s[j] == ' ')
                    map[i][j] = 1;
                else if (s[j] >= 'a' && s[j] <= 'z')
                    map[i][j] = 1, sta[s[j] - 'a'] = make_pair(i, j), ghost[cnt++] = s[j] - 'a';
                else if (s[j] >= 'A' && s[j] <= 'Z')
                    map[i][j] = 1, des[s[j] - 'A'] = make_pair(i, j);
            }
        }
        cnt = 0; ms(G, 0); ms(vis, 0);
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++){
                if (map[i][j]){
                    for (int k = 0; k < 5; k++){
                        int x = i + dir[k][0], y = j + dir[k][1];
                        if (map[x][y]){
                            G[i * w + j][k] = x * w + y;
                        }
                    }
                }
            }
        bfs();
        // for (int i = 0; i < h; i++, cout << endl)
        //     for (int j = 0; j < w; cout << map[i][j++]);
    }
    return 0;
}