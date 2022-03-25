#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 300000 + 5;

int n, a[maxn], b[maxn];
ll s[2][3][maxn] = {0};

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) scanf("%d", &b[i]);
    for (int i = n - 1; i >= 0; i--) s[0][0][i] = s[0][0][i + 1] + 1ll * a[i] * (i + 1);
    for (int i = n - 1; i >= 0; i--) s[1][0][i] = s[1][0][i + 1] + 1ll * b[i] * (i + 1);
    for (int i = n - 1; i >= 0; i--) s[0][1][i] = s[0][1][i + 1] + 1ll * a[i] * (n - i);
    for (int i = n - 1; i >= 0; i--) s[1][1][i] = s[1][1][i + 1] + 1ll * b[i] * (n - i);
    for (int i = n - 1; i >= 0; i--) s[0][2][i] = s[0][2][i + 1] + 1ll * a[i];
    for (int i = n - 1; i >= 0; i--) s[1][2][i] = s[1][2][i + 1] + 1ll * b[i];
    ll res = 0, sum = 0;
    for (int i = 0, j = 0; j < n; j++, i ^= 1){
        ll t = sum;
        t += s[i][0][j] + j * 1ll * s[i][2][j];
        t += s[i ^ 1][1][j] + (j + n) * 1ll * s[i ^ 1][2][j];
        res = max(t, res);
        
        if (i == 0){
            sum += a[j] * 1ll * (j + j + 1);
            sum += b[j] * 1ll * (j + j + 2);
        }
        else{
            sum += b[j] * 1ll * (j + j + 1);
            sum += a[j] * 1ll * (j + j + 2);
        }
    }
    for (int i = 0; i < n; i++) res -= a[i] + b[i];
    printf("%I64d", res);
    return 0;
}