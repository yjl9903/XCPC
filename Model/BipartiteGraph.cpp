// HDu2063 过山车

#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 500 + 5;

int line[maxn][maxn], k, m, n, vis[maxn], nxt[maxn];

int find(int p){
    for (int i = 1; i <= n; i++){
        if (line[p][i] && !vis[i]){
            vis[i] = 1;
            if (!nxt[i] || find(nxt[i])){
                nxt[i] = p;
                return true;
            }
        }
    }
    return false;
}
int match(){
    int sum = 0;
    for (int i = 1; i <= m; i++){
        ms(vis, 0);
        if (find(i)) sum++;
    }
    return sum;
}

int main(){
    while (cin >> k && k){
        cin >> m >> n; ms(line, 0); ms(nxt, 0);
        while (k--){
            int u, v;
            cin >> u >> v;
            line[u][v] = 1;
        }
        cout << match() << endl;
    }
    return 0;
}