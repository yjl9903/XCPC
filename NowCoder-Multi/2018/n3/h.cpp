#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10000000 + 5;

int vis[maxn] = {0}, prime[maxn], cnt = 0;
ll res[maxn] = {0};

int main(){
    vis[1] = 1;
    for (int i = 2; i < maxn; i++){
        if (!vis[i]) prime[cnt++] = i;
        for (int j = 0; j < cnt && prime[j] * i < maxn; j++){
            vis[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    int num = 0;
    for (int i = 2; i < maxn; i++){
        if (!vis[i]) num++;
        res[i] = 1ll * num * (num - 1);
        // for (int j = i / 2, k = 0; j > 2; k++, j = i / prime[k]) res[i] += res[j];
    }
    int n; scanf("%d", &n);
    ll ans = res[n];
    // for (int j = n / 2, k = 0; j > 2 && k < cnt; k++, j = n / prime[j]) ans += res[j];
    for (int j = n / 2, k = 2; j > 2; k++, j = n / k) ans += res[j];
    printf("%lld\n", ans);
    return 0;
}