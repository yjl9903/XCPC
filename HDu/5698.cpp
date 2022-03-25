#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;
const int mod = 1000000007;

int f[maxn], inv[maxn], finv[maxn];
void init(){
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    f[0] = finv[0] = 1;
    for (int i = 1; i < maxn; i++) f[i] = f[i - 1] * 1ll * i % mod, finv[i] = finv[i - 1] * 1ll * inv[i] % mod;
}
int C(int n, int m){
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
}

int main(){
    init();
    int n, m;
    while (scanf("%d%d", &n, &m) == 2){
        printf("%d\n", C(n + m - 4, m - 2));
    }
    return 0;
}