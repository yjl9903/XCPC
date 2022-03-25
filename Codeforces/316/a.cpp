#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int n, m, a[maxn][maxn];
int v[maxn], c[maxn];

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
    for (int i = 1; i <= m; i++){
        int mx = -1;
        for (int j = 1; j <= n; j++){
            if (a[i][j] > mx) v[i] = j, mx = a[i][j];
        }
        c[v[i]]++;
    }
    int mx = -1, ans = 0;
    for (int i = 1; i <= n; i++) if (c[i] > mx) ans = i, mx = c[i];
    cout << ans;
    return 0;
}