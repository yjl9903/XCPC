#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;



int main(){
    int T; scanf("%d", &T);
    while (T--){
        int a, b, k; scanf("%d%d%d", &a, &b, &k);
        ll ans = 1ll * (a - b) * (k / 2);
        if (k % 2) ans += a;
        printf("%I64d\n", ans);
    }
    return 0;
}