#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;
const int maxm = 10000 + 5;

int dp[maxn][maxm], n, m;

int check(int x, int y){
    if (y < 0 || y > x * (x - 1) / 2) return 0;
    if (!y) return 1;
    if (dp[x][y] != -1) return dp[x][y];
    for (int i = 1; i <= x; i++){
        if (check(x - i, y - i * (x - i))) 
            return dp[x][y] = 1;
    }
    return dp[x][y] = 0;
}

int main(){
    ms(dp, -1);
    int kase = 0;
    while (~scanf("%d%d", &n, &m)){
        if (!n && !m) return 0;
        printf("Case %d: %d ", ++kase, n);
        if (check(n, m)){
            printf("lines with exactly %d crossings can cut the plane into %d pieces at most.\n", m, n + m + 1);
        }
        else {
            printf("lines cannot make exactly %d crossings.\n", m);
        }
    }
    return 0;
}