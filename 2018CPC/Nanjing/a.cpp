#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

ll n;   

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%lld", &n);
        // ll x = 1, ans = 1;
        // for (ll i = 2; i <= n; i++){
        //     x = x * i % n;
        //     ans = (ans + x * i % n) % n;
        // }
        printf("%lld\n", n - 1);
    }
    return 0;
}