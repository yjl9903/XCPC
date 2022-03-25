#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int n, nxt[maxn], vis[maxn], m[maxn][maxn], cnt = 0;
int cmd[maxn * 10][2];

int find(int p){
    for (int i = 1; i <= n; i++){
        int v = i;
        if (!m[p][v]) continue;
        if (!vis[v]){
            vis[v] = 1;
            if (!nxt[v] || find(nxt[v])){
                nxt[v] = p;
                return true;
            }
        }
    }
    return false;
}
int match(){
    int sum = 0;
    for (int i = 1; i <= n; i++){
        ms(vis, 0);
        if (find(i)) sum++;
    }
    return sum;
}

int main(){
    while (cin >> n){
        cnt = 0; ms(nxt, 0);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++){
                cin >> m[i][j];
            }
        if (match() != n){
            cout << "-1" << endl; continue;
        }
        int num = 0;
        for (int i = 1; i <= n; i++){
            if (nxt[i] != i){
                cmd[num][0] = i; cmd[num][1] = nxt[i]; num++;
                for (int j = 1; j <= n; j++)
                    if (nxt[j] == i){
                        swap(nxt[j], nxt[i]);
                        break;
                    }
            }
        }
        cout << num << endl;
        for (int i = 0; i < num; i++) cout << "R " << cmd[i][0] << ' ' << cmd[i][1] << endl;
    }
    return 0;
}