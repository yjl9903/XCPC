#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10 + 5;

struct edge{int x, y;};
using G = vector<edge>;
int n, m1, m2, vis[maxn][maxn], f[maxn];

inline G read(int m){
    G a;
    for (int i = 0; i < m; i++){
        int x, y; scanf("%d%d", &x, &y);
        a.push_back(edge {x, y});
    }
    return a;
}
inline int count(const G& b, const G& a){
    ms(vis, 0);
    for (int i = 0; i < a.size(); i++) vis[a[i].x][a[i].y] = vis[a[i].y][a[i].x] = 1;
    for (int i = 0; i <= n; i++) f[i] = i;
    int res = 0;
    do{
        bool flag = true;
        for (int i = 0; i < b.size(); i++){
            if (!vis[f[b[i].x]][f[b[i].y]]){
                flag = false; break;
            }
        }
        if (flag) res++;
    } while (next_permutation(f + 1, f + 1 + n));
    return res;
}

int main(){
    while (~scanf("%d%d%d", &n, &m1, &m2)){
        G g1 = read(m1);
        G g2 = read(m2);
        int c1 = count(g1, g2);
        int c2 = count(g1, g1);
        printf("%d\n%d\n", c1, c2);
        printf("%d\n", c1 / c2);
    }
    return 0;
}