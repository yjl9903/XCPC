#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 500000 + 5;
const int inf = 1 << 30;

int n, l, a[maxn], b[maxn];

int get(int i, int j){
    int t = min(abs(a[i] + l - b[j]), abs(a[i] - l - b[j]));
    return -min(abs(a[i] - b[j]), t);
}

int nxt[maxn], wx[maxn], wy[maxn], visx[maxn], visy[maxn], d;
int dfs(int p){
    visx[p] = 1;
    for (int i = 0; i < n; i++){
        if (visy[i]) continue;
        int t = wx[p] + wy[i] - get(p, i);
        if (t == 0){
            visy[i] = 1;
            if (nxt[i] == -1 || dfs(nxt[i])){
                nxt[i] = p;
                return true;
            }
        }
        else if (t > 0){
            d = min(d, t);
        }
    }
    return false;
}
int km(){
    ms(nxt, -1); ms(wy, 0); ms(wx, 0);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) wx[i] = max(wx[i], get(i, j));
    for (int i = 0; i < n; i++){
        while (1){
            ms(visx, 0); ms(visy, 0); d = inf; 
            if (dfs(i)) break;
            for (int i = 0; i < n; i++) {
                if (visx[i]) wx[i] -= d;
                if (visy[i]) wy[i] += d;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++) res += get(nxt[i], i);
    return -res;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &l);
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        for (int i = 0; i < n; i++) scanf("%d", &b[i]);
        printf("%d\n", km());
    }
    return 0;
}