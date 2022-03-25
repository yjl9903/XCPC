#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;
const int inf = 1 << 30;

int map[maxn][maxn], nxt[maxn], vis[maxn], n;
int d, t;

int find(int p){
    for (int i = 0; i < n; i++){
        if (!vis[i] && map[p][i] >= d && map[p][i] <= t){
            vis[i] = 1;
            if (nxt[i] == -1 || find(nxt[i])){
                nxt[i] = p;
                return true;
            }
        }
    }
    return false;
}
int match(){
    int sum = 0; ms(nxt, -1);    
    for (int i = 0; i < n; i++){
        ms(vis, 0);
        if (find(i)) sum++;
    }
    return sum;
}

int main(){
    int T; cin >> T;
    while (T--){
        cin >> n; 
        int mmax = -inf, mmin = inf;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++){
            int x; cin >> x;
            map[i][j] = x; 
            mmax = max(mmax, x); mmin = min(mmin, x);
        }
        int l = 0, r = mmax - mmin, res = 0;
        while (l <= r){
            int m = (l + r) / 2, flag = 0;
            for (d = mmin; d + m <= mmax; d++){
                t = d + m;
                if (match() == n){
                    flag = 1; break;
                }
            }
            if (flag){
                res = m;
                r = m - 1;
            }
            else {
                l = m + 1;
            }
        }
        cout << res << endl;
    }
    return 0;
}