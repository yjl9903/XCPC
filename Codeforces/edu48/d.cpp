#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m, a[maxn], b[maxn], map[maxn][maxn], vis[maxn] = {0};

int main(){
    scanf("%d%d", &n, &m);
    int s = 0;
    for (int i = 0; i < n; i++) scanf("%d", &a[i]), s ^= a[i];
    for (int i = 0; i < m; i++) scanf("%d", &b[i]), s ^= b[i];
    if (s){
        puts("NO"); return 0;
    }
    puts("YES");
    for (int i = 0; i < n - 1; i++){
        int t = 0;
        for (int j = 0; j < m - 1; j++){
            map[i][j] = j + 1;
            t ^= j + 1;
            vis[j] ^= j + 1;
        }
        map[i][m - 1] = a[i] ^ t;
        vis[m - 1] ^= a[i] ^ t;
    }
    for (int i = 0; i < m; i++){
        map[n - 1][i] = b[i] ^ vis[i];
    }
    for (int i = 0; i < n; i++, puts("")) for (int j = 0; j < m; j++){
        printf("%d ", map[i][j]);
    }
    return 0;
}