#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, a[maxn][maxn], tx, ty;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
        scanf("%d", &a[i][j]);
        if (a[i][j] == -1) tx = i, ty = j;
    }
    for (int i = 1; i <= n; i++){
        if (i == tx) continue;
        int mn = 1 << 30;
        for (int j = 1; j <= n; j++) mn = min(mn, a[i][j]);
        for (int j = 1; j <= n; j++) a[i][j] -= mn;
    }
    for (int i = 1; i <= n; i++){
        if (i == ty) continue;
        int mn = 1 << 30;
        for (int j = 1; j <= n; j++) mn = min(mn, a[j][i]);
        for (int j = 1; j <= n; j++) a[j][i] -= mn;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) if (i != tx){
        ans += a[i][ty]; break;
    }
    for (int i = 1; i <= n; i++) if (i != ty){
        ans += a[tx][i]; break;
    }
    printf("%d", ans);
    return 0;
}