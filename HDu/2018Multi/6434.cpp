#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20000000 + 5;

int gcd(int a, int b){return b ? gcd(b, a % b) : a;}

int vis[maxn];
ll phi[maxn], pri[maxn], a[maxn];
void init(int n){
    phi[1] = 1;
    for (int i = 2; i <= n; i ++) {
        if (!vis[i]) {
            phi[i] = i - 1; // i是质数，第一种情况。
            pri[++ pri[0]] = i;
        }
        for (int j = 1; j <= pri[0]; j ++) {
            if (1ll * i * pri[j] > n) break;
            vis[i * pri[j]] = 1; //筛质数。
            if (i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j];//（i % pri[j] = 0），第二种情况
                break;
            }
            phi[i * pri[j]] = phi[i] * (pri[j] - 1); //（i % pri[j] ！= 0），第三种情况
        }
    }
    for (int i = 1; i <= n; i++) if (i & 1) phi[i] /= 2;
}

int n;

int main(){
    init(maxn - 1);
    for (int i = 1; i < maxn; i++) a[i] = phi[i] + a[i - 1];
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);  
        printf("%lld\n", a[n]);
    }
    return 0;
}