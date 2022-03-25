#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof a)
using namespace std;
typedef long long ll;
const int maxn = 30 + 5;

int G[maxn][maxn], a[maxn], d[maxn], vis[maxn], used[maxn], n, res;
char s[100], x[maxn];

void dfs(int p){
    // cout << p << ' ' << a[p - 1] << endl;
    int tot = 0;
    for (int i = 0; i < p; i++){
        int t = 0;
        for (int j = i + 1; j < p; j++){
            if (G[a[i]][a[j]])   
                t = j - i;
        }
        // cout << t << ' ';
        tot = max(tot, t);
    }
    // cout << endl;
    // if (p == n){
    //     for (int i = 0; i < p; cout << char(a[i++] + 'A') << ' ');
    //     cout << endl << tot << endl;
    // }

    if (tot >= res)  return;
    if (p == n && tot < res){
        for (int i = 0; i < p; i++){
            x[i] = a[i] + 'A';
        }
        res = tot;
    } 
    
     
    for (int i = 0; i < 26; i++){
        if (used[i] && !vis[i]){
            a[p] = i;
            vis[i] = 1;
            dfs(p + 1);
            vis[i] = 0;
        }
    }
}

int main(){
    while (cin >> s && s[0] != '#'){
        ms(G, 0); ms(vis, 0); ms(used, 0); ms(x, 0);
        int len = strlen(s);
        for (int i = 0; i < len; i++){
            if (s[i] >= 'A' && s[i] <= 'Z' && s[i + 1] == ':'){
                int x = s[i] - 'A';
                used[x] = 1;
                for (i = i + 2; s[i] != ';' && i < len; i++){
                    if (s[i] >= 'A' && s[i] <= 'Z'){
                        int y = s[i] - 'A';
                        G[x][y] = G[y][x] = 1;
                        used[y] = 1;
                    }
                }
            }
        }
        n = 0; res = 1 << 30;
        for (int i = 0; i < 26; i++)
            if (used[i])    n++;
        dfs(0);
        len = strlen(x);
        for (int i  = 0; i < len; i++){
            cout << x[i] << ' ';
        }
        cout << "-> " << res << endl;
    }
    return 0;
}