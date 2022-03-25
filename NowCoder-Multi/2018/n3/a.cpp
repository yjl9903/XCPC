#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 35 + 5;

// struct node{
    // int p, a, c, m, id;
// }path[maxn][maxn][maxn][maxn];
bool path[maxn][maxn][maxn][maxn][maxn];
vector<int> v;
int n, p[maxn], a[maxn], c[maxn], m[maxn], g[maxn], mp, ma, mc, mm;
int dp[maxn][maxn][maxn][maxn];

int main(){
    while (~scanf("%d", &n)){
        for (int i = 1; i <= n; i++) scanf("%d%d%d%d%d", &p[i], &a[i], &c[i], &m[i], &g[i]);
        scanf("%d%d%d%d", &mp, &ma, &mc, &mm);
        ms(dp, 0); v.clear(); ms(path, 0);
        for (int i = 1; i <= n; i++){
            for (int j = mp; j >= p[i]; j--) for (int k = ma; k >= a[i]; k--) 
                for (int l = mc; l >= c[i]; l--) for (int q = mm; q >= m[i]; q--){
                    if (dp[j][k][l][q] < dp[j - p[i]][k - a[i]][l - c[i]][q - m[i]] + g[i]){
                        dp[j][k][l][q] = dp[j - p[i]][k - a[i]][l - c[i]][q - m[i]] + g[i];
                        // path[j][k][l][q] = {j - p[i], k - a[i], l - c[i], q - m[i], i};
                        path[i][j][k][l][q] = 1;
                    }
                }
        }
        int i = n, j = mp, k = ma, l = mc, q = mm, cnt = 0;
        while (i > 0){
            if (!j && !k && !l && !q) break;
            if (path[i][j][k][l][q]){
                v.push_back(i);
                j -= p[i]; k -= a[i]; l -= c[i]; q -= m[i];
            }
            i--;
        }
        printf("%d\n", v.size());
        for (int i = 0; i < v.size(); i++){
            if (i) printf(" ");
            printf("%d", v[i] - 1);
        }
        printf("\n");
        // printf("%d\n", dp[mp][ma][mc][mm]);
    }
    return 0;
}