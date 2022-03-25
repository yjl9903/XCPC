#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

struct edge{int x, y;};
using G = vector<edge>;
inline G read(int m){
    G a;
    for (int i = 0; i < m; i++){
        int x, y; scanf("%d%d", &x, &y);
        a.push_back(edge {x, y});
    }
    return a;
}
G g1, g2;

int n, ma, mb, f[maxn], vis[maxn][maxn];
int ia, ib, da, db;

int count(){
    ms(vis, 0);
    for (int i = 0; i < n; i++) f[i] = i;
    for (int i = 0; i < g2.size(); i++) vis[g2[i].x][g2[i].y] = vis[g2[i].y][g2[i].x] = 1;
    int ans = 0, res = 1 << 30;
    do{
        int t = 0;
        for (int i = 0; i < g1.size(); i++){
            if (!vis[f[g1[i].x]][f[g1[i].y]]){
                t++;
            }
        }
        res = min(res, t);
    } while (next_permutation(f, f + n));
    ans += min(res * da, res * ib);

    ms(vis, 0);
    for (int i = 0; i < n; i++) f[i] = i;
    for (int i = 0; i < g1.size(); i++) vis[g1[i].x][g1[i].y] = vis[g1[i].y][g1[i].x] = 1;
    res = 1 << 30;
    do{
        int t = 0;
        for (int i = 0; i < g2.size(); i++){
            if (!vis[f[g2[i].x]][f[g2[i].y]]){
                t++;
            }
        }
        res = min(res, t);
    } while (next_permutation(f, f + n));
    ans += min(res * ia, res * db);

    return ans;
}

int main(){
    int kase = 0;
    while (~scanf("%d%d%d", &n, &ma, &mb)){
        if (!n && !ma && !mb) break;
        scanf("%d%d%d%d", &ia, &ib, &da, &db);
        g1 = read(ma); g2 = read(mb);
        printf("Case #%d: %d\n", ++kase, count());
    }
    return 0;
}